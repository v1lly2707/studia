#pragma once
#include "FiguraPlaska.h"
#include <iostream>

class Kolo : public FiguraPlaska {
    double radius;


protected:
    void Wypisz(std::ostream& out) const override;

public:
    static int lkola;

    Kolo(double radius);
    double GetRadius() const;
    void SetRadius(double a);
    double Obwod() override;
    double Obwod(double pi);
    double Pole() override;
    
    ~Kolo() ;
};
