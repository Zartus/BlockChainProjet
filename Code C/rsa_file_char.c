#include "rsa_header.h"

void RSAcryptFile(char *inFilename,char *outFilename,rsaKey_t pubKey,int *output_length){
    FILE* fichier_in = NULL;
    FILE* fichier_out = NULL;

    fichier_in=fopen(inFilename,"r+");
    fichier_out=fopen(outFilename,"w+");
    
    unsigned char *msg = malloc(100*sizeof(unsigned char));
    int i=0;
    uint64* cryptedMsg;

    if(fichier_in==NULL)
    {
        fprintf(stderr,"Probléme dans l'ouverture du fichier d'entrée");
        exit(1);
    }
    else if(fichier_out==NULL)
    {
        fprintf(stderr,"Probleme dans le fichier de sortie");
        exit(1);
    }
    else
    {
        int caractereActuel = 0;
        while((caractereActuel = fgetc(fichier_in))!=EOF)
        {
            if(i%100==0){
                msg=realloc(msg,((i/100)+1)*100*sizeof(unsigned char));
            }
            msg[i]=caractereActuel;
            ++i;
        }
        cryptedMsg=malloc(i*sizeof(uint64));
        RSAcrypt(msg,cryptedMsg,pubKey);
        fprintf(fichier_out,"%s",base64_encode((unsigned char*)cryptedMsg,(size_t)i*sizeof(uint64),(size_t*)output_length));
    }

    free(msg);
    free(cryptedMsg);
    fclose(fichier_in);
    fclose(fichier_out);
}

void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){
    FILE* fichier_in = NULL;
    FILE* fichier_out = NULL;

    fichier_in=fopen(inFilename,"r+");
    fichier_out=fopen(outFilename,"w+");
    
    char * cryptedMsg = malloc(100*sizeof(unsigned char));

    int i=0;
    //unsigned char *msg;
    

    if(fichier_in==NULL)
    {
        fprintf(stderr,"Probléme dans l'ouverture du fichier d'entrée");
        exit(1);
    }
    else if(fichier_out==NULL)
    {
        fprintf(stderr,"Probleme dans le fichier de sortie");
        exit(1);
    }
    else
    {
        int caractereActuel = 0;
        while((caractereActuel = fgetc(fichier_in))!=EOF)
        {
            if(i%100==0){
                cryptedMsg=realloc(cryptedMsg,((i/100)+1)*100*sizeof(char));
            }
            cryptedMsg[i]=caractereActuel;
            ++i;
        }

        int test253;
        uint64 *intRes2 = base64_decode(cryptedMsg,length*sizeof(uint64),&test253);
        printf("\n==%d\n",test253);
        printf("\n==%d\n",strlen(intRes2));
        printf("\n\n");
        //printf("\n");
        //msg=malloc(i*sizeof(unsigned char));
        //RSAdecrypt(msg,cryptedMsg,privKey);
        char *truc=malloc(test253*sizeof(char));
        RSAdecrypt(truc,intRes2,privKey);
        fprintf(fichier_out,"%s",truc);
    }

    //free(msg);
    free(cryptedMsg);
    fclose(fichier_in);
    fclose(fichier_out);
}