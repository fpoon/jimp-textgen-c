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
#define DATABASE_MAGIC 0x564B524D
#define DATABASE_VERSION 0x1

typedef enum
{
	Valid = 0x0,
	Invalid_magic,
	Invalid_sections,
	Invalid_ngrams
} DB_ERRORS;

typedef struct
{
	int magic;         //0x00
	int version;       //0x04
	int total_words;   //0x08
	int unique_words;  //0x0C
	int words_section; //0x10
	int ngrams_length; //0x14
	int ngrams;        //0x18
	int ngrams_section;//0x1C

	char reserved[96]; //0x20
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

Ngram_t * getNgramFromDB(Database_t * db, List_t * prefixes);

#endif /* SRC_DATABASE_H_ */
