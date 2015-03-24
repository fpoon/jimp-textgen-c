/*
 * database.c
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#include <stdio.h>

#include "database.h"
#include "ngrams.h"

int addWordToDB(Database_t * db, const char * word)
{
	printf("Dodaję słowo do bazy danych\n");
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
