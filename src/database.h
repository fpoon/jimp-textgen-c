/*
 * database.h
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#ifndef SRC_DATABASE_H_
#define SRC_DATABASE_H_

#include "ngrams.h"
#include "utilities.h"

#define DEFAULT_DATABASE_PATH "./database.db"
#define DATABASE_MAGIC 0x41505544
#define DATABASE_VERSION 0x1

typedef struct
{
	int magic;
	int version;
	int words;
	int words_section;
	int ngrams_lenght;
	int ngrams;
	int ngrams_section;

	char reserved[100];
} DB_Header_t;

typedef struct
{
	const char * path;
	DB_Header_t  header;
	List_t     * words;
	List_t     * ngrams;
} Database_t;

Database_t * openDB(const char * path);

int addWordToDB(Database_t * db, const char * word);
int addNgramToDB(Database_t * db, Ngram_t * ngram);

Ngram_t * getNgramFromDB(Database_t * db, List_t prefixes);

#endif /* SRC_DATABASE_H_ */
