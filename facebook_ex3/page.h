#ifndef PAGE_CLASS
#define PAGE_CLASS

#include <string>
#include <vector>

#include "entity.h"

class Person;


class Page : public Entity
{
private:
	vector<Person*> fans;

public:
	Page(string name);
	Page(const Page& other);
	~Page();

	vector<Person*>& getFans();

	// ----------------- operators -----------------

	bool operator>(const Page& other) const
	{
		return this->fans.size() > other.fans.size();

	}

};

#endif // PAGE_CLASS
