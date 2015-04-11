/*
 * ngrams.c
 *
 *  Created on: 10 kwi 2015
 *      Author: mariusz
 */

#include <stdlib.h>
#include <string.h>

#include "ngrams.h"

void freeNgram(Ngram_t * ngram)
{
	freeList(ngram->prefixes);
	freeList(ngram->suffixes);
	//free(ngram);
}

Ngram_t * newNgram()
{
	Ngram_t * ngram = (List_t*) malloc(sizeof(List_t));
	memset((void*)ngram, 0, sizeof(List_t));
	return ngram;
}