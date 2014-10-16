
#include "Room.h"

 

// Initializes room data and assign ID to room
Room::Room(int id, const string& name, bool lab, int numberOfSeats) : _id(id),
																	  _name(name),
																	  _lab(lab),
																	  _numberOfSeats(numberOfSeats) { }
