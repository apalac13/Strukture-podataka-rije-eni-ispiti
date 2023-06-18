/******************************************************************************************************
Napisati program kojim se
a) Iz datoteke čitaju riječi i spremaju u vezanu listu na način da se riječi slažu po abecednom
redu obrnutom od abecednog reda. Zatim ispisati tu vezanu listu.

b) Iz generirane liste ispisati samo one riječi koje se nalaze zapisane u drugoj proizvoljnoj datoteci.
*******************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024
#define LIMIT 20

struct lista;
typedef struct lista *pozicija;
struct lista
{
	char rijec[LIMIT];
	pozicija next;
};

int citaj_iz_datoteke(pozicija);
int Ispis_liste(pozicija);
int citaj_iz_proizvoljne(pozicija);


int main(void)
{
	struct lista head;
	head.next = NULL;

	citaj_iz_datoteke(&head);
	printf("\nIspis liste:\n");
	Ispis_liste(&head);

	printf("\n");
	citaj_iz_proizvoljne(&head);

	return 0;
}

int citaj_iz_datoteke(pozicija p)
{
	FILE *fp = NULL;
	char *fileName = NULL;
	pozicija g = NULL;
	pozicija temp = p;


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("\nAlokacija datoteke neuspjesna!\n");
		return 1;
	}
	printf("Unesite ime datoteke: ");
	scanf("%s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\nGrekska pri otvaranju datoteke!\n");
		return 1;
	}

	while (!feof(fp))
	{
		g = (pozicija)malloc(sizeof(struct lista));
		if (g == NULL)
		{
			printf("\nAlokacija liste neuspjesna!\n");
			return 1;
		}

		fscanf(fp, "%s", g->rijec);

		p = temp;
		while (p->next != NULL && strcmp(p->next->rijec, g->rijec) > 0)
		{
			p = p->next;
		}

		if (p->next != NULL && strcmp(p->next->rijec, g->rijec) == 0)
		{
			free(g);
		}
		else
		{
			g->next = p->next;
			p->next = g;
		}

	}


	fclose(fp);
	return 0;
}

int Ispis_liste(pozicija p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%s ", p->rijec);
		p = p->next;
	}

	return 0;
}

int citaj_iz_proizvoljne(pozicija p)
{
	p = p->next;
	FILE *fp = NULL;
	char *fileName = NULL;
	char niz[LIMIT];
	pozicija temp = p;


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("\nAlokacija datoteke neuspjesna!\n");
		return 1;
	}
	printf("Unesite ime datoteke: ");
	scanf("%s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\nGrekska pri otvaranju datoteke!\n");
		return 1;
	}

	printf("\nIspis istih rijeci:\n");
	while (!feof(fp))
	{
		fscanf(fp, "%s", niz);

		p = temp;

		while (p != NULL && strcmp(p->rijec, niz) != 0)
		{
			p = p->next;
		}

		if (p != NULL && strcmp(p->rijec, niz) == 0)
		{
			printf("%s ", p->rijec);
		}

	}



	fclose(fp);
	return 0;
}

