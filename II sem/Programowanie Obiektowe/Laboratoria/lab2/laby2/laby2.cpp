#include <iostream>
#include <string>
#include "Book.h"
#include "Library.h"

std::ostream& operator<<(std::ostream& out, Book& book)
{
    out << "Ksiazka: Autor: ";
    out << book.GetAuthor();
    out << " Tytul: ";
    out << book.GetTitle() << std::endl;
    out << "Rozdzialy:" << std::endl;
    auto chapterTitles = book.GetChapterTitles();
    int i = 1;
    for (const auto& chapter : chapterTitles) {
        out << i << ". " << chapter << std::endl;
        i++;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, Library& library)
{
    out << "Biblioteka:\n{" << std::endl;
    for (std::size_t i = 0; i < library.GetSize(); i++)
    {
        out << ' ' << library[i];
    }
    out << " }" << std::endl;
    return out;
}

int main() {
   
    std::string a = "<Matthew Syed>", t = "<Metoda czarnej skrzynki>";

    Book e;
    std::cout << "e: " << e << std::endl;

    Book b1 = { a, t, {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"} };
    std::cout << "b1: " << b1 << std::endl;

    
    Book b2 = { "<Robert Kiyosaki>","<Bogaty ojciec,biedny ojciec>",
                {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"} };
    std::cout << "b2: " << b2 << std::endl;

    
    Book b3 = b1;
    std::cout << "b3: " << b3 << " b1: " << b1 << std::endl;

   
    e = std::move(b2);
    std::cout << "e: " << e << " b2:" << b2 << std::endl;

    
    e.SetAuthor("<George Orwell>");
    std::cout << "e: " << e << std::endl;

    
    e.SetTitle("<Rok 1984>");
    std::cout << "e: " << e << std::endl;

   
    Library l;
    std::cout << "l: " << l << std::endl;

    
    Library l1 = {
        {"George Orwell ", "Folwark Zwierzecy", {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"}},
        {"Robin Sharma","Manifest codziennego bohatera", {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"}},
        {"James Clear", "Atomowe nawyki", {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"}},
        {"Nicolo Machiavelli", "Ksiaze", {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"}}
    };
    std::cout << "l1: " << l1 << std::endl;

    
    Library l2(2);
    std::cout << "l2: " << l2 << std::endl;
    l2[0] = { "Simon Sinek", "Zaczynaj od dlaczego", {"Rozdzial1", "Rozdzial2", "Rozdzial3", "Rozdzial4", "Rozdzial5"} };
    l2[1] = { "Joseph Murphy", "Potega podswiadomości", {"Skarbnica w twoim wnetrzu", "Jak dziala umysl", "Cudotworcza moc podswiadomosci", "Uzdrawianie duchowe w dawnych czasach", "Uzdrawianie duchowe w czasach wspolczesnych"} };
    std::cout << "l2: " << l2 << std::endl;

   
    l = std::move(l2);
    std::cout << "l: " << l << " l2: " << l2 << std::endl;

    
    l1[0] = std::move(l[1]);
    std::cout << "l1: " << l1 << " l: " << l << std::endl;

    return 0;
}
