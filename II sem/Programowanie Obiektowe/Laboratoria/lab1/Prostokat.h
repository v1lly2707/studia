#pragma once
#include "FiguraPlaska.h"
class Prostokat : public FiguraPlaska {
private:
	double a, b;
protected:
	void Wypisz(std::ostream& out) const override;
public:
	Prostokat(double a, double b);
	static int lprostokaty;
	double GetA() const;
	void SetA(double a);
	double GetB() const;
	void SetB(double b);
	double Obwod() override;
	//double Obwod(double  a, double b) override;

	double Pole() override;

	~Prostokat() ;
};