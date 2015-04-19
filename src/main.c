/*
 * main.c
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "settings.h"
#include "utilities.h"
#include "traintextanal.h"
#include "markov.h"
#include "ngrams.h"
#include "database.h"


int main(int argc, const char * argv[])
{
	int error;
	List_t * input;
	Database_t * db;
	srand(time(NULL));
	settings = loadSettings(argc, argv);
	error = settings->error_code;
	if(error)
	{
		fprintf(stderr, "Błąd: %s", SETTINGS_FAILURES[settings->error_code]);
		if(settings->fatal)
		{
			freeSettings(settings);
			return error;
		}
	}
	input = settings->input;

	db = openDB(DEFAULT_DATABASE_PATH);

	while(input != NULL)
	{
		analyzeTrainingText((const char*)input->val, db);
		input = input->next;
	}

	printf("%s\n\n",createMarkovChain(db, 100));

	closeDB(db);

	//freeSettings(settings);

	debugLog("--THE END--\n");

	return 0;
}
