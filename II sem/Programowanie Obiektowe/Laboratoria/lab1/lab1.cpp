#include <iostream>
#include "FiguraPlaska.h"
#include "Kolo.h"
#include "Trojkat.h"
#include "Prostokat.h"

using namespace std;

int main()
{
	
	Prostokat p1(3, 5);
	Prostokat* p2 = new Prostokat(4, 9);
	Kolo k1(14);
	Prostokat p3(4, 9);
	FiguraPlaska* figuraPlaska[3];
	figuraPlaska[0] = &k1;
	figuraPlaska[1] = &p1;
	figuraPlaska[2] = &p3;
	figuraPlaska[0]->Obwod();
	FiguraPlaska* test;
	test = &p1;
	cout << test->Pole() << endl;

	test = p2;
	cout << test->Pole() << endl;
	
	test = &k1;
	cout << test->Pole() << endl;

	for (auto &i : figuraPlaska)
	{
		cout << *i << endl;
	}

	//test = &p3;
	//cout << test->Pole() << endl;

	delete p2;
}