/*
 * settings.h
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#ifndef SRC_SETTINGS_H_
#define SRC_SETTINGS_H_

#include <stdio.h>

#include "utilities.h"

extern const char * SETTINGS_FAILURES[];

typedef enum
{
	OK,
	UNDEFINED_OUTPUT,
	UNDEFINED_INPUT,
	UNDEFINED_ARGUMENT,
	CANNOT_OPEN_FILE,
	UNKNOWN_FAILURE
} SETTINGS_ERROR_CODES;

typedef enum
{
	INPUT,
	OUTPUT,
	LENGHT,
	GRAMS,
	STATISTICS,
	DATABASE,
	DATABASE_OUTPUT
} ARGUMENTS;

typedef struct
{
	int            error_code;
	bool           fatal;
	List_t *       input;
	const char *   output;
	int            grams;
	bool           statistics;
	const char *   database;
	const char *   odatabase;
} Settings_t;

Settings_t * loadSettings(int argc, const char * argv[]);

void freeSettings(Settings_t * settings);

#endif /* SRC_SETTINGS_H_ */
