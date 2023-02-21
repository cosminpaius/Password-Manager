
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

struct pereche
{
    char *camp, *valoare;
};

void inlocuirecuvant(char sir[], char vechi[], char nou[])
{   char aux[25000], *p;
    int lgsir = strlen( sir ) + 1;
    p = strstr(sir, vechi);     //pointer pentru a cauta prima aparitie in sir
    int lgnou = strlen(nou), lgvec = strlen(vechi);
    while( p )
    {   
        if( isalpha(*(p - 1)) || isalpha(*( p + lgvec)) || isdigit(*(p - 1)) || isdigit(*(p + lgvec))) 
        {   
            p = strstr(p + 1, vechi);   //verificarea caracterului dinainte sau dupa cuvant
        }
        else
        if(lgvec > lgnou)   //cazuri separate pentru lungime   
        {
         strcpy(aux, p + lgvec);        //copiem ce este dupa cuvant
         strcpy(p, nou);                //adaugarea cuvantului
         strcpy(p + lgnou, aux);        //copiem ce era inainte dupa cuvant
         p = strstr(p + 1, vechi);      //cautam urmatoarea aparitie
         lgsir = strlen(sir) + 1;       
         
        }
        else
        {
         lgsir = lgsir + lgnou - lgvec;
         sir = (char*)realloc(sir, lgsir);
         strcpy(aux, p + lgvec);
         strcpy(p, nou);
         strcpy(p + lgnou, aux);
         p = strstr(p + 1, vechi);     
        }
    }
    free(p);
}


int main()
{   int N, i, l1, l2;
    struct pereche *v;
    char *propozitie, aux1[15000], aux2[15000];
    scanf("%d", &N);
    v = (struct pereche*)calloc(N, sizeof(struct pereche));
    for(i = 0 ; i <= N-1; i++)
    {   
        scanf("%s", aux1);      //citire in alte auxiliare pt a afla dimensiunea
        getchar();
        l1 = strlen( aux1 ) + 1;
        scanf("%s", aux2);
        getchar();
        l2 = strlen( aux2 ) + 1;
        v[i].camp = (char*)calloc(l1, sizeof(char));
        strcpy(v[i].camp, aux1);
        v[i].valoare = (char*)calloc(l2, sizeof(char));
        strcpy(v[i].valoare, aux2);
    }
    if(N == 0)          // aveam erori pt N=0, cred ca din cauza bufferului
        {
        getchar();
        fgets(aux1, 15000, stdin);       
        propozitie = (char*)calloc(strlen( aux1 ) + 1, sizeof(char));
        strcpy(propozitie, aux1);
        }
    else
    {
        fgets(aux1, 15000, stdin);
        propozitie = (char*)calloc(strlen( aux1 ) + 1, sizeof(char));
        strcpy(propozitie, aux1);
    }
    for(i = 0; i <= N-1; i++)
        { 
            inlocuirecuvant(propozitie, v[i].camp, v[i].valoare);
        }
    printf("%s", propozitie);
    return 0;
}