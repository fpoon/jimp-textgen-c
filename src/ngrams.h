/*
 * ngrams.h
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#ifndef SRC_NGRAMS_H_
#define SRC_NGRAMS_H_

#include "utilities.h"

typedef struct
{
	const char * word;
	int          instances;
} Word_t;


typedef Word_t Suffix_t;

typedef struct
{
	List_t * prefixes;
	int      instances;
	List_t * suffixes;
} Ngram_t;

void freeNgram(Ngram_t * ngram);
Ngram_t * newNgram();
Word_t * searchWordList(List_t * list, char * str);
Ngram_t * addToNgram(Ngram_t * ngram, const char * word, int n);

#endif /* SRC_NGRAMS_H_ */
