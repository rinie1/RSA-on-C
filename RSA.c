#include "RSA.h"

void PrimeNumbersGeneration(int* primeNumberFirst, int* primeNumberSecond)
{
    srand(time(NULL));

    int massOfPrimes[50];
    //counter for including prime numbers in massive
    int n = 0;

    //searching for prime numbers from 53 to 224
    for (int i = 53; i < 224; ++i){
        int k = 0;

        //cycle of divisions of number
        for (int j = 2; j < i; ++j){
            if (i % j == 0) ++k;
        }

        if (k == 0){
            //if number i is prime it would have zero divisions
            massOfPrimes[n] = i;
            ++n; //updating index for next prime number
        }
    }

    //random element from massive with prime numbers
    //massive lenght is n, not 50
    *primeNumberFirst = massOfPrimes[rand() % n];

    int buffer = massOfPrimes[rand() % n];

    //this block of code prevents numbers from being repeated
    while (buffer == *primeNumberFirst){
        int buffer = massOfPrimes[rand() % n];
    }

    //if numbers are different lets give him value
    *primeNumberSecond = buffer;
}

int EilerFunc(int p, int q)
{
    return (p - 1) * (q - 1);                   //Eiler function for fi creation
}

int OpenExpGeneration(int fi)
{
    srand(time(NULL));

    //cycle for searching open exp from odd numbers
    for (int i = 10001; i < fi; i = i + 2){

        //counter of divisiors
        int k = 0;

        //cycle to find common divisiors with fi
        for (int j = 2; j <= i; ++j){
            //if common divisior has been found
            if ((i % j == 0) && (fi % j == 0)) ++k;
        }

        //if k = 0, fi and i dont have any common divisiors
        if (k == 0) return i;
    }
}

int gcd(int firstNum, int secondNum)
{ //extended Evklid Algoritm
    int q, r;
    int x1 = 0;
    int x2 = 1;
    int y1 = 1;
    int y2 = 0;

    while(secondNum > 0){
        q = firstNum/secondNum; //integer division value
        r = firstNum % secondNum; //remainder of division

         //buffer value for x, y with remainder of division
        int x_buffer = x2 - q * x1;
        int y_buffer = y2 - q * y1;

        //going for next values for Evklid Algoritm
	    //for searching Largest Common Divisior
        firstNum = secondNum;
        secondNum = r;

        //same for x and y
        x2 = x1;
        x1 = x_buffer;

        y2 = y1;
        y1 = y_buffer;
    }

    //this is generation of close exp
    //because close exp is minimal odd number from x2 or y2
    if ((x2 > y2) && (y2 % 2 == 1)) return y2;
    else if ((x2 <= y2) && (x2 % 2 == 1)) return x2;
    //else return -1;
}

int RSAKeyGeneration(int* openK, int* privateK, int* commonK)
{
    int primeNumberFirst;
    int primeNumberSecond;

    PrimeNumbersGeneration(&primeNumberFirst, &primeNumberSecond);

    //first part of asymm key
    int productNumbers = primeNumberFirst * primeNumberSecond;

    //fi(productNumbers) from Eiler Finction
    int eiler = EilerFunc(primeNumberFirst, primeNumberSecond);
    //printf("%d\n", eiler);

    //getting open exp from function
    int openExp = OpenExpGeneration(eiler);

    //opened key is ready!

    //for private key we need to get close exp
    int closeExp = gcd(openExp, eiler);

    //private key is ready!


    if (((openExp * closeExp) % eiler) != 1) return -1; //if keys are wrong
    else{

        *openK = openExp;
        *privateK = closeExp;
        *commonK = productNumbers;

        return 0;
    }
}

int RSACrypting(int message, int e, int n) 
{

    int result = 1;

    for (int i = 0; i < e; i++) {
        result = (result * message) % n; //in every product while pow we can mod it
    }

    return result;

}
