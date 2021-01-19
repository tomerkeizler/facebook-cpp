#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "page.h"
#include "person.h"
#include "status.h"


bool inRange(int low, int high, int num);
void prompt(const string textToPrint);

bool doesExists(const vector<Entity*>& data, string name);
Entity* pickFromAll(vector<Entity*>& data);

void addStatus(Entity& e);
void compareEntities(Entity e1, Entity e2, bool comp1, bool comp2);

void compareStatuses(Entity& curr);
int pickStatus(int size);

void mainMenu(vector<Entity*>& members, vector<Entity*>& pages);
void personSubMenu(vector<Entity*>& members, vector<Entity*>& pages, Person& user);
void pageSubMenu(vector<Entity*>& members, vector<Entity*>& pages, Page& page);


/* -------- a template function --------
INPUT: a vector of type T
OUTPUT: prints the elements of the vector */
template <class T>
void printVector(const vector<T*>& v);


void main()
{
	vector<Entity*> members;
	vector<Entity*> pages;
	cout << "Welcome to facebook!";
	mainMenu(members, pages);
}


////////////////////////////////////////////////////////////////////////////


bool inRange(int low, int high, int num)
{
	return (low <= num && num <= high);
}


void prompt(const string textToPrint)
{
	cout << endl;
	for (int i = 0; i < textToPrint.size(); i++)
		cout << "-";
	cout << endl << textToPrint << endl;
	for (int i = 0; i < textToPrint.size(); i++)
		cout << "-";
	cout << endl;
}


bool doesExists(const vector<Entity*>& data, string name)
{
	return std::find_if(data.begin(), data.end(), [name](Entity* e)->bool { return e->getName() == name; }) == data.end();
}


Entity* pickFromAll(vector<Entity*>& data)
{
	if (data.empty())
	{
		cout << "----- No records -----\n";
		return nullptr;
	}
	else
	{
		printVector(data);

		cout << "\nPlease choose from the above: ";
		char name[MAX_STR];
		cin.ignore();
		cin.getline(name, 1000);

		vector<Entity*>::iterator elem = std::find_if(data.begin(), data.end(), [name](Entity* e)->bool { return e->getName() == name; });
		if (elem == data.end())
		{
			prompt("There is no such record");
			return nullptr;
		}
		else
			return *elem;
	}
}


void addStatus(Entity& e)
{
	int type;
	do {
		cout << "0 - text\n1 - picture\n2 - text & picture\n3 - video\n4 - text & video\n\n";
		cout << "choose status type: ";
		cin >> type;
	} while (!inRange(0, 4, type));

	char status[MAX_STR];
	cout << "\nenter status content: ";
	cin.ignore();
	cin.getline(status, 1000);

	e.addStatus(new Status((status_type)type, status));
	prompt("The status was added successfully");
}


void compareEntities(Entity e1, Entity e2, bool comp1, bool comp2)
{
	if (comp1)
		prompt(e1.getName() + " is \"bigger\" than " + e2.getName());
	else if (comp2)
		prompt(e2.getName() + " is \"bigger\" than " + e1.getName());
	else
		prompt(e1.getName() + " and " + e2.getName() + " are \"equal\"");
}


void compareStatuses(Entity& curr)
{
	// show feed of the current entity
	prompt("Your status feed");
	printVector(curr.getFeed());

	int feedSize = curr.getFeed().size();

	if (feedSize > 1)
	{
		cout << "\nPlease choose 2 status numbers to compare:\n";
		int status1 = pickStatus(feedSize);
		int status2 = pickStatus(feedSize);

		if ((curr.getStatusByNum(status1) == curr.getStatusByNum(status2)) == 0)
			prompt("Those statuses are entirely identical");
		else
			prompt("Those statuses are completely different");
	}
	else
		prompt("The feed has less than 2 statuses");
}


int pickStatus(int size)
{
	int num;
	bool isFirstAttempt = true;

	do
	{
		if (!isFirstAttempt)
			cout << "No such status number. try again!\n";
	cout << "\nStatus number: ";
		cin >> num;
		isFirstAttempt = true;
	} while (!inRange(1, size, num));

	return num;
}


/* -------- a template function --------
INPUT: a vector of type T
OUTPUT: prints the elements of the vector */
template <class T>
void printVector(const vector<T*>& v)
{
	if (v.empty()) // no records in the vector
		cout << "----- No records -----\n";

	else // there are records in the vector
		for (typename vector<T*>::const_iterator i = v.begin(); i != v.end(); ++i)
			cout << **i << endl;
}



// -------------------------------------------------- //
// -------------------  main menu  -------------------//
// -------------------------------------------------- //


void mainMenu(vector<Entity*>& members, vector<Entity*>& pages)
{
	int opt;

	do
	{
		prompt("Please pick an option:");
		int i = 0;
		cout << ++i << ") Create a member\n";
		cout << ++i << ") Log in as a member\n";
		cout << ++i << ") Create a fan page\n";
		cout << ++i << ") Log in as a fan page\n";
		cout << ++i << ") Display all entities\n";
		cout << ++i << ") Exit\n";

		cout << "\nyour pick: ";
		cin >> opt;
		cout << endl;

		switch (opt)
		{

		case 1: // Create a member
		{
			char name[MAX_STR];
			int dob[3];

			bool firstAttempt = true;

			do {
				if (!firstAttempt)
					prompt("There is already a member called " + string(name));
				firstAttempt = false;

				prompt("Please enter member name and date of birth");
				cout << "Name: ";
				cin.ignore();
				cin.getline(name, 1000);

				cout << "Date of birth:\n";
				cout << "Day: ";
				cin >> dob[0];
				cout << "Month: ";
				cin >> dob[1];
				cout << "Year: ";
				cin >> dob[2];
			} while (!doesExists(members, name));

			members.push_back(new Person(name, dob[0], dob[1], dob[2]));
			cout << "\nThe member " << name << " was added successfully\n";
		}
		break;

		case 2: // Log in as a member
		{
			prompt("Log in as a member");
			Person* p = (Person*)pickFromAll(members);
			if (p != nullptr)
				personSubMenu(members, pages, *p);
		}
		break;

		case 3: // Create a fan page
		{
			char name[MAX_STR];
			bool firstAttempt = true;

			do {
				if (!firstAttempt)
					prompt("There is already a member called " + string(name));
				firstAttempt = false;

				cout << "Please enter a page name: ";
				cin.ignore();
				cin.getline(name, 1000);
			} while (!doesExists(pages, name));

			pages.push_back(new Page(name));
			cout << "\nThe page " << name << " was added successfully\n";
		}
		break;

		case 4: // Log in as a fan page
		{
			prompt("Log in as a fan page");
			Page* p = (Page*)pickFromAll(pages);
			if (p != nullptr)
				pageSubMenu(members, pages, *p);
		}
		break;

		case 5: // Display all entities
		{
			prompt("List of all members on facebook");
			printVector(members);

			prompt("List of all fan pages on facebook");
			printVector(pages);
		}
		break;

		default:
		{
			prompt("please enter a valid choice");
		}

		} // end of switch

	} while (opt != 6);
}


void personSubMenu(vector<Entity*>& members, vector<Entity*>& pages, Person& user)
{
	prompt("Welcome to facebook, " + user.getName());

	int opt;
	do
	{
		prompt("Please pick an option:");
		int i = 0;
		cout << ++i << ") Add a status\n";
		cout << ++i << ") Show your feed\n";
		cout << ++i << ") compare between two statuses\n\n";

		cout << ++i << ") Friend a member\n";
		cout << ++i << ") Display your friends\n";
		cout << ++i << ") Display recent posts of friends\n";
		cout << ++i << ") Compare number of friends with another person\n\n";

		cout << ++i << ") Like a page\n";
		cout << ++i << ") Display your liked pages\n\n";

		cout << ++i << ") Log out\n";

		cout << "\nyour pick: ";
		cin >> opt;
		cout << endl;

		switch (opt)
		{
		case 1: // Add a status
		{
			addStatus(user);
		}
		break;

		case 2: // Show your feed
		{
			prompt("Your status feed");
			printVector(user.getFeed());
		}
		break;

		case 3: // compare between two statuses
		{
			compareStatuses(user);
		}
		break;

		case 4: // Friend a member
		{
			prompt("List of all members on facebook");
			Person* newFriend = (Person*)pickFromAll(members);
			if (newFriend != nullptr)
			{
				// check if the user tries to friends himself
				if (newFriend->getName() == user.getName())
					prompt("You cannot friend yourself in facebook");
				else
				{
					user += *newFriend;
					prompt("Congratulations! " + newFriend->getName() + " is now your friend");

				}
			}
		}
		break;

		case 5: // Display your friends
		{
			prompt("List of your friends");
			printVector(user.getFriends());
		}
		break;

		case 6: // Display recent posts of friends
		{
			prompt("Recent posts of your friends");
			user.checkWithFriends();
		}
		break;

		case 7: // Compare friends with another person
		{
			prompt("List of all members on facebook");
			Person* p = (Person*)pickFromAll(members);
			if (p)
				compareEntities(user, *p, user > *p, *p > user);
		}
		break;

		case 8: // Like a page
		{
			prompt("List of all fan pages on facebook");
			Page* pageToLike = (Page*)pickFromAll(pages);
			if (pageToLike != nullptr)
			{
				user+=(*pageToLike);
				prompt("Congratulations! you now like fan page \"" + pageToLike->getName() + "\"");
			}
		}
		break;

		case 9: // Display your liked pages
		{
			prompt("List of your liked pages");
			printVector(user.getPages());

		}
		break;

		case 10: // Log out
		{
			prompt("Log out done successfully! Bye bye");
		}
		break;

		default:
		{
			prompt("please enter a valid choice");
		}

		} // end of switch
	} while (opt != 10);

	return;
}


void pageSubMenu(vector<Entity*>& members, vector<Entity*>& pages, Page& page)
{
	prompt("Welcome to facebook, fan page " + page.getName());
	
	int opt;
	do
	{
		prompt("Please pick an option:");
		int i = 0;
		cout << ++i << ") Add a status\n";
		cout << ++i << ") Show your feed\n";
		cout << ++i << ") compare between two statuses\n\n";

		cout << ++i << ") Display your fans\n";
		cout << ++i << ") Compare number of fans with another page\n\n";

		cout << ++i << ") Log out\n";

		cout << "\nyour pick: ";
		cin >> opt;
		cout << endl;

		switch (opt)
		{
		case 1: // Add a status
		{
			addStatus(page);
		}
		break;

		case 2: // Show your feed
		{
			prompt("Your status feed");
			printVector(page.getFeed());
		}
		break;

		case 3: // compare between two statuses
		{
			compareStatuses(page);
		}
		break;

		case 4: // Display your fans
		{
			prompt("Fans of this page");
			printVector(page.getFans());
		}
		break;


		case 5: // Compare fans with another page
		{
			prompt("List of all fan pages on facebook");
			Page* p = (Page*)pickFromAll(pages);
			if (p)
				compareEntities(page, *p, page > *p, *p > page);
		}
		break;

		case 6: // Log out
		{
			prompt("Log out done successfully! Bye bye");
		}
		break;

		default:
		{
			prompt("please enter a valid choice");
		}

		} // end of switch
	} while (opt != 6);

	return;
}

