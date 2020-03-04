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
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief permet de crypter un fichier
 * 
 * @param inFilename Fichier Source
 * @param outFilename Fichier Destination
 * @param pubKey Clef publique
 * @param output_length Taille obtenue en sortie
 */
void RSAcryptFile(char *inFilename,char *outFilename,rsaKey_t pubKey,int *output_length){

  //varibale
  FILE* fichierIn;
  FILE* FichierOut;
  *output_length = 0;
  int lettre_courante;
  uint64 cryptedChar;
  char* char64;


  //ouverture des fichiers
  if((fichierIn = fopen(inFilename,"r")) == NULL) {
    fprintf(stderr,"Erreur d'ouverture en lecture du fichier %s\n",inFilename);
    exit(1);
  }

  if((FichierOut = fopen(outFilename,"w+")) == NULL){
    fprintf(stderr,"Erreur d'ouverture en écriture du fichier %s\n",outFilename);
    fclose(fichierIn);
    exit(2);
  }


  while ( ! feof(fichierIn)){
    lettre_courante = fgetc(fichierIn);
    if(lettre_courante >= 0 && lettre_courante <= 127){
     
      //chiffrage et conversion
      cryptedChar = puissance_mod_n(lettre_courante,pubKey.E,pubKey.N);
      char64 = base64_encode(&cryptedChar,sizeof(uint64),output_length);
      fputs(char64,FichierOut);

      //liberation de la memoire donner par base64_encode
      free(char64);
    }

  }


  fclose(fichierIn);
  fclose(FichierOut);
}

/**
 * @brief Permet de decrypter un fichier
 * 
 * @param inFilename Designe le fichier Source
 * @param outFilename Designe le fichier Destination
 * @param privKey Clef privée
 * @param length Longeur des caractéres base64
 */
void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){

  //====================
  //      VARIABLES
  //====================

  FILE* src;
  FILE* dst;
  unsigned char charConv;
  uint64 *cryptedChar;
  char* char64;
  size_t taille;
  char64 = malloc(sizeof(char) * length);

  //=============================
  //    OUVERTURE DES FICHIERS
  //=============================

  /*Ouverture du fichier inFilename avec vérification*/
  if((src = fopen(inFilename,"r")) == NULL) {
    fprintf(stderr,"Erreur d'ouverture en lecture du fichier %s\n",inFilename);
    exit(1);
  }

  /*Ouverture du fichier outFilename avec vérification*/
  if((dst = fopen(outFilename,"w+")) == NULL){
    fprintf(stderr,"Erreur d'ouverture en écriture du fichier %s\n",outFilename);
    fclose(src);
    exit(2);
  }

  //lecture ligne par ligne
  while (fgets(char64,length+1,src) && ! feof(src)){

    //decodage et decryptage
    cryptedChar = base64_decode(char64,length,&taille);
    charConv = puissance_mod_n(*cryptedChar,privKey.E,privKey.N);

    //ecriture dans le fichier de sortie
    fputc(charConv,dst);

    //liberation de la mémoire
    free(cryptedChar);
  }

  free(char64);
  fclose(src);
  fclose(dst);
}