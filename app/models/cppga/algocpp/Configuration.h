

#include <list>
#include <map>
#include <fstream>
#include <string>

#include <iostream>

using namespace std;


class Professor;
class StudentsGroup;
class Course;
class Room;
class CourseClass;

// Reads configration file and stores parsed objects
class Configuration
{

private:

	// Global instance
	static Configuration _instance;

public:

	// Returns reference to global instance
	inline static Configuration& GetInstance() { return _instance; }

private:

	//for IDrooms
	map<int,int> mapid;

	map<int, Professor*> _professors;

	map<int, StudentsGroup*> _studentGroups;

	// Parsed courses
	map<int, Course*> _courses;

	// Parsed rooms
	 map<int, Room*> _rooms;

	// Parsed classes
	list<CourseClass*> _courseClasses;

	// Inidicate that configuration is not prsed yet
	bool _isEmpty;

public:

	// Initialize data
	Configuration() : _isEmpty(true) { }

	// Frees used resources
	~Configuration();

	// Parse file and store parsed object
	void ReadDatabase();
	void InsertCBR();

	// Returns pointer to professor with specified ID
	// If there is no professor with such ID method returns NULL
	inline Professor* GetProfessorById(int id)
	{ 
		 map<int, Professor*>::iterator it = _professors.find( id );
		return it != _professors.end() ? ( *it ).second : NULL;
	}

	// Returns number of parsed professors
	inline int GetNumberOfProfessors() const { return (int)_professors.size(); }

	// Returns pointer to student group with specified ID
	// If there is no student group with such ID method returns NULL
	inline StudentsGroup *GetStudentsGroupById(int id)
	{ 
	 map<int, StudentsGroup*>::iterator it = _studentGroups.find( id );
		return  it != _studentGroups.end() ? ( *it ).second : NULL;
	}

	// Returns number of parsed student groups
	inline int GetNumberOfStudentGroups() const { return (int)_studentGroups.size(); }

	// Returns pointer to course with specified ID
	// If there is no course with such ID method returns NULL
	inline Course* GetCourseById(int id)
	{ 
	 map<int, Course*>::iterator it = _courses.find( id );
		return it != _courses.end() ? ( *it ).second : NULL;
	}

	inline int GetNumberOfCourses() const { return (int)_courses.size(); }

	// Returns pointer to room with specified ID
	// If there is no room with such ID method returns NULL
	inline Room* GetRoomById(int id)
	{ 
		 map<int, Room*>::iterator it = _rooms.find( id );
		return it != _rooms.end() ? ( *it ).second : NULL;
	}


	 inline int MapRoomBackward(int id)  { 
	 	int key = -1;
	 	for (auto it = mapid.begin(); it!=mapid.end(); ++it) {
	 		if (it->second == id) {
	 			key = it->first;
	 			break;
	 		}
	 	}
     	return key;
    }

 	inline int MapRoomId(int id)  { 
    	 auto it = mapid.find( id );
      	if (it != mapid.end()) {
      	//cout <<  ( *it ).second << "govo";
       return  ( *it ).second;
     }
    }
	// Returns number of parsed rooms
	inline int GetNumberOfRooms() const { return (int)_rooms.size(); }

	// Returns reference to list of parsed classes
	inline const list<CourseClass*>& GetCourseClasses() const { return _courseClasses; }

	// Returns number of parsed classes
	inline int GetNumberOfCourseClasses() const { return (int)_courseClasses.size(); }

	// Returns TRUE if configuration is not parsed yet
	inline bool IsEmpty() const { return _isEmpty; }
};
