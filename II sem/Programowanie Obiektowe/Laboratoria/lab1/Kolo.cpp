#include "Kolo.h"
#include <iostream>
#include <cmath>

int Kolo::lkola = 0;

Kolo::Kolo(double radius)
    : radius(radius) {
    std::cout << "Konstruktor Kola(" << radius << ")" << std::endl;
}

double Kolo::GetRadius() const {
    return radius;
}

void Kolo::SetRadius(double radius) {
    this->radius = radius;
}

double Kolo::Obwod() {
    return 2 * 3.14 * radius;
}

double Kolo::Obwod(double pi) {
    return 2 * 3.14 * radius;
}

double Kolo::Pole() {
    return 3.14 * radius * radius;
}

void Kolo::Wypisz(std::ostream& out) const {
    lkola++;
    std::cout << "Liczba kol: " << lkola << std::endl;
    out << "Kolo: promien: " << radius << " obwod: " << 2 * 3.14 * radius << " pole: " << 3.14 * radius * radius << std::endl;
}

Kolo::~Kolo() {
    lkola--;
    std::cout << "Liczba kol: " << lkola << std::endl;
    std::cout << "Kolo: promien: " << radius << " obwod: " << 2 * 3.14 * radius << " pole: " << 3.14 * radius * radius << std::endl;
}
