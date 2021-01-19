#ifndef STATUS_CLASS
#define STATUS_CLASS

#include <string>
#include <ctime>

enum status_type { text, picture, textpicture, video , textvideo};

static const char* status_types[] = { "text" , "picture", "text & picture", "video", "text & video" };
static const char* display_types[] = { "black & white" , "color" };
static const char* software_types[] = { "simple software" , "real player" };


class Status
{
private:
	status_type publishType;
	string content;
	time_t publishTime;


public:
	Status(status_type publishType, char* content);
	~Status();
	
	// ----------------- operators -----------------

	int operator==(const Status& other) const
	{
		return this->content.compare(other.content);
	}


	int operator!=(const Status& other) const
	{
		return !(*this == other);
	}


	friend ostream& operator<<(ostream& os, const Status& s)
	{
		// for text: display in black & white
		// otherwise: display in color
		int myDisplay = (s.publishType == 0) ? (0) : (1);

		// for video: display via real player
		// otherwise: display via simple software
		int mySoftware = (s.publishType < 3) ? (0) : (1);

		os << ctime(&(s.publishTime)) << "[" << status_types[s.publishType] << ", in " << display_types[myDisplay] << ", via " << software_types[mySoftware] << "]\n";
		os << "----------- " << s.content << endl;

		return os;
	}

};

#endif // STATUS_CLASS
