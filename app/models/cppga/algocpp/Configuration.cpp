 


#include "Configuration.h"
#include "Professor.h"
#include "StudentsGroup.h"
#include "Course.h"
#include "Room.h"
#include "CourseClass.h"

Configuration Configuration::_instance;

// Frees used resources
Configuration::~Configuration()
{
	
	for( unordered_map<int, Professor*>::iterator it = _professors.begin(); it != _professors.end(); it++ )
		delete ( *it ).second;

	for( unordered_map<int, StudentsGroup*>::iterator it = _studentGroups.begin(); it != _studentGroups.end(); it++ )
		delete ( *it ).second;

	for( unordered_map<int, Course*>::iterator it = _courses.begin(); it != _courses.end(); it++ )
		delete ( *it ).second;

	for( unordered_map<int, Room*>::iterator it = _rooms.begin(); it != _rooms.end(); it++ )
		delete ( *it ).second;

	for( list<CourseClass*>::iterator it = _courseClasses.begin(); it != _courseClasses.end(); it++ )
		delete *it;
		
}
