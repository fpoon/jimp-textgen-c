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

Settings_t * settings;

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
	if (!strcmp(arg, "-l")) return LENGTH;
	if (!strcmp(arg, "-g")) return GRAMS;
	if (!strcmp(arg, "-s")) return STATISTICS;
	if (!strcmp(arg, "-db")) return DATABASE;

	return -1;
}

Settings_t * loadSettings(int argc, const char * argv[])
{
	int i,a;
	Settings_t * _settings = malloc(sizeof(Settings_t));
	FILE * file;

	memset(_settings, 0, sizeof(Settings_t));
	_settings->output = NULL;
	_settings->grams = 2;
	_settings->statistics = false;
	_settings->length = 100;

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
					_settings->input = (List_t *) addToList(_settings->input, (void*)argv[i]);
					fclose(file);
				}
				else
				{
					_settings->error_code = CANNOT_OPEN_FILE;
					_settings->fatal      = true;
					fclose(file);
					return _settings;
				}
			}
			i--;

			break;

		case OUTPUT:
			if (++i < argc && argv[i][0] != '-')
			{
				debugLog("Zapis do %s\n", argv[i]);
				_settings->output = argv[i];
			}
			else
				--i;
			break;

		case DATABASE:
			if (++i < argc && argv[i][0] != '-')
			{
				debugLog("Baza danych %s\n", argv[i]);
				_settings->database = argv[i];
			}
			else
				--i;
			break;

		case GRAMS:
			_settings->grams = atoi(argv[++i]);
			debugLog("Ustawiono %d-gram.\n",_settings->grams);
			break;

		case LENGTH:
				_settings->length = atoi(argv[++i]);
				debugLog("Ustawiono długość %d.\n",_settings->length);
				break;

		case STATISTICS:
			_settings->statistics = true;
			debugLog("Włączono statystykę\n");
			break;

		default:
			_settings->error_code = UNDEFINED_ARGUMENT;
			_settings->fatal      = true;
			return _settings;
		}
	}

	return _settings;
}

void freeSettings(Settings_t * settings)
{
	FILE * file;
	int i = 0;

	/*while(file = (FILE*)getFromList(settings->input, i++))
		fclose(file);*/

	/*fclose(settings->output);

	freeList(settings->input);*/
	free(settings);
}
