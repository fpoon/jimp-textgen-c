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

static Ngram_t ** initNgrams(int grams)
{
	int i;
	Ngram_t ** ret = (Ngram_t **) malloc(sizeof(Ngram_t*)*settings->grams);
	memset(ret, 0, sizeof(Ngram_t*)*settings->grams);

	return ret;
}

int analyzeTrainingText(const char * path, Database_t * db)
{
	FILE * file;
	int counter = 0;
	int i,a;
	char buffer[BUFFER_SIZE];
	List_t * tmp, itable;
	int * ngrams_cnt = (int*) malloc(settings->grams*(sizeof(int)));

	memset(ngrams_cnt,0,settings->grams*(sizeof(int)));
	Ngram_t ** ngrams = initNgrams(settings->grams);

	slog("Otwieranie pliku %s\n", path);
	file = fopen(path,"r");
	if (!file)
	{
		return -1;
	}

	while (fscanf(file, "%s", buffer) != EOF)
	{
		addWordToDB(db, buffer);

		if (counter >= settings->grams)
			a = settings->grams;
		else
			a = counter+1;

		for (i = 0; i < a; i++)
		{
			ngrams[i] = addToNgram((Ngram_t*)ngrams[i], buffer, ngrams_cnt[i]++);
			if (ngrams_cnt[i] >= settings->grams)
			{
				addNgramToDB(db, ngrams[i]);
				//freeNgram(ngrams[i]);
				ngrams[i] = newNgram();
			}
			ngrams_cnt[i] %= settings->grams;
		}


		counter++;
	}

	slog("Plik %s: Wczytano %d słów\n", path, counter);

	fclose(file);
	return 0;
}
