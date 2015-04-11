/*
 * database.c
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "ngrams.h"
#include "utilities.h"
#include "settings.h"

static Database_t * createDB(const char * path)
{
	FILE * file;
	Database_t * db;

	if (path == NULL)
		path = DEFAULT_DATABASE_PATH;

	if (!(file = fopen(path, "w")))
			return NULL;

	debugLog("Tworzenie bazy danych %s.\n", path);

	db = (Database_t *)malloc(sizeof(Database_t));
	memset(db, 0, sizeof(Database_t));

	/* Inicjalizacja pustej bazy danych */
	db->path = path;
	db->header.magic = DATABASE_MAGIC;
	db->header.version = DATABASE_VERSION;
	db->header.words_section = sizeof(DB_Header_t);
	db->header.ngrams_section = sizeof(DB_Header_t);
	db->words = NULL;

	fwrite((const void*)&db->header, sizeof(DB_Header_t), 1, file);

	fclose(file);
	debugLog("Utworzono bazę danych %s.\n", path);

	return db;
}

Database_t * openDB(const char * path)
{
	FILE * file;
	Database_t * db;

	if (path == NULL)
		return createDB(path);

	if (!(file = fopen(path, "rw")))
		return createDB(path);

	debugLog("Otwarto bazę danych %s.", path);

	db = (Database_t *)malloc(sizeof(Database_t));
	memset(db, 0, sizeof(Database_t));
	db->path = path;



	fclose(file);

	return db;
}

void flushDB(Database_t * db)
{
	FILE * file;
	List_t * list = db->words;
	List_t * list2;
	debugLog("Zapisywanie do bazy danych %s.\n", db->path);
	file = fopen(db->path, "w");
	fwrite((const void*)&db->header, sizeof(DB_Header_t), 1, file);

	while (list)
	{
		debugLog("Zapisuję %s\n", (char *)list->val);
		fwrite((const void *)list->val, sizeof(char), strlen((char *)list->val), file);
		fputc(0, file);
		list = list->next;
	}

	list = db->ngrams;

	while (list)
	{
		list2 = ((Ngram_t*)list->val)->prefixes;
		debugLog("Zapisuję %d-ngram(%dx): ", settings->grams, ((Ngram_t*)list->val)->instances);
		while (list2)
		{
			debugLog("%s ", (const char*)list2->val);
			list2 = list2->next;
		}
		list2 = ((Ngram_t*)list->val)->suffixes;
		debugLog("(");
		while (list2)
		{
			debugLog("%d x %s, ",
					((Word_t*)list2->val)->instances,
					((Word_t*)list2->val)->word);
			list2 = list2->next;
		}
		debugLog(")\n");
		list = list->next;
	}

	fclose(file);

	debugLog("Zapisano.\n");
}

void closeDB(Database_t * db)
{
	flushDB(db);
	freeList(db->words);
	//freeList(db->ngrams);
}

int addWordToDB(Database_t * db, const char * word)
{
	void * v;
	debugLog("Dodaję słowo \"%s\" do bazy danych\n", word);
	if(db)
	{
		db->header.total_words++;
		if(!searchStringList(db->words, (char*)word))
		{
			db->header.ngrams_section += strlen(word)+1;
			v = malloc(strlen(word)+1);
			memcpy(v, (const void*)word, strlen(word)+1);
			db->header.unique_words++;
			db->words = addToList(db->words, v);
		}

	}
	return 0;
}

int addNgramToDB(Database_t * db, Ngram_t * ngram)
{
	List_t * list = ngram->prefixes;
	Word_t * word;
	Ngram_t * ng;
	int i = 0;
	debugLog("Dodaję %d-gram: ", settings->grams);
	while (list != NULL)
	{
		debugLog("%s ", (const char*)list->val);
		list = list->next;
	}
	debugLog("%s\n", ((Word_t*)ngram->suffixes->val)->word);

	if(!db) return -1;
	if(!(ng = getNgramFromDB(db, ngram->prefixes)))
	{
		ngram->instances = 1;
		db->header.ngrams++;
		db->ngrams = addToList(db->ngrams, ngram);
	}
	else
	{
		ng->instances++;
		word = searchWordList(ng->suffixes, ((Word_t*)ngram->suffixes->val)->word);
		if (word)
			word->instances++;
		else
			ng->suffixes = addToList(ng->suffixes, ngram->suffixes->val);
	}

	return 0;
}

Ngram_t * getNgramFromDB(Database_t * db, List_t * prefixes)
{
	List_t * list, * list2, * list3;
	int flag = false;
	list = db->ngrams;

	while (list)
	{
		list2 = ((Ngram_t*)list->val)->prefixes;
		list3 = prefixes;
		flag = 1;
		while(list3 && list2 && flag)
		{
			flag = !strcmp((char *)list2->val, (char *)list3->val);
			list2 = list2->next;
			list3 = list3->next;
		}
		if (flag)
			return (Ngram_t*)list->val;
		list = list->next;
	}
	return NULL;
}
