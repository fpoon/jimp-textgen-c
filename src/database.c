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

	fclose(file);

	debugLog("Zapisano.\n");
}

void closeDB(Database_t * db)
{
	flushDB(db);
}

int addWordToDB(Database_t * db, const char * word)
{
	void * v = malloc(strlen(word)+1);
	memcpy(v, (const void*)word, strlen(word)+1);
	debugLog("Dodaję słowo \"%s\" do bazy danych\n", (char*)v);
	if(db)
	{
		db->header.words++;
		db->words = addToList(db->words, v);
	}
	return 0;
}

int addNgramToDB(Database_t * db, Ngram_t * ngram)
{
	List_t * list = ngram->prefixes;
	int i = 0;
	debugLog("Dodaję %d-gram: ", settings->grams);
	while (list != NULL)
	{
		debugLog("%s ", (const char*)list->val);
		list = list->next;
	}
	debugLog("%s\n", (const char*)ngram->suffixes->val);

	return 0;
}

Ngram_t * getNgramFromDB(Database_t * db, List_t prefixes)
{
	return NULL;
}
