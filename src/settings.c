/*
 * settings.c
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#include <string.h>

#include "settings.h"
#include "utilities.h"

const char * SETTINGS_FAILURES[] = {
										"OK",
										"Niezdefiniowane wyjście => wyjście na stdout",
										"Nie podano plików wejściowych => zatrzymanie programu",
										"Nieznany argument => zatrzymanie programu",
										"Nieznany błąd => zatrzymanie programu"
};

static int argument(const char * arg)
{
	if (strcmp(arg, "-i")) return 0;
	if (strcmp(arg, "-o")) return 1;
	if (strcmp(arg, "-g")) return 2;
	if (strcmp(arg, "-s")) return 3;

	return -1;
}

Settings_t * loadSettings(int argc, const char * argv[])
{
	int i;
	Settings_t * settings = malloc(sizeof(Settings_t));
	FILE * file;

	memset(settings, 0, sizeof(Settings_t));

	for (i = 1; i < argc; i++)
	{
		switch (argument(argv[i]))
		{
		case 0:

			while (++i < argc && argv[i][0] != '-')
			{
				file = fopen(argv[i], "r");
				settings->input = (List_t *) addToList(settings->input, (void*)file);
			}

			break;

		case 1:
			if (++i < argc && argv[i][0] != '-')
				settings->output = fopen(argv[i], "w");
			else --i;
			break;

		case 2:
			settings->grams = atoi(argv[++i]);
			break;

		case 3:
			settings->statistics = true;
			break;

		default:
			return UNDEFINED_ARGUMENT;
		}
	}

	return settings;
}

void freeSettings(Settings_t * settings)
{
	FILE * file;
	int i = 0;

	while(file = (FILE*)getFromList(settings->input, i++))
		fclose(file);

	fclose(settings->output);

	freeList(settings->input);
	free(settings);
}
