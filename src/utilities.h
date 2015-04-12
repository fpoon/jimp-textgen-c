/*
 * utilities.h
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#define STRING_BASE_SIZE 16
#define STRING_MULTIPLIER 2

int debugLog(const char * fmt, ...);

typedef enum {true, false} bool;

typedef struct LIST_ELEMENT
{
	struct LIST_ELEMENT * next;
	void * val;
} List_t;

typedef struct STRING
{
	char * str;
	int size;
	int length;
} String_t;

List_t * addToList(List_t * list, void * val);
void * getFromList(List_t * list, int num);
void freeList(List_t * list);
char * searchStringList(List_t * list, char * str);
String_t * addToString(String_t * str, const char * word);
#endif /* SRC_UTILITIES_H_ */
