
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string.h> 
#include <sstream>
#include <iostream>

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
  
  
 
/*
	// chromosome's score
	int score = 0;

	int numberOfRooms = select numofrooms from cbrcases where id = max;
	int numberOfGroups =  select numofgroups from cbrcases where id = max;
	int daySize = DAY_HOURS * numberOfRooms;

	int ci = 0;
    int d = 0;
  
    map < int, map<int, int> >  mymap[6];
 	 
	// read classes func
	
	// check criterias and calculate scores for each class in schedule
	for(  map<CourseClass*, int>::const_iterator it = _classes.begin(); it != _classes.end(); ++it, ci += 5 )
	{
		// coordinate of time-space slot
		int p = ( *it ).second;

		int day = p / daySize;

		int timeS = p % daySize;
	 
		int room = timeS / DAY_HOURS;

		timeS = timeS % DAY_HOURS;

		int dur = ( *it ).first->GetDuration();


		// check for room overlapping of classes
		bool ro = false;
		for( int i = dur - 1; i >= 0; i-- )
		{
			if( _slots[ p + i ].size() > 1 )
			{
				ro = true;
				break;
			}
		}
		// on room overlaping
		if( !ro )
			score++;

		_criteria[ ci + 0 ] = !ro;

		CourseClass* cc = ( *it ).first;
		//cout << room <<"-"<<endl;
 		room++;
		Room* r = Configuration::GetInstance().GetRoomById( room );// YBRAT COSTUL ====== NE RABOTAET DLY NE UPORYAD ZNA4ENII
		// does current room have enough seats
	 
		_criteria[ ci + 1 ] = r->GetNumberOfSeats() >= cc->GetNumberOfSeats(); 
		if( _criteria[ ci + 1 ] )
			score++;

		// does current room have computers if they are required
		_criteria[ ci + 2 ] = !cc->IsLabRequired() || ( cc->IsLabRequired() && r->IsLab() );
		if( _criteria[ ci + 2 ] )
			score++;

 
		bool po = false, go = false;
	 
		// check overlapping of classes for professors and student group
		for( int i = numberOfRooms, t = day * daySize + timeS; i > 0; i--, t += DAY_HOURS )
		{
			// for each hour of class
			for( int i = dur - 1; i >= 0; i-- )
			{
				// check for overlapping with other classes at same time
				const list<CourseClass*>& cl = _slots[ t + i ];
			//	cout << "slots"<<_slots[ t + i ] << endl;
				for( list<CourseClass*>::const_iterator it = cl.begin(); it != cl.end(); it++ )
				{
					if( cc != *it )
					{
						// professor overlaps?
						if( !po && cc->ProfessorOverlaps( **it ) )
							po = true;

			
						// student group overlaps?
						if( !go && cc->GroupsOverlap( **it ) ) 		 
							go = true;

						// both type of overlapping? no need to check more
						if( po && go )
							goto total_overlap;
					}
				}
			}
		}

total_overlap:
		// professors have no overlaping classes?
		if( !po )
			score++;
		_criteria[ ci + 3 ] = !po;

		// student groups has no overlaping classes?
		if( !go )
			score++;
		_criteria[ ci + 4 ] = !go;
	}
	 ////////////////////////////
	 if ((float)score / ( Configuration::GetInstance().GetNumberOfCourseClasses() *5) >= 1) {
	 	ci = 0;
	 	 
for(  map<CourseClass*, int>::const_iterator it = _classes.begin(); it != _classes.end(); ++it, ci += 6 )
	{
		// coordinate of time-space slot
		int p = ( *it ).second;

		int day = p / daySize;

		//cout << day << "day" << endl;
		int timeS = p % daySize;
	 
		int room = timeS / DAY_HOURS;

		timeS = timeS % DAY_HOURS;

		int dur = ( *it ).first->GetDuration();
		// List of classes that group attends
     	list<StudentsGroup*> gr  = ( *it ).first->GetGroups();
     for(list<StudentsGroup*>::const_iterator iter = gr.begin(); iter != gr.end(); iter++ )
		{
			mymap[day][(*iter)->GetId()][timeS] = dur;
		}
		}
	bool windows = false;
    for (int q = 0; q < 6 && !windows  ; q++) {
      for (int g = 0; g < numberOfGroups  && !windows ; g++) {
      auto  ender = mymap[q][g].end();
      if (mymap[q][g].size() > 1) {
        ender--;
      
        for (auto iter = mymap[q][g].begin(); iter != ender; iter++) {
         auto tmp = iter;
          auto tmp2 = ++iter;
            if (  tmp->first + tmp->second  != tmp2->first ) {
             windows =true;
            }	else score++;
          iter --;
      }
     } 
     else if (mymap[q][g].size() == 1)
     	{score++;}
   }
}

} 
		 cout << Configuration::GetInstance().GetNumberOfCourseClasses() *6 << "->" << score << endl;
	// calculate fitess value based on score
	_fitness = (float)score / ( Configuration::GetInstance().GetNumberOfCourseClasses() *6); 
	if (_fitness == 1) 
		return true;
	else 
		return false;
		*/
}

int main() {
	TestCalculateFitness();	
	return 0;
}