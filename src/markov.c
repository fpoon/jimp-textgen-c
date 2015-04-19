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
#include "utilities.h"
#include "settings.h"

static const char * getSuffix(Ngram_t * ngram)
{
	if (!ngram) return NULL;
	int start = 0, end = rand()%ngram->instances;
	List_t * list = ngram->suffixes;
	const char * suf = NULL;

	do
	{
		suf = ((Word_t*)list->val)->word;
		start += ((Word_t*)list->val)->instances;
		list = list->next;
	} while (list && start < end);

	return suf;
}

const char * createMarkovChain(Database_t * db, int length)
{
	Ngram_t * ngram;
	List_t * list = db->ngrams, *list2;
	int i=0,j, a = rand()%db->header.ngrams;
	const char * suf;
	String_t * text = NULL;

	//Wylosowanie początkowego n-gramu

	while(list && i != a)
	{
		list = list->next;
		i++;
	}

	//debugLog("%p\n",ngram);

	ngram = (Ngram_t*)list->val;
	list = ngram->prefixes;

	//Wypełnienie pierwszym n-gramem

	i = 0;
	list2 = NULL;
	while(list)
	{
		text = addToString(text,list->val);
		text = addToString(text," ");
		if (i > 0) list2 = addToList(list2,list->val);
		list = list->next;
		i++;
	}

	//Główna pętla

	for(i = settings->grams-1; i < length && ngram != NULL; i++)
	{
		//debugLog("Przejscie %d\n%s\n",i,text->str);
		suf = getSuffix(ngram);
		text = addToString(text, suf);
		//debugLog("Text: %s\n",text->str);
		list2 = addToList(list2, suf);
		ngram = getNgramFromDB(db, list2);
		if(!ngram)
		{
			debugLog("Pusty ngram. Koniec.\n");
			break;
		}
		text = addToString(text, " ");
		list = ngram->prefixes;
		list2 = NULL;
		for (j = 0; list; j++)
		{
			if (j > 0) list2 = addToList(list2,list->val);
			list = list->next;
		}
	}

	return text->str;
}
