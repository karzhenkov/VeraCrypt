#include <iostream>
#include <iomanip>
#include <list>
#include "ForEach.h"

using namespace VeraCrypt;

void print(const char* message, const char* data);

class Item
{
public:

	Item()
	{
		static int id = 0;
		m_data = new char(++id);
		print("create item", m_data);
	}

	Item(const Item& other)
	{
		m_data = new char(*other.data() + 100);
		print("copy item", m_data);
	}

	~Item()
	{
		print("destroy item", m_data);
		delete m_data;
	}

	const char* data() const
	{
		return m_data;
	}

private:

	const char *m_data;
};

void print(const char* message, const char* data)
{
	std::cout
		<< (const void*)data << " -> "
		<< std::setw(3) << (int)(unsigned char)(*data) << "  "
		<< message << std::endl;
}

int main()
{
	const int size = 3;

	std::cout << "create container" "\n";
	std::list<Item> container(size);

	int count = 0;
	const char* pointers[size];

	std::cout << "\n" "get data pointers" "\n";
	foreach (const Item& item, container) // iterates over the container copy!
	{
		const char* ptr = item.data();
		print("get valid pointer", ptr);
		pointers[count++] = ptr;
	}

	std::cout << "\n" "use data pointers" "\n";
	for (int i = 0; i < count; ++i)
		print("is pointer valid?", pointers[i]);

	std::cout << "\n" "destroy container" "\n";
}
