
#include <gest.h> 
 
 
int ajouter (char * filename, u)
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d %s %s %s %s %s %s %s %s %s\n",u.id,u.nom,u.prenom,u.sexe,u.age,u.adresse,u.mail,u.nationalite,u.phone,u.work);
        fclose(f);
        return 1;
    }
    return 0;
}

/* update user */
int modifier (char * filename, int id, user nouv )
{
    int tr=0;
    user u;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %s %s %s %s %s %s %s %s %s\n",&u.id,u.nom,u.prenom,u.sexe,u.age,u.adresse,u.mail,u.nationalite,u.phone,u.work)!=EOF)
        {
            if(u.id== id)
            {
                fprintf(f2,"%d %s %s %s %s %s %s %s %s %s\n",nouv.id,nouv.nom,nouv.prenom,nouv.sexe,nouv.age,nouv.adresse,nouv.mail,nouv.nationalite,nouv.phone,nouv.work);
                tr=1;
            }
            else
                fprintf(f2,"%d %s %s %s %s %s %s %s %s %s\n",u.id,u.nom,u.prenom,u.sexe,u.age,u.adresse,u.mail,u.nationalite,u.phone,u.work);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

/* delete user */
int supprimer()
{
    char id[15];
    scanf("%s",&id);
    supprimer(id);
    return 0;
}

/* search user */
int rechercher()
{
    char id[15];
    scanf("%s",&id);
    rechercher(id);
    return 0;
}
