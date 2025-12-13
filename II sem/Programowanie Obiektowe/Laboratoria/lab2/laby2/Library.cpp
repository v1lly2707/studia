#include "Library.h"

Library::Library() 
{
	arr = nullptr;
	idx = 0;
}

Library::Library(std::size_t idx)
	:idx{ idx }, arr{ new Book[idx] }
{
}

Library::Library(std::initializer_list<Book> list) //konstruktor z lista inicjalizacyjna
	: idx{ list.size() }, arr{ new Book[list.size()] }
{
	std::size_t i = 0;
	for (Book v : list)
	{
		arr[i] = v;
		i++;
	}
}

Library::Library(const Library& orig) //konstruktor kopiuj¹cy
	:idx{ orig.idx }, arr{ new Book[orig.idx] }
{
	for (std::size_t i = 0; i < idx; i++)
	{
		arr[i] = orig.arr[i];
	}
}

Library::Library(Library&& orig) //konstruktor przenosz¹cy
{
	idx = orig.idx;
	arr = orig.arr;

	orig.idx = 0;
	orig.arr = nullptr;
}

Library& Library::operator=(const Library& right) //kopiuj¹cy operator przypisania
{
	Library tmp = right;
	std::swap(arr, tmp.arr);
	std::swap(idx, tmp.idx);
	return *this;
}

Library& Library::operator=(Library&& right) //przenosz¹cy operator przypisania
{
	std::swap(idx, right.idx);
	std::swap(arr, right.arr);
	return *this;
}

Book& Library::operator[](std::size_t index)
{
	return arr[index];
}

const Book& Library::operator[](std::size_t index) const
{
	return arr[index];
}

std::size_t Library::GetSize() const
{
	return idx;
}

Library::~Library()
{
	if (arr != nullptr)
	{
		delete[] arr;
	}
}