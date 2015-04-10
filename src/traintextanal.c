/*
 * traintextanal.c
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "database.h"
#include "traintextanal.h"
#include "settings.h"
#include "utilities.h"

static List_t * initNgrams(int grams)
{
	int i;
	List_t * it = NULL;
	for(i = 0; i < settings->grams; i++)
	{
		List_t * tmp = malloc(sizeof(List_t));
		tmp->val =  NULL;
		tmp->next = it;
		it = tmp;
	}
	return it;
}

static int addToNgram(Ngram_t * ngram, const char * word, int n)
{
	void * v;
	if (n >= settings->grams) return -1;

	v = malloc(strlen(word)+1);
	memcpy(v, (const void*)word, strlen(word)+1);

	if (n < settings->grams-1)
		ngram->prefixes = addToList(ngram->prefixes, v);
	else
		ngram->suffixes = addToList(ngram->suffixes, v);

	return 0;
}

int analyzeTrainingText(const char * path, Database_t * db)
{
	FILE * file;
	int counter = 0;
	char buffer[BUFFER_SIZE];

	List_t * ngrams = initNgrams(settings->grams);

	debugLog("Otwieranie pliku %s\n", path);
	file = fopen(path,"r");

	while (fscanf(file, "%s", buffer) != EOF)
	{
		addWordToDB(db, buffer);
		//addToNgram((Ngram_t*)ngrams->val, buffer, 0);
		counter++;
	}

	debugLog("Wczytano %d słów\n", counter);

	freeList(ngrams);

	fclose(file);
	return 0;
}
