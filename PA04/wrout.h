#ifndef __WROUT_H__
#define __WROUT_H__

#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

void finOut(FILE *output, Tnode *tree);

void freeTree(Tnode *tree);

#endif