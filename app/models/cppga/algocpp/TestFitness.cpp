
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string.h> 
#include <sstream>
#include <iostream>
//htonl


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
}

//_slots; _criteria; all groups ..
void TestFitness::TestCalculateFitness()
{
  _days.clear();
  _timess.clear();
  _rms.clear();
_dur.clear();
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
                    int roomname =  atoi(PQgetvalue(res, row , 1)) ;
                    bool lab = !strcmp ( PQgetvalue(res, row , 2), "t" );
                    int meetingtime = atoi(PQgetvalue(res, row , 3));
                     int meetingday = atoi(PQgetvalue(res, row , 4));
                      int courseduration = atoi(PQgetvalue(res, row , 5));
						char* coursename =  PQgetvalue(res, row , 6) ;
				char* profname =  PQgetvalue(res, row , 7) ;
				char* groupname =  PQgetvalue(res, row , 8) ;
             _rms.insert( pair<int, int>( row, roomname ) );
             _days.insert( pair<int, int>( row, meetingday ) );
             _timess.insert( pair<int, int>( row, meetingtime ) );
             _dur.insert( pair<int, int>( row, courseduration ) );
               // cout << id << endl << "->" << 
               
               // meetingtime << "<-t"<<endl <<
               // meetingday <<endl <<
               //  courseduration << "<-dur"<<endl << endl;
              // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
	PQclear(res);
}
           //  puts ("rooms");
/*   int idmax;
  res = PQexec(conn,"select id from cbrcases order by id desc limit 1");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);

       for (row=0; row<rec_count; row++) {
                     idmax =   atoi(PQgetvalue(res, row , 0));
               
                          cout << idmax << "idmax";
               // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
	PQclear(res);


    const char *paramValues[1];
    int         paramLengths[1];
    int         paramFormats[1];
    uint32_t    binaryIntVal;
  binaryIntVal = htonl((uint32_t) 2);
  paramValues[0] = (char *) &binaryIntVal;
    paramLengths[0] = sizeof(binaryIntVal);
    paramFormats[0] = 1;        

int idcbr ;
 res = PQexecParams(conn,"select id from cbrcases where numofcla = $1::int4 limit 1",
  1, //number of parameters
NULL, //ignore the Oid field
paramValues, //values to substitute $1 and $2
paramLengths, //the lengths, in bytes, of each of the parameter values
paramFormats, //whether the values are binary or not
0); 
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
         rec_count = PQntuples(res);

       for (row=0; row<rec_count; row++) {
                     idcbr =   atoi(PQgetvalue(res, row , 0));
                      // int numberOfCourseClasses =   atoi(PQgetvalue(res, row , 1));  
                      // int numberOfProfessors =   atoi(PQgetvalue(res, row , 2));
                      //   int numberOfGroups =   atoi(PQgetvalue(res, row , 3));
                      //     int numberOfRooms =   atoi(PQgetvalue(res, row , 4));
                          cout << idcbr << "cbri";
                          //  << numberOfCourseClasses << numberOfProfessors << numberOfGroups<<
                          // numberOfRooms << endl ;
               // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
  PQclear(res);

    const char *paramValues2[1];
    int         paramLengths2[1];
    int         paramFormats2[1];
    uint32_t    binaryIntVal2;
  binaryIntVal2 = htonl((uint32_t) idcbr);
  paramValues2[0] = (char *) &binaryIntVal2;
    paramLengths2[0] = sizeof(binaryIntVal2);
    paramFormats2[0] = 1;       

 
  res = PQexecParams(conn,"select * from courseevents where cbrcase_id= $1::int4 order by id",
     1, //number of parameters
NULL, //ignore the Oid field
paramValues2, //values to substitute $1 and $2
paramLengths2, //the lengths, in bytes, of each of the parameter values
paramFormats2, //whether the values are binary or not
0);
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
        }
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
             _rms.insert( pair<int, int>( row, roomname ) );
             _days.insert( pair<int, int>( row, meetingday ) );
             _timess.insert( pair<int, int>( row, meetingtime ) );
               // cout << id << endl << "->" << 
               // roomname << "<-"<< row<<endl <<
               // lab << endl <<
               // meetingtime << endl <<
               // meetingday <<endl <<
               //  courseduration << endl <<
               //  coursename <<endl <<
               //   profname <<endl
               //   << groupname << "---> " <<"id read" << endl;
              // Room* r =  new Room(id, name, lab, size ); 
                   
            // if( r ) {
            //   _rooms.insert( pair<int, Room*>( r->GetId(), r ) );
      }
  PQclear(res);

}

int main() 
{

	TestFitness *testf = new TestFitness();
   testf-> TestCalculateFitness();	
	return 0;
}

Schedule* Schedule::MakeNewFromPrototype() const
{
  // number of time-space slots
  int size = (int)_slots.size();
 
  // make new chromosome, copy chromosome setup
  Schedule* newChromosome = new Schedule( *this, true );

  // place classes at random position
 
  const list<CourseClass*>& c = Configuration::GetInstance().GetCourseClasses();
  //cout <<"s-"<<c.size()<< endl;
  int a = 0;
  for( list<CourseClass*>::const_iterator it = c.begin(); it != c.end(); it++ )
  {
    // determine random position of class
    int nr = Configuration::GetInstance().GetNumberOfRooms();
    //cout << nr<<"nr"<<endl; 
    int dur = ( *it )->GetDuration();
    int day = rand() % DAYS_NUM;
    int room = rand() % nr;

    int timeS = rand() % ( DAY_HOURS + 1 - dur );
    int pos = day * nr * DAY_HOURS + room * DAY_HOURS + timeS;
   
    // fill time-space slots, for each hour of class
    for( int i = dur - 1; i >= 0; i-- )
      newChromosome->_slots.at( pos + i ).push_back( *it );
    // insert in class table of chromosome
    newChromosome->_classes.insert( pair<CourseClass*, int>( *it, pos ) );
   
    
  }
 
  newChromosome->CalculateFitness();

  // return smart pointer
  return newChromosome;
}
*/