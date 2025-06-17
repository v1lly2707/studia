#include <stdio.h>

double srednia_wazona(double tablica_dane[], double tablica_wagi[], unsigned int n);

int main()
{
	double wynik;
	double tablica_dane[] = { 1.0, 2.0, 4.0, 6.0, 12.0, 5.0 };
	double tablica_wagi[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	printf("%lf", srednia_wazona(tablica_dane, tablica_wagi, 6));


	return 0;
}