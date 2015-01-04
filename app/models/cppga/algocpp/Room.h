

#include <string>

 using namespace std;

// Stores data about classroom
class Room
{

private:

 	static int _nextRoomId;

private:

	// Room ID - automatically assigned
	int _id;

	// Room name
	string _name;

	// Inidicates if room has computers
	bool _lab;

	// Number of seats in room
	int _numberOfSeats;

public:

	Room(const string& name, bool lab, int numberOfSeats);
	// Initializes room data and assign ID to room
//	Room(int id, const string& name, bool lab, int numberOfSeats);

	// Returns room ID
	inline int GetId() const { return _id; }

	// Returns name
	inline const string& GetName() const { return _name; }

	// Returns TRUE if room has computers otherwise it returns FALSE
	inline bool IsLab() const { return _lab; }

	// Returns number of seats in room
	inline int GetNumberOfSeats() const { return _numberOfSeats; }

	 
};
