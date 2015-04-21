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
	int error, foo, bar, foobar;
	List_t * input;
	FILE * output;
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
	slog("Włączono wyświetlanie statystyki\n");
	input = settings->input;

	db = openDB(settings->database);
	if (db == NULL)
	{
		fprintf(stderr, "Nie można otworzyć bazy danych!\n");
		return -1;
	}
	foo = db->header.unique_words;
	bar = db->header.ngrams;
	foobar = db->header.total_words;

	while(input != NULL)
	{
		analyzeTrainingText((const char*)input->val, db);
		input = input->next;
	}

	slog("Do bazy danych %s dodano:\n", db->path);
	slog(" - %d nowych wyrazów;\n", db->header.unique_words-foo);
	slog(" - %d wystąpień wyrazów;\n", db->header.total_words-foobar);
	slog(" - %d nowych %d-gramów;\n", db->header.ngrams-bar, db->header.ngrams_length);

	output = settings->output == NULL ? stdout : fopen(settings->output, "w");

	fprintf(output, "%s", createMarkovChain(db, settings->length));

	fclose(output);

	closeDB(db);

	freeSettings(settings);

	debugLog("--THE END--\n");

	return 0;
}
