#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#include "page.h"
#include "status.h"
#include "person.h"


Page::Page(string name) : Entity(name)
{
}

Page::Page(const Page& other) : Entity(other)
{

}

Page::~Page()
{
}


vector<Person*>& Page::getFans()
{
	return this->fans;
}
