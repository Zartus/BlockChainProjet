#include "rsa_header.h"


void RSAcrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t pubKey){
    
    int i=0;
    
    while(msg[i]!='\0'){
        cryptedMsg[i]=puissance_mod_n(msg[i],pubKey.E,pubKey.N);
        ++i;
    }

}

void RSAdecrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t privKey){

    int i=0;

    do{
        msg[i]=puissance_mod_n(cryptedMsg[i],privKey.E,privKey.N);
        ++i;
    }while(msg[i-1]!='\0');
}