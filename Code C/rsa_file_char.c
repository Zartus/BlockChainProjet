/**
 * @file other_base64.c
 * @author antonin.miloudi@gmail.com
 * @brief Contient les fonctions qui permettent de crypter et de decrypter des fichiers
 * @version 1
 * @date 2020-03-04
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "rsa_header.h"

/**
 * @brief permet de crypter un fichier avec une lecture caractere par caractere et écrit dans un fichier de sortie
 *
 * @param inFilename Fichier Source
 * @param outFilename Fichier Destination
 * @param pubKey Clef publique
 * @param output_length Taille obtenue en sortie
 */
void RSAcryptFile(char *inFilename,char *outFilename,rsaKey_t pubKey,int *output_length){
    /*declaration des variables*/
    int ascii;
    char * strB64;
    uint64 asciiCrypt;

    /*Ouverture des fichiers*/
    FILE * pFichierIn = fopen(inFilename, "r");
    if(pFichierIn == NULL){
        fprintf(stderr,"[!] Erreur lecture de fichier d'entrée'");
        exit(1);
    }
    FILE * pFichierOut = fopen(outFilename, "w+");
    if(pFichierOut == NULL){
        fprintf(stderr,"[!] Erreur lecture de fichier de sortie");
        exit(2);
    }

    /*lecture du fichier d'entrée et ecriture dans le fichier de sortie*/
    while ((ascii = fgetc(pFichierIn)) != EOF){
        asciiCrypt = puissance_mod_n(ascii,pubKey.E,pubKey.N);
        strB64 = base64_encode(&asciiCrypt, sizeof(uint64),output_length);
        fprintf(pFichierOut,"%s",strB64);
        //fwrite(strB64, 1, *output_length, pFichierOut);
        free(strB64);
    }

    /*On ferme les fichiers ouvert*/
    fclose(pFichierOut);
    fclose(pFichierIn);
}

/**
 * @brief Permet de decrypter un fichier fait l'inverse de la fonction RSAfile_decrypt
 *
 * @param inFilename Designe le fichier Source
 * @param outFilename Designe le fichier Destination
 * @param privKey Clef privée
 * @param length Longeur des caractéres base64
 */
void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){
    /*declaration des variables*/
    char *blockB64 = malloc(length*sizeof(char));
    int devnull = length;
    int ascii,back,code = 1;
    int * asciiCrypt;

    /*Ouverture des fichiers*/
    FILE * pFichierIn = fopen(inFilename, "r");
    if(pFichierIn == NULL){
        fprintf(stderr,"[!] Erreur lecture de fichier d'entrée'");
        exit(1);
    }
    FILE * pFichierOut = fopen(outFilename, "w+");
    if(pFichierOut == NULL){
        fprintf(stderr,"[!] Erreur lecture de fichier de sortie");
        exit(2);
    }

    /*Ouverture et ecriture dans le fichier de sortie*/
    while((code = fread(blockB64,length*sizeof(char),1, pFichierIn)) != 0){
        asciiCrypt = base64_decode(blockB64,length*sizeof(char),&devnull);
        ascii = puissance_mod_n(*asciiCrypt,privKey.E,privKey.N);
        fprintf(pFichierOut,"%c",ascii);
        free(asciiCrypt);
    }

    /*On ferme les fichiers ouvert*/
    fclose(pFichierOut);
    fclose(pFichierIn);
}
