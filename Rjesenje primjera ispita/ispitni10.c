/***********************************************************************************************************
Napisati program koji iz datoteke čita popis studenata i sprema ih u vezanu listu.:

struct _student;
typedef struct _student *StudentNode;
typedef struct _student {

	int brojIndeksa;
	char *ime;
	char *prezime;
	int orderNum;

	StudentNode next;
} Student;

a) Prilikom spremanja studenta u vezanu listu potrebno je studentu dodijeliti orderNum, kao
slučajno generirani cijeli broj u rasponu od 1 do 1000. Ispisati listu.
b) Iz tako kreirane liste potrebno je kreirati novu vezanu listu u kojoj će studenti biti sortirani
po orderNum. Ispisati listu. NAPOMENA: Nije dozvoljena nova alokacija elementata pri unosu u novu
vezanu listu već je potrebno prebaciti čvorove iz postojeće liste.
c) Iz sortirane liste kreirati hash tablicu sa zasebnim redovima od 8 (osam) mjesta. Funkcija preslikavanja
ključ računa kao ostatak cjelobrojnog dijeljenja orderNum s ukupnim brojem elemenata tablice. Studenti s
izračunatim ključem se spremaju u binarno stablo po broju indexa.

NAPOMENA: Zatvoriti sve otvorene datoteke, pobrisati svu dinamički alociranu memoriju i mirnim putem prekinuti
rad programa. Programski kod napisati kozistentno, uredno te odvojeno u funkcije.
***************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BUFFER 1024
#define LIMIT 20

struct _student;
typedef struct _student *StudentNode;
typedef struct _student
{

	int brojIndeksa;
	char *ime;
	char *prezime;
	int orderNum;

	StudentNode next;
} Student;

int citaj_iz_datoteke(StudentNode);
int sl_br(int, int);
int Ispis(StudentNode);
int izmjena_liste(StudentNode);

int main(void)
{
	Student head;
	head.next = NULL;

	citaj_iz_datoteke(&head);
	printf("\nIspis liste:\n");
	Ispis(&head);

	/*izmjena_liste(&head);
	printf("Ispis nove liste:\n");
	Ispis(&head);*/


	return 0;
}


int citaj_iz_datoteke(StudentNode s)
{
	FILE *fp = NULL;
	char *fileName = NULL;
	char niz1[LIMIT], niz2[LIMIT];
	StudentNode g, temp = s;
	int x, y;


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("Alokacija datoteke neuspjesna!\n");
	}

	printf("Unesite ime datoteke za citanje: ");
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
		g = (StudentNode)malloc(sizeof(Student));
		if (g == NULL)
		{
			printf("Alokacija liste neuspjesna!\n");
			return 1;
		}

		fscanf(fp, "%d %s %s", &g->brojIndeksa, niz1, niz2);

		x = strlen(niz1);
		y = strlen(niz2);

		g->ime = (char *)malloc((x + 1) * sizeof(char));
		g->prezime = (char *)malloc((y + 1) * sizeof(char));

		strcpy(g->ime, niz1);
		strcpy(g->prezime, niz2);
		g->orderNum = sl_br(1, 1000);

		while (s->next != NULL)
		{
			s = s->next;
		}

		g->next = s->next;
		s->next = g;
	}


	fclose(fp);
	return 0;
}



int sl_br(int min, int max)
{
	return rand() % (max - min) + min;
}

int Ispis(StudentNode s)
{
	s = s->next;

	while (s != NULL)
	{
		printf("%d %s %s %d\n", s->brojIndeksa, s->ime, s->prezime, s->orderNum);
		s = s->next;
	}

	return 0;
}

int izmjena_liste(StudentNode s)
{
	s = s->next;
	StudentNode broj = s->next;
	StudentNode temp = broj;


	while (s != NULL)
	{
		while (broj != NULL)
		{
			if (s->orderNum > broj->orderNum)
			{

			}

			broj = broj->next;
		}

		broj = temp;
		s = s->next;
	}


	return 0;
}


