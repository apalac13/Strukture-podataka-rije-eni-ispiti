/*******************************************************************************************************
Napisati program koji iz datoteke čita dio teksta, riječ po riječ i unosi u binarno stablo
pretraživanja (maksimalna duljina riječi 1024 znaka). Ispisati binarno stablo na „inorder“ način. 

Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve riječi koje počinju samoglasnikom, a u
drugoj sve riječi koje počinju suglasnikom. Riječi zapisane u datotekama moraju biti sortirane po abecedi. 
**********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024

typedef struct cvorStabla *stablo;
struct cvorStabla
{
    char rijec[BUFFER];
    stablo l;
    stablo d;
};

stablo citaj_iz_datoteke(stablo);
stablo dodaj(stablo, char *);
int Ispis(stablo);
int upis_u_datoteke(stablo);
int Upisi(stablo, char *, char *);


int main(void)
{
    stablo root = NULL;
    
    printf("Citanje iz datoteke:\n");
    root = citaj_iz_datoteke(root);
    
    printf("Ispis stabla:\n");
    Ispis(root);
    
    printf("\nUpis u datoteke:\n");
    upis_u_datoteke(root);
    
    
    return 0;
}
stablo citaj_iz_datoteke(stablo s)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    char ime[BUFFER];
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return 1;
    }
    printf("Ukucajte datoteku iz koje zelite procitat sadrzaj: ");
    scanf(" %s", fileName);
    
    if(strchr(fileName, '.') == 0)
    {
        strcat(fileName, ".txt");
    }
    
    fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }
    
    while(!feof(fp))
    {
        
        fscanf(fp, " %s", ime);
        s = dodaj(s, ime); 
    }
    
    
    fclose(fp);
    return s;
}

stablo dodaj(stablo s, char *ime)
{
    
    if(NULL == s)
    {
        s = (stablo)malloc(sizeof(struct cvorStabla));
        if(s == NULL)
        {
            printf("Alokacija neuspjesna\n");
        }
        
        strcpy(s->rijec, ime);
        s->l = NULL;
        s->d = NULL;
    }
    else if(strcmp(s->rijec, ime) > 0)
    {
        s->l = dodaj(s->l, ime);
    }
    else if(strcmp(s->rijec, ime) < 0)
    {
        s->d = dodaj(s->d, ime);
    }
    
    
    return s;
}
int Ispis(stablo s)
{
    
    if(s!=NULL)
    {
        Ispis(s->l);
        printf(" %s", s->rijec);
        Ispis(s->d);
    }
    
    
    return 0;
}

int upis_u_datoteke(stablo s)
{
    FILE *f1 = NULL;
    FILE *f2 = NULL;
    char *fileName1 = NULL;
    char *fileName2 = NULL;
    
    fileName1 = (char *)malloc(BUFFER*sizeof(char));
    fileName2 = (char *)malloc(BUFFER*sizeof(char));
    
    if(fileName1 == NULL || fileName2 == NULL)
    {
        printf("Alokacija neuspjesna\n");
        return 1;
    }
    
    printf("Ukucajte ime prve datoteke(samoglasnici): ");
    scanf(" %s", fileName1);
    
    printf("Ukucajte ime druge datoteke(suglasnici): ");
    scanf(" %s", fileName2);
    
    
    if(strchr(fileName1, '.')==0)
    {
        strcat(fileName1, ".txt");
    }
    
    if(strchr(fileName2, '.')==0)
    {
        strcat(fileName2, ".txt");
    }
    
    
    f1 = fopen(fileName1, "w");
    f2 = fopen(fileName2, "w");
    
    if(f1 == NULL || f2 == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }
    
    
    Upisi(s,f1, f2);
    
    
    fclose(f1);
    fclose(f2);
    return 0;
}
int Upisi(stablo s, char *f1, char *f2)
{
    
    if(s!=NULL)
    {
        Upisi(s->l, f1, f2);
        Upisi(s->d, f1, f2);
        
        if(s->rijec[0] == 'a' || s->rijec[0] == 'i' || s->rijec[0] == 'e' || s->rijec[0]== 'o' || s->rijec[0] == 'u')
        {
            fprintf(f1, "%s ", s->rijec);
        }
        else
        {
            fprintf(f2, "%s ", s->rijec);
        }
    }
    
    
    return NULL;
}


