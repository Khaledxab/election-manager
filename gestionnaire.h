#ifndef GET_H
#define GET_H

#include <stdio.h> 
#include <string.h> 

typedef struct user
{
    int id;
    char nom[15];
    char prenom[15];
    char sexe[5];
    int age[8];
    char adresse[50];
    char mail[15];
    char nationalite[15];
    int phone[15];
    char work[100];
}user;

int ajouter (char * filename, user u);
int modifier (char * filename, int id, user nouv );
int supprimer();
int rechercher()




#endif