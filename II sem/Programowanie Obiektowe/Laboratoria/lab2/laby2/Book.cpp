#include "Book.h"

Book::Book() // konstruktor bezparametrowy
    : author(""), title(""), chapterTitles({}) {}

Book::Book(const std::string& author, const std::string& title, const std::array<std::string, 5>& chapterTitles)
    : author(author), title(title), chapterTitles(chapterTitles) {}

Book::Book(std::string&& author, std::string&& title, std::array<std::string, 5>&& chapterTitles)
    : author(std::move(author)), title(std::move(title)), chapterTitles(std::move(chapterTitles)) {}

std::string Book::GetAuthor() // geter author
{
    return author;
}

std::string Book::GetTitle() // geter title
{
    return title;
}

std::array<std::string, 5> Book::GetChapterTitles() // geter tytu³ów rozdzia³ów
{
    return chapterTitles;
}

void Book::SetAuthor(const std::string& author) // seter author z l-referencja
{
    this->author = author;
}

void Book::SetTitle(const std::string& title) // seter title z l-referencja
{
    this->title = title;
}

void Book::SetAuthor(std::string&& author) // seter author z r-referencja
{
    this->author = std::move(author);
}

void Book::SetTitle(std::string&& title) // seter title z r-referencja
{
    this->title = std::move(title);
}

void Book::SetChapterTitles(const std::array<std::string, 5>& chapterTitles) // seter tytu³ów rozdzia³ów z l-referencjami
{
    this->chapterTitles = chapterTitles;
}

void Book::SetChapterTitles(std::array<std::string, 5>&& chapterTitles) // seter tytu³ów rozdzia³ów z r-referencjami
{
    this->chapterTitles = std::move(chapterTitles);
}

Book::Book(const Book& other) // konstruktor kopiuj¹cy
    : author(other.author), title(other.title), chapterTitles(other.chapterTitles) {}

Book::Book(Book&& other) // konstruktor przenosz¹cy
    : author(std::move(other.author)), title(std::move(other.title)), chapterTitles(std::move(other.chapterTitles)) {}

Book& Book::operator=(const Book& right) // kopiuj¹cy operator przypisania
{
    if (this == &right)
        return *this;

    author = right.author;
    title = right.title;
    chapterTitles = right.chapterTitles;
    return *this;
}

Book& Book::operator=(Book&& right) // przenosz¹cy operator przypisania
{
    if (this == &right)
        return *this;

    author = std::move(right.author);
    title = std::move(right.title);
    chapterTitles = std::move(right.chapterTitles);
    return *this;
}