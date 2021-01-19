#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#include "person.h"
#include "status.h"
#include "page.h"


Person::Person(string name, int dd, int mm, int yyyy) : Entity(name)
{
	this->dateOfBirth[0] = dd;
	this->dateOfBirth[1] = mm;
	this->dateOfBirth[2] = yyyy;
}

Person::Person(const Person& other) : Entity(other)
{
	for (int i = 0; i < 3; i++)
		this->dateOfBirth[i] = other.dateOfBirth[i];
	//this->friends = vector<Person*>(other.friends);
	//this->pages = vector<Page*>(other.pages);
}

Person::~Person()
{
}


vector<Person*>& Person::getFriends()
{
	return this->friends;
}


vector<Page*>& Person::getPages()
{
	return this->pages;
}


void Person::likePage(Page& p)
{
	this->pages.push_back(&p);
	p.getFans().push_back(this);
}


void Person::addFriend(Person& p)
{
	this->friends.push_back(&p);
	p.friends.push_back(this);
}


void Person::checkWithFriends()
{
	vector<Status*> currentFeed;
	for (auto myFriend = this->friends.begin(); myFriend != this->friends.end(); ++myFriend)
	{
		currentFeed = (*myFriend)->feed;
		cout << "\n||||||||  posts by " << **myFriend << "  ||||||||\n\n";

		int i = 0;
		for (auto status = currentFeed.rbegin(); status != currentFeed.rend() & i < 10; ++status, ++i)
			cout << **status << endl;
	}
}

