/*
 * ngrams.c
 *
 *  Created on: 10 kwi 2015
 *      Author: mariusz
 */

#include <stdlib.h>
#include <string.h>

#include "ngrams.h"
#include "settings.h"

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

Ngram_t * addToNgram(Ngram_t * ngram, const char * word, int n)
{
	void * v;

	if (n >= settings->grams)
		return NULL;

	if (ngram == NULL)
	{
		ngram = (Ngram_t*) malloc(sizeof(Ngram_t));
		memset((void*)ngram, 0, sizeof(Ngram_t));
	}

	if (n < settings->grams-1)
	{
		v = malloc(strlen(word)+1);
		memcpy(v, (const void*)word, strlen(word)+1);
		ngram->prefixes = addToList(ngram->prefixes, v);
	}
	else
	{
		v = malloc(strlen(word)+1+sizeof(Word_t));
		memcpy(v+sizeof(Word_t), (const void*)word, strlen(word)+1);
		((Word_t*)v)->word = v+sizeof(Word_t);
		((Word_t*)v)->instances = 1;
		ngram->suffixes = addToList(ngram->suffixes, v);
	}

	return ngram;
}

Word_t * searchWordList(List_t * list, char * str)
{
	if (!list)
		return NULL;

	while (list)
	{
		if(!strcmp(((Word_t *)list->val)->word, str))
			return (Word_t *)list->val;
		list = list->next;
	}
	return NULL;
}
