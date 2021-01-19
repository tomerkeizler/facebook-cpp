#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include <string>
#include <vector>

class Status;


class Entity
{
protected:
	string name;
	vector<Status*> feed;

public:
	Entity(string name);
	Entity(const Entity& other);
	~Entity();

	string& getName();
	vector<Status*>& getFeed();

	Status& getStatusByNum(int num);
	void addStatus(Status* s);

	// ----------------- operators -----------------

	bool operator==(const Entity& e) const
	{
		return this->name.compare(e.name) == 0;
	}


	friend ostream& operator<<(ostream& os, const Entity& e)
	{
		os << e.name;
		return os;
	}

};

#endif // Entity_CLASS
