#include <stdio.h>
#include <string.h>

int text(char sir[])
{
    int i = 0, ok = 1;
    while( sir[i] )     
    {
        if(!(sir[i] >= 'A' && sir[i] <= 'Z') && !(sir[i] >= 'a' && sir[i] <= 'z'))     
            ok = 0;     //vericarea caracterului (daca e altceva in afara de litera)
        i++;
    }
    if(ok == 0)
        return 0;
    return 1;

}

int main()
{   int n, m, i, j, k, distanta, pozitie, suma;
    char cheie[13501], clar[13502], copie[13501];
    char abc[53]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    scanf("%s %s", cheie, clar);
    n = strlen(cheie);
    m = strlen(clar);
    strcpy(copie, cheie);
    if(text(cheie) && text(clar))
        {
        while(n < m)
        {
            strcat(cheie, copie);
            n = strlen(cheie);      //copiez cheia de cate orie este nevoie
        }
        cheie[m]='\0';              //adaugam NULL pe pozitia lungimii textului clar
        for(i = 0; i <= m-1; i++)
            {
            for(j = 0; j <= 51 ; j++)
                if(cheie[i] == abc[j])
                    distanta = j;       //calculez distanta fata de a
            for(k = 0; k <= 51 ; k++)
                if(clar[i] == abc[k])
                    pozitie = k;        //calculez pozitia caracterului in vectorul abc
            suma = (distanta + pozitie) % 52; //sunt 52 de litere in alfabet
            clar[i] = abc[suma];
        }
        printf("%s", clar);
        printf("\n");
    }
    else
        printf("INVALID\n"); 
} 