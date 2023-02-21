#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void generaresir(int seed, int lg, char aux[])
{   
    int i;
    srand(seed);
    for(i = 0 ; i <= lg - 1 ; i++)
         aux[i] = (rand() % (125 - 32 + 1) + 32);
    aux[lg] = '\0';
}

char* codificare0(char c)
{
    char *aux, nrc[4];
    static int apar[95] = {0} ;    //initializare cu 0 pentru ca nu luam in considerare si caracterul recent
    int i, ap, nrcif = 0, cop;
    aux = (char*)calloc(5, sizeof(char));
    ap = (int)c - 32;
    cop = apar[ap];     //copie pentru a calcula numarul cifrelor
    if(cop == 0)
        nrcif = 1;
    while(cop)
    {
        nrcif ++;
        cop = cop / 10;         //calculam nr de cif
    }
    cop = apar[ap];
    for(i = nrcif - 1 ; i >= 0; i --)
        {
        nrc[i] = cop % 10 + '0';        //trecem nr in sir de caractere
        cop = cop / 10;                 
        }
    nrc[nrcif] = '\0';
    aux[0] = c;
    strcpy(aux + 1, nrc);
    apar[ap]++;
    return aux;
}

int nrbiti(int x)
{
    int nrbiti = 0;         //functia de numarare gasita in breviar
    while (x) 
    {
        x = x & (x-1);          //sterge bitul "1" cel mai din dreapta
        nrbiti++;
    }
    return nrbiti;
}

char* codificare1(char c)
{   int nrbit;
    char *aux;
    aux = (char*)calloc(3, sizeof(char));
    c = c ^ 64;     // negare pozitia 6: 01000000
    c = c ^ 8;      // negare pozitia 3: 00001000
    nrbit = nrbiti((int)c);
    c = c | 32;     // sau cu masca
    c = c & 254;    // pt eliminarea ultimului bit facem & cu 11111110
    aux[0] = c;
    aux[1] = nrbit + '0';
    aux[2] = '\0';
    return aux;
}

char* codificare2(char c)
{   char *aux;
    int dist = 'a' - 'A';   
    aux = (char*)calloc(2, sizeof(char));
    if(c >= 'a' && c <= 'z')
        aux[0] = c - dist;
    else
        aux[0] = c;
    aux[1] = '\0';
    return aux;
}

void codificare( char* text, char* (*codif[])(char))
{
    int i, lg, cod;
    char *aux;
    lg = strlen(text);
    for(i = 0; i <= lg - 1; i++)
        {   
            cod = rand() % 3;           //avem 3 tipuri de codificare
            aux = codif[cod](text[i]);  //aux primeste rezultatul codificarii date de cod aplicata caracterului text[i]  
            printf("%s", aux);
            free(aux);
        }
    printf("\n");
}

int main()
{
    int seed, lg;
    scanf("%d %d", &seed, &lg);
    char* (*codif[3])(char) = {codificare0, codificare1, codificare2};
    char* text;
    text = (char*)calloc(lg + 1, sizeof(char));
    generaresir(seed, lg, text);
    codificare(text, codif);
    free(text);
}