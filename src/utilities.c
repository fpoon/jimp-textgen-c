/*
 * utilities.c
 *
 *  Created on: 25 lut 2015
 *      Author: mariusz
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "utilities.h"

int debugLog(const char * fmt, ...)
{
	int ret = 0;
#ifdef _DEBUG
	va_list args;
	va_start(args, fmt);
	ret = vfprintf(stderr, fmt, args);
	va_end(args);
	//fflush(stderr);
#endif
	return ret;
}

List_t * addToList(List_t * list, void * val)
{
	//debugLog("L: %p \n", list);
	int i = 0;
	List_t * ret = list;
	List_t * elem  = (List_t*) malloc(sizeof(List_t));
	//debugLog("%p -> ", elem);

	elem->next = NULL;
	elem->val = val;

	if (list == NULL)
	{
		return elem;
	}

	while(list->next != NULL)
	{
		list = list->next;
		i++;
	}

	list->next = elem;

	return ret;
}

char * searchStringList(List_t * list, char * str)
{
	if (!list)
		return NULL;

	while (list)
	{
		if(!strcmp(list->val, str))
			return (char*)list->val;
		list = list->next;
	}
	return NULL;
}


void * getFromList(List_t * list, int num)
{
	int i = 0;

	if (list == NULL) return NULL;

	while (list->next)
	{
		if (i == num) return list->val;

		list = list->next;
		i++;
	}

	return NULL;
}

void freeList(List_t * list)
{
	List_t * next = next = list->next;

	while (next)
	{
		next = list->next;
		if (list->val)
			free(list->val);
		free(list);
		list = next;
	}
}
