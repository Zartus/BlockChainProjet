/**
 * @file rsa_file_blocks.c
 * @author Antonin MILOUDI (antonin.miloudi@gmail.com)
 * @brief 
 * @version 1
 * @date 2020-03-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "rsa_header.h"

/**
 * @brief Permet de faire le chiffrage en utilisant GMP pour un block de 4 octets
 * 
 * @param blockInt : le blocks à chiffrer
 * @param pubKey : la clé publique
 * @return uint64 : le résultats de la fonction
 */
uint64 RSAcrypt1BlockGmp(uint64 blockInt, rsaKey_t pubKey)
{
    mpz_t res;
    puissance_mod_n_gmp(res, blockInt, pubKey.E, pubKey.N);
    return mpz_get_ui(res);
}

/**
 * @brief Permet de faire le déchiffrage en utilisant GMP
 * 
 * @param blockInt : le block à décrypter
 * @param privKey : la clé privée à utiliser
 * @return uint64 : le résultats de la fonction
 */
uint64 RSAdecrypt1BlockGmp(uint64 blockInt, rsaKey_t privKey)
{
    mpz_t res;
    puissance_mod_n_gmp(res, blockInt, privKey.E, privKey.N);
    return mpz_get_ui(res);
}

/**
 * @brief : chiffre un message par blocs depuis un fichier, codage en base64 et écriture dans un fichier.
 * 
 * @param inFilename : fichier d'entrée
 * @param outFilename : fichier de sortie
 * @param pubKey : clé publique à utiliser pour le cryptage
 */
void RSAfile_crypt(char *inFilename, char *outFilename, rsaKey_t pubKey)
{
    /*Variables declaration*/
    uchar block[BLOCK_SIZE];
    char *cryptedblock;
    int code;
    size_t output_l;
    uint B;
    uint64 blockgmp;

    /*opening files */
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
        fclose(f_in);
        exit(2);
    }

    /*reding income file and crypting in the out file*/
    while ((code = fread(block, sizeof(uchar), BLOCK_SIZE, f_in)) != 0)
    {
        B = convert_4byte2int((uchar *)block);
        blockgmp = RSAcrypt1BlockGmp((uint64)B, pubKey);
        cryptedblock = base64_encode((uchar *)&blockgmp, sizeof(blockgmp), &output_l);
        fprintf(f_out, "%s", cryptedblock);
        memset(block, 0, BLOCK_SIZE);
        free(cryptedblock);
    }

    /*closing files*/
    fclose(f_in);
    fclose(f_out);
}

/**
 * @brief dechiffre un message par blocs depuis un fichier, codage en base64 et écriture dans un fichier.
 * 
 * @param inFilename : fichier d'entrer
 * @param outFilename : fichier de sortie
 * @param privKey : clé privée à utiliser pour le décryptage
 */
void RSAfile_decrypt(char *inFilename, char *outFilename, rsaKey_t privKey)
{
    /*Variables declaration*/
    size_t output_l = 0;
    char blockB64[BLOCK_BASE_64];
    uint64 decrypt;
    int code = 1;
    uint64 *crypt;
    uchar uncryptedblock[BLOCK_SIZE + 1] = {0};

    /*opening files */
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
        fclose(f_in);
        exit(2);
    }

    /*reding income file and decrypting in the out file*/
    while ((code = fread(blockB64, sizeof(blockB64), 1, f_in)) != 0)
    {
        crypt = (uint64 *)base64_decode(blockB64, sizeof(blockB64), &output_l);
        decrypt = RSAdecrypt1BlockGmp(*crypt, privKey); /*le message est decrypté*/
        convertInt2uchar(decrypt, uncryptedblock);
        fprintf(f_out, "%s", uncryptedblock);
        free(crypt);
    }

    /*closing files*/
    fclose(f_in);
    fclose(f_out);
}