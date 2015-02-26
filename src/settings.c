/*
 * settings.c
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#include <stdio.h>
#include <string.h>

#include "settings.h"
#include "utilities.h"

const char * SETTINGS_FAILURES[] = {
										"OK",
										"Niezdefiniowane wyjście => wyjście na stdout",
										"Nie podano plików wejściowych => zatrzymanie programu",
										"Nieznany argument => zatrzymanie programu",
										"Nie można otworzyć pliku => zatrzymanie programu",
										"Nieznany błąd => zatrzymanie programu"
};

static int argument(const char * arg)
{
	if (!strcmp(arg, "-i")) return INPUT;
	if (!strcmp(arg, "-o")) return OUTPUT;
	if (!strcmp(arg, "-g")) return GRAMS;
	if (!strcmp(arg, "-s")) return STATISTICS;

	return -1;
}

Settings_t * loadSettings(int argc, const char * argv[])
{
	int i,a;
	Settings_t * settings = malloc(sizeof(Settings_t));
	FILE * file;

	memset(settings, 0, sizeof(Settings_t));
	settings->output = stdout;
	settings->grams = 2;
	settings->statistics = false;

	for (i = 1; i < argc; i++)
	{
		a = argument(argv[i]);
		debugLog("Argument %s -> %s [%d]\n", argv[i], a < 0 ? "Błąd" : "OK", a);
		switch (a)
		{
		case INPUT:

			while (++i < argc && argv[i][0] != '-')
			{
				debugLog("Otwieranie pliku %s\n", argv[i]);
				file = fopen(argv[i], "r");
				if (file)
				{
					settings->input = (List_t *) addToList(settings->input, (void*)file);
				}
				else
				{
					settings->error_code = CANNOT_OPEN_FILE;
					settings->fatal      = true;
					return settings;
				}
			}
			i--;

			break;

		case OUTPUT:
			if (++i < argc && argv[i][0] != '-')
			{
				debugLog("Zapis do %s\n", argv[i]);
				settings->output = fopen(argv[i], "w");
				if (!settings->output)
				{
					settings->error_code = CANNOT_OPEN_FILE;
					settings->fatal      = true;
					return settings;
				}
			}
			else
				--i;
			break;

		case GRAMS:
			settings->grams = atoi(argv[++i]);
			debugLog("Ustawiono %d-gram.\n",settings->grams);
			break;

		case STATISTICS:
			settings->statistics = true;
			debugLog("Włączono wyświetlanie statystyki\n");
			break;

		default:
			settings->error_code = UNDEFINED_ARGUMENT;
			settings->fatal      = true;
			return settings;
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
