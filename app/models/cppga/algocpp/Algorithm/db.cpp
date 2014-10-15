#include <iostream>
 #include <postgresql/libpq-fe.h>
 #include <string>
#include <cstdlib>
#include <unordered_map>
#include <fstream>
  #include <string.h>
#include "Room.h"
#include "Course.h"
#include "Professor.h"
#include "StudentsGroup.h"
#include "CourseClass.h"
#include "Configuration.h"

  using namespace std;
 
   
void    Configuration::ReadDatabase() {
  _professors.clear();
  _studentGroups.clear();
  _courses.clear();
  _rooms.clear();
  _courseClasses.clear();

   

	    PGconn          *conn;
  		PGresult        *res, *resgr;
        int             rec_count, rec_countgr;
        int             row;
         int             row1;

 		int             col;
    //***
    int number = 0;
   /*
   unordered_map<int, Room*> _rooms;
   unordered_map<int, Course*> _courses;
   unordered_map<int, Professor*> _professors;
   unordered_map<int, StudentsGroup*> _studentGroups;
    list<CourseClass*> _courseClasses;*/
   // string name;


 
         conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
 
         if (PQstatus(conn) == CONNECTION_BAD) {
                 puts("We were unable to connect to the database");
          
      }
 
     
 
         res = PQexec(conn,
                 "select * from rooms order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);

       for (row=0; row<rec_count; row++) {
                    int id =   atoi(PQgetvalue(res, row , 0));
                    char* name =  PQgetvalue(res, row , 1) ;
                    bool lab = !strcmp ( PQgetvalue(res, row , 2), "t" );
                    int size = atoi(PQgetvalue(res, row , 3));
     
                    Room* r =  new Room(id, name, lab, size );  
            if( r )
              _rooms.insert( pair<int, Room*>( r->GetId(), r ) );

             puts ("rooms");

       }
  PQclear(res);
         res = PQexec(conn,
                 "select * from courses order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);
       

      for (row=0; row<rec_count; row++) {
                    int id =   atoi(PQgetvalue(res, row , 0));
                    char* name =  PQgetvalue(res, row , 1) ;
     
                    Course* r =  new Course(id, name  );  
            if( r )
              _courses.insert( pair<int, Course*>( r->GetId(), r ) );
            puts ("courses");
       }
 
         PQclear(res);
            res = PQexec(conn,
                 "select * from professors order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);
       

      for (row=0; row<rec_count; row++) {
                    int id =   atoi(PQgetvalue(res, row , 0));
                    char* name =  PQgetvalue(res, row , 1) ;
     
                    Professor* r =  new Professor(id, name  );  
            if( r )
              _professors.insert( pair<int, Professor*>( r->GetId(), r ) );
            puts ("professors");
       }
 
         PQclear(res);

             res = PQexec(conn,
                 "select * from groups order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);
       

      for (row=0; row<rec_count; row++) {
                    int id =   atoi(PQgetvalue(res, row , 0));
                    char* name =  PQgetvalue(res, row , 1) ;
                   int size = atoi(PQgetvalue(res, row , 3));
                    StudentsGroup* r =  new StudentsGroup(id, name , size );  
            if( r )
              _studentGroups.insert( pair<int, StudentsGroup*>( r->GetId(), r ) );
            puts ("srudgroups");
       }
 
         PQclear(res);



PQclear(res);
list<StudentsGroup*> groups;

             res = PQexec(conn,
                 "select * from clas order by id");
         resgr = PQexec(conn,
  "SELECT groups.id FROM groups INNER JOIN cla_groups ON groups.id = cla_groups.group_id");


       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
        if (PQresultStatus(resgr) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);
        rec_countgr = PQntuples(resgr);

      for (row=0; row<rec_count; row++) {
                   int pid =   atoi(PQgetvalue(res, row , 0));
                   int  cid = atoi(PQgetvalue(res, row , 1));
                    string  value = PQgetvalue(res, row , 2);  /////////////&&&
              
                   int dur  = atoi(PQgetvalue(res, row , 3));
                  bool lab = !strcmp ( PQgetvalue(res, row , 4), "t" );

                Professor* p = GetProfessorById( pid );
                Course* c = GetCourseById( cid );
          for (row1=0; row1<rec_countgr; row1++) {

               StudentsGroup* g = GetStudentsGroupById( atoi(PQgetvalue(resgr, row1 , 0)));
                     if( g )
                    groups.push_back( g );
            }

              CourseClass* cc = new CourseClass( p, c, groups, lab, dur );

              if( cc )
                   _courseClasses.push_back( cc );
        }
     
 

         PQclear(res);
       PQclear(resgr);
 
     PQfinish(conn);
     
 }


int main() 
{
  Configuration*  a = new Configuration();
  a->ReadDatabase();
  a->~Configuration();
  return 0;
}
