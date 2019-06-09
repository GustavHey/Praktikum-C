#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "komplex.h"
void eingabe(struct komplex *);
int speichern(struct komplex*, struct komplex*, struct komplex*);
void ausgabe(int);
void change(int);


int main()
{
	struct komplex z1, z2, z3;
	int abruf = 0;
	int aendern = 0;
	int abbruch = 11;

	eingabe(&z1);
	eingabe(&z2);
	eingabe(&z3);
	abbruch = speichern(&z1, &z2, &z3);

	if (abbruch == 11)
		return EXIT_FAILURE;

	do
	{
		printf("\n\nMoechten sie eine Zahl abrufen? (0 fuer keine, sonst 1,2,3)");
		scanf("%i", &abruf);

		if (abruf < 0 || abruf >3)
		{
			printf("Ungueltige Wahl");
		}

	} while (abruf < 0 || abruf >3);
	
	if (abruf >= 1 && abruf <= 3)
	{
		ausgabe(abruf);
	}


	do
	{
		printf("\n\nMoechten sie eine Zahl aendern? (0 fuer keine, sonst 1,2,3)");
		scanf("%i", &aendern);

		if (abruf < 0 || abruf >3)
		{
			printf("Ungueltige Wahl");
		}
	} 
	while (aendern < 0 || aendern >3);

	if (abruf >= 1 && abruf <= 3)
	{
		change(aendern);
	}


	printf("\nDas Programm ist nun beendet.\n\n");

	return EXIT_SUCCESS;
}

void eingabe(struct komplex *zahl)
{
	double var1 = 0;
	double var2 = 0;
	printf("Geben sie den Realteil ein: ");
	scanf("%lf", &var1);
	zahl->real = var1;

	printf("Geben sie den Imaginaerteil ein: ");
	scanf("%lf", &var2);
	printf("\n\n");
	zahl->imag = var2;

}

int speichern(struct komplex *z1, struct komplex *z2, struct komplex *z3)
{
	FILE *datei;

	if ((datei = fopen("X:/test.txt", "wb")) != NULL)
	{
		fprintf(datei, "%lf", z1->real);
		fprintf(datei, "%lf", z1->imag);
		fprintf(datei, "%lf", z2->real);
		fprintf(datei, "%lf", z2->imag);
		fprintf(datei, "%lf", z3->real);
		fprintf(datei, "%lf", z3->imag);
		
		//fwrite(z1, sizeof(struct komplex), 1, datei);
		//fwrite(z2, sizeof(struct komplex), 1, datei);
		//fwrite(z3, sizeof(struct komplex), 1, datei);
	}
	else
	{
		printf("Fehler beim Oeffnen der Zieldatei.\n\n");
		return 11;
	}
	
	fclose(datei);
	return 0;
}

void ausgabe(int abruf)
{
	struct komplex ausgabe;
	FILE *datei;
	int offset = ((abruf-1) * (sizeof(struct komplex)));
	int offset2 = ((abruf - 1) * (sizeof(struct komplex)) + sizeof(double));

	if ((datei = fopen("X:/test.txt", "r+")) != NULL)
	{
		fseek(datei, offset, SEEK_SET);
		fscanf(datei, "%lf", &ausgabe.real);
		fseek(datei, offset2, SEEK_SET);
		fscanf(datei, "%lf", &ausgabe.imag);
		
		//fread(&ausgabe.real, (sizeof(double)), 1, datei);
		//fread(&ausgabe.imag, (sizeof(double)), 1, datei);

		printf("Die %i. Zahl ist:\n\n", abruf);
		printf("Real: %lf", ausgabe.real);
		printf("\nImag: %lf", ausgabe.imag);

		fclose(datei);
	}
	else
		printf("\nFehler");
}

void change(int aendern)
{
	struct komplex ausgabe;
	FILE *datei;
	double realneu, imagneu;
	int offset = ((aendern-1) * (sizeof(struct komplex)));
	int offset2 = ((aendern - 1) * (sizeof(struct komplex)) + sizeof(double));

	printf("Neuer Realteil: ");
	scanf("%lf", &realneu);
	printf("\nNeuer Imaginaerteil: ");
	scanf("%lf", &imagneu);

	if ((datei = fopen("X:/test.txt", "r+")) != NULL)
	{
		fseek(datei, offset, SEEK_SET);
		fprintf(datei, "%lf", realneu);
		fprintf(datei, "%lf", imagneu);

		fseek(datei, offset, SEEK_SET);
		fscanf(datei, "%lf", &ausgabe.real);
		fseek(datei, offset2, SEEK_SET);
		fscanf(datei, "%lf", &ausgabe.imag);


		//fread(&ausgabe.real, (sizeof(double)), 1, datei);
		//fread(&ausgabe.imag, (sizeof(double)), 1, datei);

		printf("Die neue Zahl ist:\n\n");
		printf("Real:%lf ", ausgabe.real);
		printf("\nImag: %lf", ausgabe.imag);

		fclose(datei);
	}
	else
		printf("\nFehler beim Oeffnen der Zieldatei.");
}
