#pragma once
#include <iostream>
#include <string>
#include <initializer_list>
#include "Book.h"

class Library {
	Book* arr;
	std::size_t idx;
public:
	Library();
	Library(std::size_t idx);
	Library(std::initializer_list<Book> list);
	Library(const Library& orig);
	Library(Library&& orig);
	Library& operator=(const Library& right);
	Library& operator=(Library&& right);
	Book& operator[](std::size_t index);
	const Book& operator[](std::size_t index) const;
	std::size_t GetSize() const;
	~Library();
};