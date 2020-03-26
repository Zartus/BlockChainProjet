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
    int lettre;
    char * strB64;
    uint64 Crypt;

    /*Ouverture des fichiers*/
    FILE * pFichierIn = fopen(inFilename, "r");
    if(pFichierIn == NULL){
        fprintf(stderr,"Probleme dans la lecture du fichier d'entrée\n");
        exit(1);
    }
    FILE * pFichierOut = fopen(outFilename, "w+");
    if(pFichierOut == NULL){
        fprintf(stderr,"Probleme dans la lecture du fichier de sortie\n");
        exit(2);
    }

    /*lecture du fichier d'entrée et ecriture dans le fichier de sortie*/
    while ((lettre = fgetc(pFichierIn)) != EOF){
        Crypt = puissance_mod_n(lettre,pubKey.E,pubKey.N);
        strB64 = base64_encode((uchar*)&Crypt, sizeof(uint64),(size_t*)output_length);
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
    int longeur = length;
    int lettre,code = 1;
    int * crypt;

    /*Ouverture des fichiers*/
    FILE * pFichierIn = fopen(inFilename, "r");
    if(pFichierIn == NULL){
        fprintf(stderr,"Probleme dans la lecture du fichier d'entrée\n");
        exit(1);
    }
    
    FILE * pFichierOut = fopen(outFilename, "w+");

    if(pFichierOut == NULL){
        fprintf(stderr,"Probleme dans la lecture du fichier de sortie\n");
        exit(2);
    }

    /*Ouverture et ecriture dans le fichier de sortie*/
    while((code = fread(blockB64,length*sizeof(char),1, pFichierIn)) != 0){
        crypt = (int*)base64_decode(blockB64,length*sizeof(char),(size_t*)&longeur);
        lettre = puissance_mod_n(*crypt,privKey.E,privKey.N);
        fprintf(pFichierOut,"%c",lettre);
        free(crypt);
    }

    /*On ferme les fichiers ouvert*/
    fclose(pFichierOut);
    fclose(pFichierIn);
}