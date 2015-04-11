/*
 * markov.c
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#include <time.h>
#include <stdlib.h>

#include "ngrams.h"
#include "markov.h"
#include "database.h"

static const char * getSuffix(Ngram_t * ngram)
{
	if (!ngram) return NULL;
	int start = 0, end = rand()%ngram->instances;
	List_t * list = ngram->suffixes;
	const char * suf = NULL;

	while (list && start < end)
	{
		suf = ((Word_t*)list->val)->word;
		start += ((Word_t*)list->val)->instances;
		list = list->next;
	}

	return suf;
}

const char * createMarkovChain(Database_t * db, int lenght)
{
	Ngram_t * ngram;
	List_t * list = db->ngrams, *list2, *text = NULL;
	int i=0, a = rand()%db->header.ngrams;
	const char * suf;

	while(list && i != a)
	{
		list = list->next;
		i++;
	}

	ngram = (Ngram_t*)list->val;
	list = ngram->prefixes;

	while(list)
	{
		text = addToList(text,list->val);
		list = list->next;
	}

	list2 = NULL;

	return "JESTĘ TEKSTĘ";
}
