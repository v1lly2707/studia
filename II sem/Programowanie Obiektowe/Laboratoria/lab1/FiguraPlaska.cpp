#include "FiguraPlaska.h"
int FiguraPlaska::lfigury = 0;
std::ostream& operator<<(std::ostream& os, const FiguraPlaska& figura) {
	figura.Wypisz(os);
	return os;
}

FiguraPlaska::FiguraPlaska() {
	FiguraPlaska::lfigury++;
	std::cout << "Liczba figur " << lfigury << std::endl;
}
FiguraPlaska::~FiguraPlaska() {
	FiguraPlaska::lfigury--;
	std::cout << "Liczba figur " << lfigury << std::endl;
}

