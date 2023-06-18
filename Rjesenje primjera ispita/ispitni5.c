/************************************************************************************************************
Napisati program koji za tri različita predmeta čita ime i prezime studenta te njegovu ocjenu.
Podaci o svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati
vezanu listu i ispisati je.
a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri predmeta.
b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena studenata, sadrži
i njihovu prosječnu ocjenu iz ta tri predmeta.
**************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define LIMIT 50

typedef struct predmet *pozicija;
struct predmet
{
	char ime[LIMIT];
	char prezime[LIMIT];
	int ocjena;
	float prosjek_ocj;

	pozicija next;
};


int citaj_iz_datoteke(pozicija);
int Ispis(pozicija);
int polozeno(pozicija, pozicija, pozicija, pozicija);
int IspisPol(pozicija);


int main(void)
{
	struct predmet mat, fiz, ele, pol;
	mat.next = NULL;
	fiz.next = NULL;
	ele.next = NULL;
	pol.next = NULL;


	printf("Matematika:\n");
	citaj_iz_datoteke(&mat);
	Ispis(&mat);

	printf("\nFizika:\n");
	citaj_iz_datoteke(&fiz);
	Ispis(&fiz);


	printf("\nElektronika:\n");
	citaj_iz_datoteke(&ele);
	Ispis(&ele);

	printf("Studenti koji su polozili sve:\n");
	polozeno(&mat, &fiz, &ele, &pol);
	IspisPol(&pol);




	return 0;
}

int citaj_iz_datoteke(pozicija p)
{
	FILE *fp = NULL;
	char *fileName = NULL;
	pozicija g;

	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("Alokacija neuspjesna!\n");
		return 1;
	}

	printf("Unesite datoteku za citanje: ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return 1;
	}

	while (!feof(fp))
	{
		g = (pozicija)malloc(sizeof(struct predmet));
		if (g == NULL)
		{
			printf("Alokacija neuspjesna!\n");
			return 1;
		}

		fscanf(fp, " %s %s %d", g->ime, g->prezime, &g->ocjena);

		g->next = p->next;
		p->next = g;

	}

	fclose(fp);
	return 0;
}

int Ispis(pozicija p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}


	return 0;
}

int polozeno(pozicija m, pozicija f, pozicija e, pozicija p)
{
	m = m->next;
	f = f->next;
	e = e->next;

	pozicija glava1, g1, g2;
	pozicija temp1 = f;
	pozicija temp2 = e;

	glava1 = (pozicija)malloc(sizeof(struct predmet));
	glava1->next = NULL;


	while (m != NULL)
	{
		while (f != NULL)
		{
			if (strcmp(m->ime, f->ime) == 0 && strcmp(m->prezime, f->prezime) == 0)
			{
				g1 = (pozicija)malloc(sizeof(struct predmet));
				if (g1 == NULL)
				{
					printf("Alokacija neuspjesna!\n");
					return 1;
				}

				strcpy(g1->ime, m->ime);
				strcpy(g1->prezime, m->prezime);

				g1->prosjek_ocj = (float)(m->ocjena + f->ocjena);

				g1->next = glava1->next;
				glava1->next = g1;
			}
			f = f->next;
		}

		f = temp1;
		m = m->next;
	}


	while (g1 != NULL)
	{
		while (e != NULL)
		{
			if (strcmp(g1->ime, e->ime) == 0 && strcmp(g1->prezime, e->prezime) == 0)
			{
				g2 = (pozicija)malloc(sizeof(struct predmet));
				if (g2 == NULL)
				{
					printf("Alokacija neuspjesna!\n");
					return 1;
				}

				strcpy(g2->ime, e->ime);
				strcpy(g2->prezime, e->prezime);

				g2->prosjek_ocj = (float)(g1->prosjek_ocj + e->prosjek_ocj) / 3.0;

				g2->next = p->next;
				p->next = g2;
			}
			e = e->next;
		}

		e = temp2;
		g1 = g1->next;
	}


	return 0;
}

int IspisPol(pozicija p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%s %s %.2f\n", p->ime, p->prezime, p->prosjek_ocj);
		p = p->next;
	}


	return 0;
}

