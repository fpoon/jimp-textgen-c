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

Database_t * openDB(const char * file)
{
	return NULL;
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
	debugLog("Dodaję słowo \"%s\" do bazy danych\n", word);
	return 0;
}

int addNgramToDB(Database_t * db, Ngram_t * ngram)
{
	return 0;
}

Ngram_t * getNgramFromDB(Database_t * db, List_t prefixes)
{
	return NULL;
}
