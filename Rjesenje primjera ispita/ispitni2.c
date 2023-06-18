/*************************************************************************************************
Napisati program koji iz datoteke čita dio teksta, riječ po riječ i unosi ih u red s prioritetom
(maksimalna duljina riječi 1024 znaka, prioritet=1 => riječ počinje samoglasnikom, prioritet=2 => 
riječ počinje suglasnikom;). Riječi u redu moraju biti sortirane po prioritetu. 

Iz tako kreiranog reda kreirati dvije datoteke, u prvoj će se nalaziti riječi sa prioritetom=1, a 
u drugoj riječi s prioritetom=2; s tim da su te riječi u datoteci zapisane sortirane po abecedi. 
***************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024

typedef struct red *pozicija;
struct red{
    
    char rijec[BUFFER];
    int prioritet;
    pozicija next;
};

int citaj_iz_datoteke(pozicija);
int ispis(pozicija);
int ispis_u_datoteke(pozicija);

int main(void)
{
    struct red head;
    head.next = NULL;
    
    printf("Citanje iz datoteke:\n");
    citaj_iz_datoteke(&head);
    
    printf("\nIspis:\n");
    ispis(&head);
    
    printf("\nIspis u datoteke:\n");
    ispis_u_datoteke(&head);
    
    return 0;
}
int citaj_iz_datoteke(pozicija p)
{
    FILE *iz = NULL;
    char *fileName = NULL;
    pozicija g;
    pozicija poc = p;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return 1;
    }
    else
    {
        printf("Ukucajte datoteku za citanje: ");
        scanf(" %s", fileName);
    }
    
    if(strchr(fileName, '.') == 0)
    {
        strcat(fileName, ".txt");
    }
    
    iz = fopen(fileName, "r");
    if(iz == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
    }
    
    while(!feof(iz))
    {
        g = (pozicija)malloc(sizeof(struct red));
        if(g == NULL)
        {
            printf("Alokacija neuspjesna!\n");
            
            return 1;
        }
        
        fscanf(iz, " %s", g->rijec);
        
        if(g->rijec[0] == 'a' || g->rijec[0] == 'i' || g->rijec[0] == 'e' || g->rijec[0]== 'o' || g->rijec[0] == 'u')
        {
            g->prioritet = 1;
        }
        else
        {
            g->prioritet = 2;
        }
        
        p = poc;
        while(p->next!=NULL && g->prioritet == 2)
        {
            p = p->next;
        }
        
        
        g->next = p->next;
        p->next = g;
        
    }
    
    
    fclose(iz);
    return 0;
}
int ispis(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf(" %s", p->rijec);
        p = p->next;
    }
    
    return 0;
}

int ispis_u_datoteke(pozicija p)
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
    
    printf("Ukucajte ime prve datoteke(prioritet 1): ");
    scanf(" %s", fileName1);
    
    printf("Ukucajte ime druge datoteke(prioritet 2): ");
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
    
    while(p->next!=NULL)
    {
        
        if(p->prioritet == 1)
        {
            fprintf(f1, "%s ", p->rijec);
        }
        else
        {
            fprintf(f2, "%s ", p->rijec);
        }
        
        
        p = p->next;
    }
    
    
    fclose(f1);
    fclose(f2);
    return 0;
}