/*
 * traintextanal.h
 *
 *  Created on: 24 mar 2015
 *      Author: mariusz
 */

#ifndef SRC_TRAINTEXTANAL_H_
#define SRC_TRAINTEXTANAL_H_

#include "database.h"

#define BUFFER_SIZE 64

int analyzeTrainingText(const char * path, Database_t * db);

#endif /* SRC_TRAINTEXTANAL_H_ */
