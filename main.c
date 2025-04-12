#include "symm.h"
#include "RSA.h"

int main(int argc, char* argv[]) {

    //if user wants to crypt file and keys
    if (strcmp(argv[1], "-en") == 0){

        int symKey = SymKeyGeneration();
        //crypting message from file
        symmCrypt(argv[2], symKey);

        //list of RSA keys
        int openKey;
        int privateKey;
        int commonPartOfKeys;

        //program will be finding correct keys if they are wrong
        while (RSAKeyGeneration(&openKey, &privateKey, &commonPartOfKeys) == -1){
            RSAKeyGeneration(&openKey, &privateKey, &commonPartOfKeys);
        }

        //encrypting symmetry key
        int encrypt = RSACrypting(symKey, openKey, commonPartOfKeys);

        printf("Message has been crypted. Check file!\n");

        //opening keys.txt file, if file not exist program will create file
        FILE *fpk;
        fpk = fopen("keys.txt", "w");

        //file structure:
        //first string is encrypted symmetry key
        //second string is open key of RSA
        //third str is private key of RSA
        fprintf(fpk, "%d\n%d %d\n%d %d", encrypt, openKey, commonPartOfKeys, privateKey, commonPartOfKeys);
        printf("Keys has been added to 'keys.txt' file.\n");

        fclose(fpk);
    }

    //if user wants to decrypt file
    //arguments are: -de file_name file_with_keys
    else if(strcmp(argv[1], "-de") == 0){

        FILE *fp;
        fp = fopen(argv[3], "r");

        int buffer;
        int encryptedKey;
        int privateKey;
        int commonPartOfKeys;

        fscanf(fp, "%d\n%d %d\n%d %d", &encryptedKey, &buffer, &commonPartOfKeys, &privateKey, &buffer);

        fclose(fp);

        int decryptKey = RSACrypting(encryptedKey, privateKey, commonPartOfKeys);

        symmCrypt(argv[2], decryptKey);

        printf("Message has been decrypted. Check file!\n");
    }

    return 0;
}
