/*
 * main.c
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#include <stdio.h>

#include "settings.h"
#include "utilities.h"
#include "traintextanal.h"
#include "markov.h"
#include "ngrams.h"
#include "database.h"


int main(int argc, const char * argv[])
{
	int error;
	Settings_t * settings = loadSettings(argc, argv);
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
	freeSettings(settings);
	return 0;
}
