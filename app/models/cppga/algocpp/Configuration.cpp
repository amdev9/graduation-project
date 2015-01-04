#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string.h> 
#include <sstream>


#include "Configuration.h"
#include "Professor.h"
#include "StudentsGroup.h"
#include "Course.h"
#include "Room.h"
#include "CourseClass.h"
#include "ChildView.h"

 

using namespace std;

Configuration Configuration::_instance;

// Frees used resources
Configuration::~Configuration()
{
	
	for(  map<int, Professor*>::iterator it = _professors.begin(); it != _professors.end(); it++ )
		delete ( *it ).second;

	for(  map<int, StudentsGroup*>::iterator it = _studentGroups.begin(); it != _studentGroups.end(); it++ )
		delete ( *it ).second;

	for( map<int, Course*>::iterator it = _courses.begin(); it != _courses.end(); it++ )
		delete ( *it ).second;

	for( map<int, Room*>::iterator it = _rooms.begin(); it != _rooms.end(); it++ )
		delete ( *it ).second;

	for( list<CourseClass*>::iterator it = _courseClasses.begin(); it != _courseClasses.end(); it++ )
		delete *it;
		
}


void    Configuration::ReadDatabase() {
  _professors.clear();
  _studentGroups.clear();
  _courses.clear();
   _rooms.clear();
  _courseClasses.clear();
  mapid.clear(); 
  PGconn     *conn;
  PGresult    *res, *resgr;
  int     rec_count, rec_countgr;
  int row,row1,col;
  
  conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
  if (PQstatus(conn) == CONNECTION_BAD) 
  { puts("We were unable to connect to the database");}
  
  res = PQexec(conn,"select * from rooms order by id");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {puts("We did not get any data!");}
         
  rec_count = PQntuples(res);
  for (row=0; row<rec_count; row++) {
    int id =   atoi(PQgetvalue(res, row , 0));
    char* name =  PQgetvalue(res, row , 1) ;
    bool lab = !strcmp ( PQgetvalue(res, row , 2), "t" );
    int size = atoi(PQgetvalue(res, row , 3));
    Room* r =  new Room(name, lab, size ); 
                    
    int a = row;
    a = a + 1;
    mapid.insert(pair <int,int> (a,id));
        
    if( r ) {
      _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
    }
  }
  PQclear(res);
 
  res = PQexec(conn, "select * from courses order by id");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) { puts("We did not get any data!");}
  rec_count = PQntuples(res);
       
  for (row=0; row<rec_count; row++) {
    int id =   atoi(PQgetvalue(res, row , 0));
    char* name =  PQgetvalue(res, row , 1) ; 
    
    Course* r =  new Course(id, name  );  
    if( r )
        _courses.insert( pair<int, Course*>( r->GetId(), r ) );
    }
    PQclear(res);

    res = PQexec(conn,"select * from professors order by id");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) { puts("We did not get any data!");}
    rec_count = PQntuples(res);

    for (row=0; row<rec_count; row++) {
      int id =   atoi(PQgetvalue(res, row , 0));
      char* name =  PQgetvalue(res, row , 1) ;
      Professor* r =  new Professor(id, name  );  
      if( r )
        _professors.insert( pair<int, Professor*>( r->GetId(), r ) );
      }
      PQclear(res);
      res = PQexec(conn,"select * from groups order by id");
      if (PQresultStatus(res) != PGRES_TUPLES_OK) { puts("We did not get any data!");}
      rec_count = PQntuples(res);
      
      for (row=0; row<rec_count; row++) {
        int id =   atoi(PQgetvalue(res, row , 0));
        char* name =  PQgetvalue(res, row , 1) ;
        int size = atoi(PQgetvalue(res, row , 2));      
        StudentsGroup* r =  new StudentsGroup(id, name , size );  
        if( r ) {
          _studentGroups.insert( pair<int, StudentsGroup*>( r->GetId(), r ) );
        }
      }
      PQclear(res);
 
      list<StudentsGroup*> groups;
             
      res = PQexec(conn, "select * from clas order by id");
      if (PQresultStatus(res) != PGRES_TUPLES_OK) {puts("We did not get any data!");}
      rec_count = PQntuples(res);           
      resgr = PQexec(conn,
        "select clas.id, cla_groups.group_id from cla_groups INNER JOIN clas ON  cla_groups.cla_id = clas.id");
                       
      if (PQresultStatus(resgr) != PGRES_TUPLES_OK) {puts("We did not get any data!");  }
      rec_countgr = PQntuples(resgr);

      for (row=0; row<rec_count; row++) {
        int claid = atoi(PQgetvalue(res, row , 0));
        int pid =   atoi(PQgetvalue(res, row , 1));
        int  cid = atoi(PQgetvalue(res, row , 2));
        int dur  = atoi(PQgetvalue(res, row , 4));
        bool lab = !strcmp ( PQgetvalue(res, row , 5), "t" );
        
        Professor* p = GetProfessorById( pid );
        Course* c = GetCourseById( cid );
        
        for (row1=0; row1<rec_countgr; row1++) {
          if (claid ==atoi(PQgetvalue(resgr, row1 , 0))) {
            StudentsGroup* g = GetStudentsGroupById(  atoi(PQgetvalue(resgr, row1 , 1)));
            if( g ) {
              groups.push_back( g );
            }
          }
        }
        CourseClass* cc = new CourseClass( p, c, groups, lab, dur );
        if( cc ) 
          _courseClasses.push_back( cc );
        groups.clear();
      }
      PQclear(resgr);
      PQclear(res);
      PQfinish(conn);
      _isEmpty = false;
 }
 