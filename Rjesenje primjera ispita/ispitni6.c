/***********************************************************************************************************
Napisati program koji generira 20 slučajnih brojeva iz opsega 100 – 150 i njih spremitiu vezanu listu
i svakom od njih dodijeliti redni broj od 0-19.

a) Nakon toga treba generirati pet slučajnih brojeva iz opsega 0-19 (voditi računa da se ne pojavi isti
broj više puta) i elemente gornje liste s tim rednim brojem postaviti na početak liste. Ispisati te brojeve
te novu listu s rednim brojevima. Ako se izgeneriraju redni brojevi 4, 2, 6, 0, 5 prvo se na početak dodaje
element s rednim brojem 4, pa s rednim brojem 2, pa s 6…
b) Izmijeniti gornji zadatak tako da iz postojeće liste nova formira na način da se elementi iz postojeće liste
prebace po redoslijedu generiranja rednih brojeva.Ispisati te brojeve te novu listu s rednim brojevima.
**************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIMIT 50 

struct lista;
typedef struct lista *pozicija;
struct lista
{
	int br;
	int red_br;

	pozicija next;
};

int napravi_listu(pozicija);
int gen_br(int, int);
int napravi_novu(pozicija, pozicija);
int Ispis(pozicija);



int main(void)
{
	struct lista head, glava;
	head.next = NULL;
	glava.next = NULL;
	
	srand((unsigned)time(NULL));

	napravi_listu(&head);
	printf("\nIspis liste:\n");
	Ispis(&head);

	napravi_novu(&head, &glava);
	printf("\nIspis nove liste:\n");
	Ispis(&glava);


	return 0;
}

int gen_br(int min, int max)
{
	return rand() % (max - min) + min;
}

int napravi_listu(pozicija p)
{
	pozicija g = NULL;
	pozicija temp = p;
	int a = 0, i = 0;

	while (a <= 20)
	{
		g = (pozicija)malloc(sizeof(struct lista));
		if (g == NULL)
		{
			printf("Alokacija liste neuspjesna!\n");
			return 1;
		}

		g->br = gen_br(100, 150);
		printf("Izgenerirao se broj %d\n", g->br);

		p = temp;
		while (p->next != NULL && p->next->br != g->br)
		{
			p = p->next;
		}

		if (p->next != NULL && p->next->br == g->br)
		{
			free(g);
		}
		else
		{
			g->next = p->next;
			p->next = g;
			g->red_br = i;

			++a;
			++i;
		}
	}

	return 0;
}

int Ispis(pozicija p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%d %d\n", p->br, p->red_br);
		p = p->next;
	}


	return 0;
}

int napravi_novu(pozicija p, pozicija n)
{
	pozicija g = NULL;
	pozicija temp = p;
	pozicija poc = n;
	int a = 0;


	while (a <= 5)
	{
		g = (pozicija)malloc(sizeof(struct lista));
		if (g == NULL)
		{
			printf("Alokacija nove liste neuspjesna!\n");
			return 1;
		}
		g->red_br = gen_br(0, 19);
		printf("Izgenerirao se redni broj %d!\n", g->red_br);

		p = temp;
		while (p->next != NULL && p->next->red_br != g->red_br)
		{
			p = p->next;
		}

		if (p->next != NULL && p->next->red_br == g->red_br)
		{
			g->br = p->br;

			n = poc;

			while (n->next != NULL && n->next->br != g->br)
			{
				n = n->next;
			}

			if (n->next != NULL && n->next->br == g->br)
			{
				free(g);
			}
			else
			{
				g->next = n->next;
				n->next = g;

				++a;
			}
		}


	}




	return 0;
}


