/**
 * @file crypt_decrypt.c
 * @author Antonin MILOUDI antonin.miloudi@gmail.com
 * @brief Fonction qui permette de crypter un message ou de le décoder avec une clé publique et privée
 * @version 1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "rsa_header.h"

/**
 * @brief fonction qui permet de crypter un message avec une clé publique
 * 
 * @param msg le message à crypter
 * @param cryptedMsg le message décrypter
 * @param pubKey la clé publique pour crypter
 */
void RSAcrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t pubKey){
    
    int i=0;
    
    while(msg[i]!='\0'){
        cryptedMsg[i]=puissance_mod_n(msg[i],pubKey.E,pubKey.N);
        ++i;
    }
    
}

/**
 * @brief fonction qui permet de décrypter un message avec une clé privée
 * 
 * @param msg le message à décrypter
 * @param cryptedMsg le message décrypter
 * @param privKey la clé privé pour décrypter
 */
void RSAdecrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t privKey){

    int i=0;

    do{
        msg[i]=puissance_mod_n(cryptedMsg[i],privKey.E,privKey.N);
        ++i;
    }while(msg[i-1]!='\0');
}