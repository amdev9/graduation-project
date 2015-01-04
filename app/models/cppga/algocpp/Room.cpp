
#include "Room.h"

 
int Room::_nextRoomId = 0;
// Initializes room data and assign ID to room
Room::Room(const string& name, bool lab, int numberOfSeats) : _id(_nextRoomId++), //int id,
																	  _name(name),
																	  _lab(lab),
																	  _numberOfSeats(numberOfSeats) { }
