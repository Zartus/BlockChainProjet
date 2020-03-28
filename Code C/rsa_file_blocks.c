/**
 * @file rsa_file_blocks.c
 * @author Antonin MILOUDI (antonin.miloudi@gmail.com)
 * @brief 
 * @version 1
 * @date 2020-03-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "rsa_header.h"

uint64 RSAcrypt1BlockGmp(uint64 blockInt, rsaKey_t pubKey)
{
    mpz_t res;
    puissance_mod_n_gmp(res, blockInt, pubKey.E, pubKey.N);
    return mpz_get_ui(res);
}

uint64 RSAdecrypt1BlockGmp(uint64 blockInt, rsaKey_t privKey)
{
    mpz_t res;
    puissance_mod_n_gmp(res, blockInt, privKey.E, privKey.N);
    return mpz_get_ui(res);
}

void RSAfile_crypt(char *inFilename, char *outFilename, rsaKey_t pubKey)
{
    uchar block[BLOCK_SIZE];
    char *cryptedblock;
    int code;
    size_t output_l;
    uint B;
    uint64 blockgmp;
    /*Ouverture des fichiers */
    FILE *f_in = fopen(inFilename, "r");
    if (f_in == NULL)
    {
        perror(inFilename);
        exit(1);
    }
    FILE *f_out = fopen(outFilename, "w+");
    if (f_out == NULL)
    {
        perror(outFilename);
        exit(2);
    }

    /*Lecture du fichiefr d'entrée et cryptage dans le fichier de sortie*/
    while ((code = fread(block,sizeof(uchar), BLOCK_SIZE, f_in)) != 0)
    {
        B = convert_4byte2int((uchar *)block);
        blockgmp = RSAcrypt1BlockGmp((uint64)B, pubKey);
        cryptedblock = base64_encode((uchar *)&blockgmp, sizeof(blockgmp), &output_l);
        fprintf(f_out, "%s", cryptedblock);
        memset(block,0,BLOCK_SIZE);
        free(cryptedblock);
    }
    fclose(f_in);
    fclose(f_out);
}

void RSAfile_decrypt(char *inFilename, char *outFilename, rsaKey_t privKey)
{ 
    /*Variables declaration*/
    int output_l = 0;
    char blockB64[BLOCK_BASE_64];
    uint64 decrypt;
    int code = 1;
    uint64 *crypt;
    uchar* uncryptedblock=malloc(sizeof(uchar)*BLOCK_SIZE);

    /*open all files */
    FILE *f_in = fopen(inFilename, "r");
    
    if (f_in == NULL)
    {
        perror(inFilename);
        exit(1);
    }

    FILE *f_out = fopen(outFilename, "w+");
    
    if (f_out == NULL)
    {
        perror(outFilename);
        exit(2);
    }

    /*Lecture du fichier d'entrée et cryptage dans le fichier de sortie*/
    /*reding income file and crypting this file in the out file*/
    while ((code = fread(blockB64, sizeof(blockB64), 1, f_in)) != 0)
    {
        crypt = (uint64 *)base64_decode(blockB64, sizeof(blockB64), (size_t *)&output_l);
        decrypt = RSAdecrypt1BlockGmp(*crypt, privKey); /*le message est decrypté*/
        convertInt2uchar(decrypt, uncryptedblock);
        fprintf(f_out, "%s", uncryptedblock);
        free(crypt);
    }
    /*close open files*/
    fclose(f_in);
    fclose(f_out);
}