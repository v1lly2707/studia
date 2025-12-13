#pragma once
#include "FiguraPlaska.h"
class Trojkat : public FiguraPlaska {
	double a, b, c;
protected:
	void Wypisz(std::ostream& out) const override;
public:
	Trojkat(double a, double b, double c);
	double GetA() const;
	void SetA(double a);
	static int ltrojkaty;
	double GetB() const;
	void SetB(double b);
	double GetC() const;
	void SetC(double c);
	double Obwod() override;
	
	//double Obwod(double a, double b,double c) override;
	double Pole() override;

	~Trojkat() ;
private:
};

