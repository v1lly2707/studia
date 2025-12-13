#pragma once
#include <iostream>
#include <string>
#include <array>

class Book {
private:
    std::string author;
    std::string title;
    std::array<std::string, 5> chapterTitles;
public:
    Book(); // konstruktor bezparametrowy

    Book(const std::string& author, const std::string& title, const std::array<std::string, 5>& chapterTitles); // konstruktor l-referencja

    Book(std::string&& author, std::string&& title, std::array<std::string, 5>&& chapterTitles); // konstruktor r-referencja

    std::string GetAuthor(); // geter author

    std::string GetTitle(); // geter title

    std::array<std::string, 5> GetChapterTitles(); // geter tytu³ów rozdzia³ów

    void SetAuthor(const std::string& author); // seter z l-referencjami

    void SetTitle(const std::string& title); // seter z l-referencjami

    void SetAuthor(std::string&& author); // seter z r-referencjami

    void SetTitle(std::string&& title); // seter z r-referencjami

    void SetChapterTitles(const std::array<std::string, 5>& chapterTitles); // seter tytu³ów rozdzia³ów z l-referencjami

    void SetChapterTitles(std::array<std::string, 5>&& chapterTitles); // seter tytu³ów rozdzia³ów z r-referencjami

    Book(const Book& other); // konstruktor kopiuj¹cy

    Book(Book&& other); // konstruktor przenosz¹cy

    Book& operator=(const Book& right); // kopiuj¹cy operator przypisania

    Book& operator=(Book&& right); // przenosz¹cy operator przypisania
};