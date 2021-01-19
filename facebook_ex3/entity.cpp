#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

#include "status.h"
#include "entity.h"


Entity::Entity(string name)
{
	this->name = string(name);
}


Entity::Entity(const Entity& other)
{
	this->name = string(other.name);
}


Entity::~Entity()
{
}


string& Entity::getName()
{
	return this->name;
}


vector<Status*>& Entity::getFeed()
{
	return this->feed;
}


Status& Entity::getStatusByNum(int num)
{
	return *(this->feed[num - 1]);
}


void Entity::addStatus(Status* s)
{
	this->feed.push_back(s);
}

