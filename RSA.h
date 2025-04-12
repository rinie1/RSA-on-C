#ifndef RSA_HEADER
#define RSA_HEADER

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

void PrimeNumbersGeneration(int* primeNumberFirst, int* primeNumberSecond);
int EilerFunc(int p, int q);
int OpenExpGeneration(int fi);
int gcd(int firstNum, int secondNum);
int RSAKeyGeneration(int* openK, int* privateK, int* commonK);
int RSACrypting(int message, int e, int n);

#endif