/*
 * database.c
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#include <stdio.h>

#include "database.h"
#include "ngrams.h"
#include "utilities.h"
#include "settings.h"

static Database_t * createDB(const char * path)
{
	return NULL;
}

Database_t * openDB(const char * path)
{
	FILE * file;
	Database_t * db;

	if (path == NULL)
		return createDB(path);

	if (!(file = fopen(path, "rw")))
		return createDB(path);

	fclose(file);

	return db;
}

void flushDB(Database_t * db)
{

}

void closeDB(Database_t * db)
{
	flushDB(db);
}

int addWordToDB(Database_t * db, const char * word)
{
	//debugLog("Dodaję słowo \"%s\" do bazy danych\n", word);
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
