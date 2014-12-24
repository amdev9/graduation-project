
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string.h> 
#include <sstream>
#include <iostream>

#define DAY_HOURS	12
// Number of days in week
#define DAYS_NUM	6 //5


using namespace std;

//rewrite fitness func for test	
//if 1 -> nice
//if 0 -> delete and error message
//need
//_slots; _criteria; all groups ..
void TestCalculateFitness()
{

	    PGconn     *conn;
  		PGresult    *res, *resgr;
        int     rec_count, rec_countgr;
        int row;
         int row1;
         int col;
     
 
         conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
 
         if (PQstatus(conn) == CONNECTION_BAD) {
                 puts("We were unable to connect to the database");
          
      }
 
  res = PQexec(conn,"select * from courseevents where cbrcase_id=1 order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);

       for (row=0; row<rec_count; row++) {
                    int id =   atoi(PQgetvalue(res, row , 0));
                    char* roomname =  PQgetvalue(res, row , 1) ;
                    bool lab = !strcmp ( PQgetvalue(res, row , 2), "t" );
                    int meetingtime = atoi(PQgetvalue(res, row , 3));
                     int meetingday = atoi(PQgetvalue(res, row , 4));
                      int courseduration = atoi(PQgetvalue(res, row , 5));
						char* coursename =  PQgetvalue(res, row , 6) ;
				char* profname =  PQgetvalue(res, row , 7) ;
				char* groupname =  PQgetvalue(res, row , 8) ;
               

               cout << id << endl <<
               roomname << endl <<
               lab << endl <<
               meetingtime << endl <<
               meetingday <<endl <<
                courseduration << endl <<
                coursename <<endl <<
                 profname <<endl
                 << groupname << "---> " <<"id read" << endl;
               // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
	PQclear(res);
           //  puts ("rooms");
  
  res = PQexec(conn,"select * from cbrcases where id=1 order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);

       for (row=0; row<rec_count; row++) {
                    int idcbr =   atoi(PQgetvalue(res, row , 0));
                      int numberOfCourseClasses =   atoi(PQgetvalue(res, row , 1));  
                      int numberOfProfessors =   atoi(PQgetvalue(res, row , 2));
                        int numberOfGroups =   atoi(PQgetvalue(res, row , 3));
                          int numberOfRooms =   atoi(PQgetvalue(res, row , 4));
                          cout << idcbr << "cbri";
               // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
	PQclear(res);

}

int main() {
	TestCalculateFitness();	
	return 0;
}