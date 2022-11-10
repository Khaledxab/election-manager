#include"gest.h"

int main()
{
    gestionnaire u= {1,"mohamed","abdallah","m",20,"tunis","aa@aa.aa","tunisien","12345678","etudiant"};
    int a=ajouter("gestionaire.txt",u);
    if(a==1)
        printf("ajout avec succes");
    else
        printf("erreur");

    b = modifier("gestionaire.txt",1,u);
    if(b==1)
        printf("modification avec succes");
    else
        printf("erreur");

    c = supprimer("gestionaire.txt",1);
    if(c==1)
        printf("suppression avec succes");
    else
        printf("erreur");

    d = rechercher("gestionaire.txt",1);
    if(d==1)
        printf("recherche avec succes");
    else
        printf("erreur");

    return 0;
}