
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string.h> 
#include <sstream>
#include <iostream>

 #include "Professor.h"
#include "StudentsGroup.h"
#include "Course.h"
 #include "Configuration.h"
#include "CourseClass.h"
 


#include "TestFitness.h"


#define DAY_HOURS	12
// Number of days in week
#define DAYS_NUM	6 //5


using namespace std;
 
 
TestFitness TestFitness::_tf;

 TestFitness::~TestFitness()
{
  
   _days.clear();
  _timess.clear();
  _rms.clear();
_dur.clear();
_groupsmap.clear();
}

//_slots; _criteria; all groups ..
void TestFitness::TestCalculateFitness()
{
  _days.clear();
  _timess.clear();
  _rms.clear();
  _dur.clear();
  _groupsmap.clear();
  PGconn     *conn;
  PGresult    *res, *rescla;
  int rec_count, rec_countgr;
  int row;
  int row1;
  int col;
  
  conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
  if (PQstatus(conn) == CONNECTION_BAD) {puts("We were unable to connect to the database");}
 
  res = PQexec(conn,"select * from courseevents where cbrcase_id=1 order by id desc");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) { puts("We did not get any data!");}

  rec_count = PQntuples(res);

  for (row=0; row<rec_count; row++) {
     int id =   atoi(PQgetvalue(res, row , 0));
     int roomname =  atoi(PQgetvalue(res, row , 1)) ;
     bool lab = !strcmp ( PQgetvalue(res, row , 2), "t" );
     int meetingtime = atoi(PQgetvalue(res, row , 3));
     int meetingday = atoi(PQgetvalue(res, row , 4));
     int courseduration = atoi(PQgetvalue(res, row , 5));
		 char* coursename =  PQgetvalue(res, row , 6) ;
		 char* profname =  PQgetvalue(res, row , 7) ;
		 char* groupname =  PQgetvalue(res, row , 8) ;
             
             cout << groupname << endl;
     _rms.insert( pair<int, int>( row, roomname ) );
     _days.insert( pair<int, int>( row, meetingday ) );
     _timess.insert( pair<int, int>( row, meetingtime ) );
     _dur.insert( pair<int, int>( row, courseduration ) );
      _groupsmap.insert(pair<int, char*>(row,groupname));
   }

   list<StudentsGroup*> groupsevents;
             
      rescla = PQexec(conn, "select * from clas order by id");
      if (PQresultStatus(rescla) != PGRES_TUPLES_OK) {puts("We did not get any data!");}
      rec_count = PQntuples(rescla);           
       

      for (row=0; row<rec_count; row++) {
        int claid = atoi(PQgetvalue(rescla, row , 0));
        int pid =   atoi(PQgetvalue(rescla, row , 1));
        int  cid = atoi(PQgetvalue(rescla, row , 2));
        int dur  = atoi(PQgetvalue(rescla, row , 4));
        bool lab = !strcmp ( PQgetvalue(rescla, row , 5), "t" );
        
        Professor* p = Configuration::GetInstance().GetProfessorById( pid );
        Course* c = Configuration::GetInstance().GetCourseById( cid );
        
        int groups_col = 0;
        map<int,int> arr;
        char * pch = strtok (_groupsmap.find(row )->second,"/");
        while (pch != NULL)
        {
           arr.insert(pair <int,int>(groups_col,atoi(pch)));  
          pch = strtok (NULL, "/");
          groups_col++;
        }
        
        for (row1=0; row1<  groups_col ; row1++) {

          if (claid == arr.find(row1)->second ) {
            StudentsGroup* g = Configuration::GetInstance().GetStudentsGroupById(  arr.find(row1)->second );
            if( g ) {
              groupsevents.push_back( g );
            }
          }
        }
        CourseClass* cc = new CourseClass( p, c, groupsevents, lab, dur );
        if( cc ) 
          _courseClassesTest.push_back( cc );
        groupsevents.clear();
      }
      PQclear(res);
      PQclear(rescla);
      PQfinish(conn);   
}
  