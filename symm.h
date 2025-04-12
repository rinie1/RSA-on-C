#ifndef SYMM_HEADER
#define SYMM_HEADER

#include "time.h"
#include "wchar.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int SymKeyGeneration();
int symmCrypt(char* file_name, int key);

#endif