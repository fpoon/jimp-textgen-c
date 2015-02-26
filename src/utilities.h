/*
 * utilities.h
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

int debugLog(const char * fmt, ...);

typedef enum {true, false} bool;

typedef struct LIST_ELEMENT
{
	struct LIST_ELEMENT * next;
	void * val;
} List_t;

List_t * addToList(List_t * list, void * val);
void * getFromList(List_t * list, int num);
void freeList(List_t * list);

#endif /* SRC_UTILITIES_H_ */