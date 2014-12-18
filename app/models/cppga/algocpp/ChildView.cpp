
#include "ChildView.h"

#include "Configuration.h"
#include "Room.h"
#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <postgresql/libpq-fe.h>


using namespace std;

 
CChildView::CChildView() : _schedule(NULL),
	_running(false)
{
	 Algorithm::GetInstance().GetObserver()->SetWindow( this );
}

CChildView::~CChildView()
{
	if( _schedule )
		delete _schedule;
}

void CChildView::SetSchedule(const Schedule* schedule)
{

	if( _schedule )
		delete _schedule;

	_schedule = schedule->MakeCopy( false );


}

void CChildView::SetNewState(AlgorithmState state)
{
	_running = state == AS_RUNNING;
}


const int ROOM_CELL_WIDTH = 85;
const int ROOM_CELL_HEIGHT = 50;

const int ROOM_MARGIN_WIDTH = 50;
const int ROOM_MARGIN_HEIGHT = 50;

const int ROOM_COLUMN_NUMBER = DAYS_NUM + 1;
const int ROOM_ROW_NUMBER = DAY_HOURS + 1;

const int ROOM_TABLE_WIDTH = ROOM_CELL_WIDTH * ROOM_COLUMN_NUMBER + ROOM_MARGIN_WIDTH;
const int ROOM_TABLE_HEIGHT = ROOM_CELL_HEIGHT * ROOM_ROW_NUMBER + ROOM_MARGIN_HEIGHT;

void CChildView::Printer(int icase) 
{
	 
 PGconn     *conn;
      conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
 
         if (PQstatus(conn) == CONNECTION_BAD) {
                 puts("We were unable to connect to the database");
          
      }



	int nr = Configuration::GetInstance().GetNumberOfRooms();


  //const char * id;
   
int  numofcla = Configuration::GetInstance().GetNumberOfCourseClasses();

std::ostringstream numofclas;
numofclas << numofcla;

int numofprof =  Configuration::GetInstance().GetNumberOfProfessors();
std::ostringstream numofprofs;
numofprofs << numofprof;

int numofgroup = Configuration::GetInstance().GetNumberOfStudentGroups();
std::ostringstream numofgroups;
numofgroups << numofgroup;
  
std::ostringstream numofrooms;
numofrooms << nr;

 
std::string del2SQL;
 del2SQL.append("delete from courseevents; delete from cbrcases;");
   PGresult *del2res = PQexec(conn, del2SQL.c_str());

    if (PQresultStatus(del2res) != PGRES_COMMAND_OK)
    {
        printf("Insert employee record failed");
        PQclear(del2res);
    }
     printf("delete from courseevents, cbrcases- OK\n");

 
  int ids = icase;	////////////////////////
  

std::ostringstream id;
id << ids;


 //id = "4";
  
 //cout << "ids case" << id.str().c_str() << endl;
  std::string sSQL;
  sSQL.append("INSERT INTO cbrcases VALUES ('");
    
  sSQL.append(id.str().c_str());
  sSQL.append("', '");
  sSQL.append(numofclas.str().c_str());
  sSQL.append("', '");
  //cout << numofprofs.str().c_str() <<  " "; 
  sSQL.append(numofprofs.str().c_str());  
  sSQL.append("', '");
  //cout << numofgroups.str().c_str() <<  " "; 
  sSQL.append(numofgroups.str().c_str());
  sSQL.append("', '");
 // cout << numofrooms.str().c_str() <<  " "; 
  sSQL.append(numofrooms.str().c_str());
  sSQL.append("')");
 
  // Execute with sql statement
  PGresult *res = PQexec(conn, sSQL.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Insert cbrcases record failed");
        PQclear(res);
        
    }

  printf("Insert cbrcases record - OK\n");



  
  
   	 //	std::string s2SQL;
  	//	s2SQL.append("INSERT INTO courseevents VALUES ('");
  			//int  idev =0;
  		 
	
	// for( int k = 1; k < nr+1; k++ )
	// {
		//for( int i = 0; i < ROOM_COLUMN_NUMBER; i++ )
		//{
		//	for( int j = 0; j < ROOM_ROW_NUMBER; j++ )
		//	{
		//		int l = k % 2;
		//		int m = k / 2;
			 

				//	if( i == 0 || j == 0 )
				//				dc.Rectangle( rect );

				
				//if( i == 0 && j == 0 )  {			 
				

					//idev++;
  			// 		s2SQL.append( std::to_string(idev).c_str() );
			  //   	s2SQL.append("', '");
  		 // 	    	s2SQL.append(Configuration::GetInstance().GetRoomById( k )->GetName().c_str() );
			  //   	s2SQL.append("', '");

					// std::string tr("true");
					// std::string fl("false");

			  //    	if (Configuration::GetInstance().GetRoomById( k )->IsLab()) { 
			  //    	  s2SQL.append(tr.c_str()); 
			  //    	}
			  //   	else {
			  //     	 	s2SQL.append( fl.c_str());
			  //     	}
					// s2SQL.append("', '");
	

				//	string str;
					//#roomname
					//cout << "Room:"<< Configuration::GetInstance().GetRoomById( k )->GetName().c_str() << endl;
					 
					//#lab
					//cout <<" Lab:"<< Configuration::GetInstance().GetRoomById( k )->IsLab()  << endl; // ? y : N
					 
					//cout<< " Seats:" << Configuration::GetInstance().GetRoomById( k )->GetNumberOfSeats() << endl;
					
				//}

				//if( i == 0 && j > 0 )
				//{
					//string str;
					//	 printf( "%d - %d\n", 9 + j - 1, 9 + j );
				//		}

				// if( j == 0 && i > 0 )
				// {
				// 	static const char* days[] = { "MON", "THU", "WED", "THR", "FRI", "SAT" };

				// 	cout << days[ i - 1 ] << " "; 
				// }
			
		//	}
		//}
//	}
 

 
_schedule  = Algorithm::GetInstance().GetBestChromosome();
	if( _schedule )
	{
		 
		// printf( "\nFitness: %f, Generation: %d\n", _schedule->GetFitness(),
		// 	Algorithm::GetInstance().GetCurrentGeneration() );

		 

		const  map<CourseClass*, int>& classes = _schedule->GetClasses();
		int ci = classes.size() ;

	  if (_schedule->GetFitness()>=1) {
	  	 int  idev =0 ;

	  	 
	  	 	std::ostringstream idcase;
				idcase << ids;

				/////////////////////////////////

		for(  map<CourseClass*, int>::const_iterator it= classes.begin(); it != classes.end(); ++it ) //, ci += 5 
		{
			 
			CourseClass* c = ( *it ).first;
			int p = ( *it ).second;

			int t = p % ( nr * DAY_HOURS );
			int d = p / ( nr * DAY_HOURS ) + 1;
			int r = t / DAY_HOURS;
			t = t % DAY_HOURS + 1;

			int l = r % 2;
			int m = r / 2;
				 
					std::string s2SQL;
					std::string tr("true");
					std::string fl("false");
  			 		s2SQL.append("INSERT INTO courseevents VALUES ('");		 
				 
		 		  
  					s2SQL.append( std::to_string( ci*ids -idev).c_str() );
  					
			    	s2SQL.append("', '");

			    	//cout << l+m+1 << endl;
  		 	    	s2SQL.append(Configuration::GetInstance().GetRoomById( l+ m+1)->GetName().c_str() );
			    	s2SQL.append("', '");
			     	if (Configuration::GetInstance().GetRoomById( l+m+1 )->IsLab()) { 
			     	  s2SQL.append(tr.c_str()); 
			     	}
			    	else {
			      	 	s2SQL.append( fl.c_str());
			      	}
					s2SQL.append("', '");


			
			//cout << l << "lc" << m << "r"<< r<< endl;
	        s2SQL.append(  std::to_string(t).c_str() );
		  	s2SQL.append("', '");
		  	s2SQL.append( std::to_string(d).c_str());
		  	s2SQL.append("', '");
		 	s2SQL.append( std::to_string(c->GetDuration()).c_str() );
		 	s2SQL.append("', '");
			//cout  << t << "-" << d << "-"<<c->GetDuration()  << endl;   //#meetingtime #meetingday #duration

  			s2SQL.append(c->GetCourse().GetName().c_str());
			s2SQL.append("', '");
			s2SQL.append(c->GetProfessor().GetName().c_str() );
			s2SQL.append("', '");		
		
			string str;	 
			for( list<StudentsGroup*>::const_iterator it = c->GetGroups().begin(); it != c->GetGroups().end(); ++it )
			{
				str += std::to_string(( *it )->GetId()).c_str();
				str += "/";
			}

			//if( c->IsLabRequired() )
			//	str += "\nLab";				//#lab

 			s2SQL.append(str );
			s2SQL.append("', '");		
			s2SQL.append(idcase.str().c_str());
			s2SQL.append("')");
			//k++;
			cout << s2SQL << endl;

 			PGresult *res2 = PQexec(conn, s2SQL.c_str());

 			if (PQresultStatus(res2) != PGRES_COMMAND_OK) {
        		printf("Insert courseevents record failed");
       			PQclear(res2);
    		}

  			printf("Insert courseevents record - OK\n");
  			s2SQL.clear();

  			idev++;
			//cout << str << endl;		//#groups
		}
		 
	  
     }	
	 }

 	 

	/*			
		int i = 0;
		for( vector<list<CourseClass*>>::const_iterator it = _schedule->GetSlots().begin(); it != _schedule->GetSlots().end(); ++it, ++i ) {
			
			if( ( *it ).size() > 0) 
			{

				int t = i % ( nr * DAY_HOURS );
				int d = i / ( nr * DAY_HOURS ) + 1;
				int r = t / DAY_HOURS;
				t = t % DAY_HOURS + 1;

				int l = r % 2;
				int m = r / 2;
				cout<<t<<d << l<< "-"<<m<< " m"<<endl;
      
		//	//	CRect rect( 
			//cout <<	ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1 <<endl;
			//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1 <<endl;
			//		cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH<<endl;
				//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( t + 1 ) * ROOM_CELL_HEIGHT <<endl;

			//	dc.Rectangle( rect );
			 	
			}
		}
		*/
   
      PQfinish(conn);
 }


void CChildView::OnFileStart()
{

    Algorithm::GetInstance().Start();
	//DWORD tid;
	//HANDLE thread = CreateThread( NULL, 0, StartAlg, NULL, 0, &tid );	//one thread exec . no need ahother
	//CloseHandle( thread );

}



void CChildView::ReadDataFromDB()
{
	 
		Configuration::GetInstance().ReadDatabase();
	
}

// void CChildView::InsertDataCBR() {
// 	Configuration::GetInstance().InsertCBR();

   

// }

int main()
{

	int i = 1;
	CChildView *a = new CChildView();
	a->ReadDataFromDB();
	while (i <= 1) {
		a->OnFileStart();
		a->Printer(i);
		i++;
	}
	//a->InsertDataCBR();	 
	return 0;
} 

