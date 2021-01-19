#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#include "status.h"



Status::Status(status_type publishType = (status_type)0, char* content = new char[1])
{
	this->publishType = publishType;
	this->content = string(content);
	this->publishTime = time(0);
}


Status::~Status()
{
}
