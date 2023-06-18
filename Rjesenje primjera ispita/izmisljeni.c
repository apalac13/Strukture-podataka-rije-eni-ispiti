/*********************************************************************************************
Moj osmisljeni zadatak: imamo vezanu listu gradova koja sadrzi pokazivac na strukturu
osoba koja sadrzi ime prezime i broj telefona. Podatke citamo iz datoteke "brojevi.txt"
Ako su gradovi isti spremamo ih u vezanu osoba koje ce buti sortirane po prezimenu pa po imenu a
ako su isti onda po brojevima. Ispisati listu i pobrisati svu dinamicki alociranu memoriju!
**********************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (256)


struct _person;
typedef struct _person *PersonPosition;
typedef struct _person
{
	char firstName[MAX_NAME];
	char lastaName[MAX_NAME];
	int number;

	PersonPosition sljedeci;

} Person;


struct _city;
typedef struct _city *CityPosition;
typedef struct _city
{
	char city[MAX_NAME];

	Person person;
	CityPosition next;

} City;

int read_from_file(CityPosition, char *);
int delete_city(CityPosition);
int delete_people(PersonPosition);

int create_list_city(CityPosition, char *, char *, char *, int);
int print_city(CityPosition);

int create_people(PersonPosition, char *, char *, int);
int print_people(PersonPosition);


int main(void)
{

	City head;
	head.next = NULL;
	char fileName[MAX_NAME] = { 0 };


	printf("Unesite datoteku za citanje osoba-> ");
	scanf(" %s", fileName);
	read_from_file(&head, fileName);

	print_city(&head);
	delete_city(&head);

	return 0;
}

int read_from_file(CityPosition c, char *fileName)
{
	FILE *fp = NULL;
	char ime[MAX_NAME], prezime[MAX_NAME], grad[MAX_NAME];
	int broj;



	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}


	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\nGreska pri otvaranju datoteke!\n");
		return 1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %d", ime, prezime, grad, &broj);
		create_list_city(c, ime, prezime, grad, broj);

	}



	fclose(fp);
	return 0;
}

int create_list_city(CityPosition c, char *ime, char *prezime, char *grad, int broj)
{
	CityPosition g = NULL;
	CityPosition temp = c;

	g = (CityPosition)malloc(sizeof(City));
	if (g == NULL)
	{
		printf("\nAlokacija liste neuspjesna!\n");
		return 1;
	}

	strcpy(g->city, grad);


	c = temp;
	while (c->next != NULL && strcmp(c->next->city, g->city) < 0)
	{
		c = c->next;
	}


	if (c->next != NULL && strcmp(c->next->city, g->city) == 0)
	{
		create_people(&c->next->person, ime, prezime, broj);
		free(g);
	}
	else
	{
		g->next = c->next;
		c->next = g;
		create_people(&c->next->person, ime, prezime, broj);
	}


	return 0;
}

int create_people(PersonPosition p, char *ime, char *prezime, int broj)
{

	PersonPosition g = NULL;
	PersonPosition temp;

	/*
	if(p == NULL)
	{
		p = (PersonPosition)malloc(sizeof(Person));
		p->sljedeci = NULL;
	}
	*/


	g = (PersonPosition)malloc(sizeof(Person));
	if (g == NULL)
	{
		printf("\nAlokacija osoba neuspjena\n");
		return 1;
	}

	strcpy(g->firstName, ime);
	strcpy(g->lastaName, prezime);
	g->number = broj;
	temp = p;

	p = temp;
	while (p->sljedeci != NULL && strcmp(p->sljedeci->lastaName, g->lastaName) < 0)
	{
		p = p->sljedeci;
	}

	if (p->sljedeci != NULL && strcmp(p->sljedeci->lastaName, g->lastaName) == 0)
	{
		while (p->sljedeci != NULL && strcmp(p->sljedeci->lastaName, g->lastaName) == 0 && strcmp(p->sljedeci->firstName, g->firstName) < 0)
		{
			p = p->sljedeci;
		}

		if (p->sljedeci != NULL && strcmp(p->sljedeci->firstName, g->firstName) == 0 && strcmp(p->sljedeci->lastaName, g->lastaName) == 0)
		{
			while (p->sljedeci != NULL && strcmp(p->sljedeci->firstName, g->firstName) == 0 && strcmp(p->sljedeci->lastaName, g->lastaName) == 0 && p->sljedeci->number < g->number)
			{
				p = p->sljedeci;
			}

		}

	}

	g->sljedeci = p->sljedeci;
	p->sljedeci = g;

	return 0;
}

int print_city(CityPosition c)
{
	c = c->next;

	while (c != NULL)
	{
		printf("%s\n", c->city);
		if (&c->person != NULL)
		{
			print_people(&c->person);
		}
		printf("\n");
		c = c->next;
	}

	return 0;
}

int print_people(PersonPosition p)
{
	p = p->sljedeci;

	while (p != NULL)
	{
		printf("%s %s %d\n", p->firstName, p->lastaName, p->number);
		p = p->sljedeci;
	}

	return 0;
}

int delete_city(CityPosition c)
{

	CityPosition temp = NULL;

	while (c->next != NULL)
	{
		delete_people(&c->next->person);
		temp = c->next;
		c->next = temp->next;
		free(temp);

	}

	return 0;
}

int delete_people(PersonPosition p)
{

	PersonPosition temp = NULL;

	while (p->sljedeci != NULL)
	{
		temp = p->sljedeci;
		p->sljedeci = temp->sljedeci;
		free(temp);
	}

	return 0;
}
