#include "symm.h"

//random num generation for sym key
//max num is 127 because this is last index of ASCII table
int SymKeyGeneration()
{
    srand(time(NULL));
    return rand() % 127;
}

int symmCrypt(char* file_name, int key)
{

    FILE *fp;
    //reading the file
    fp = fopen(file_name, "r");

    char message[256];
	fgets(message, 256, fp);

    //writing in the same file
    fp = fopen(file_name, "w");

    for(int i = 0; i < strlen(message); ++i){

        //getting char's code from table of symbols
        wchar_t symb = message[i];
		int symbCode = (int) symb;

        //crypting char
		int pointer = (symbCode ^ key);

		wchar_t crypted = (wchar_t) pointer;

		fputc(crypted, fp);

	}

	fclose(fp);

	return 0;
}
