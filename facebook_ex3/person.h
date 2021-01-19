#ifndef __person_h
#define __person_h

#define MAX_STR 1000

#include "entity.h"
#include <vector>

class Page;


class Person : public Entity
{
private:
	int dateOfBirth[3];
	vector<Person*> friends;
	vector<Page*> pages;


public:
	Person(string name, int dd = 0, int mm = 0, int yyyy = 0);
	Person(const Person& other);
	~Person();

	vector<Person*>& getFriends();
	vector<Page*>& getPages();

	void likePage(Page& p);
	void addFriend(Person& p);
	void checkWithFriends();

	// ----------------- operators -----------------

	void operator+=(Page& other)
	{
		this->likePage(other);
	}


	void operator+=(Person& other)
	{
		this->addFriend(other);
	}


	bool operator>(const Person& other) const
	{
		return this->friends.size() > other.friends.size();
	}

};

#endif
