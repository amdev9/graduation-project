
#include "ChildView.h"

#include "Configuration.h"
#include "TestFitness.h"
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

void CChildView::Printer(int icase) 
{
	PGconn     *conn;
	conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
    if (PQstatus(conn) == CONNECTION_BAD) {
       puts("We were unable to connect to the database");
    }
	int nr = Configuration::GetInstance().GetNumberOfRooms();
	int numofcla = Configuration::GetInstance().GetNumberOfCourseClasses();
	
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

 	std::string sSQL;
  	sSQL.append("INSERT INTO cbrcases VALUES ('");
  	sSQL.append(id.str().c_str());
  	sSQL.append("', '");
 	sSQL.append(numofclas.str().c_str());
  	sSQL.append("', '");
   	sSQL.append(numofprofs.str().c_str());  
  	sSQL.append("', '");
  	sSQL.append(numofgroups.str().c_str());
  	sSQL.append("', '");
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
	
	_schedule  = Algorithm::GetInstance().GetBestChromosome();
	if( _schedule )
	{
		const  map<CourseClass*, int>& classes = _schedule->GetClasses();
		int ci = classes.size() ;
	  
	  	if (_schedule->GetFitness()>=1) {
	  		cout << "fitness--->" << _schedule->GetFitness() << endl;
	  		int  idev =0;
	  	 	
	  	 	std::ostringstream idcase;
			idcase << ids;

			for(  map<CourseClass*, int>::const_iterator it= classes.begin(); it != classes.end(); ++it ) //, ci += 5 
			{
				CourseClass* c = ( *it ).first;
				int p = ( *it ).second;
				int t = p % ( nr * DAY_HOURS );
				int d = p / ( nr * DAY_HOURS ) + 1;
				int r = t / DAY_HOURS;
				t = t % DAY_HOURS + 1;
			 	 
				std::string s2SQL;
				std::string tr("true");
				std::string fl("false");
  			 	s2SQL.append("INSERT INTO courseevents VALUES ('");		  
  			    s2SQL.append( std::to_string( ci*ids -idev).c_str() );
  			    s2SQL.append("', '");
			    
			    int realID = Configuration::GetInstance().MapRoomId( r+1) ;
			    s2SQL.append(  std::to_string(realID).c_str() );
			    s2SQL.append("', '");
			  //  cout << r <<"<----"<< endl;
			     	//?!?if (Configuration::GetInstance().GetRoomById( l+m+1 )->IsLab()) { 
			    if (Configuration::GetInstance().GetRoomById( r)->IsLab()) { //r
			     	  s2SQL.append(tr.c_str()); 
			    }
			    else {
			    	s2SQL.append( fl.c_str());
			    }
				s2SQL.append("', '");
				s2SQL.append(  std::to_string(t).c_str() );
		  		s2SQL.append("', '");
		  		s2SQL.append( std::to_string(d).c_str());
		  		s2SQL.append("', '");
		 		s2SQL.append( std::to_string(c->GetDuration()).c_str() );
		 		s2SQL.append("', '");
			 	s2SQL.append( c->GetCourse().GetName().c_str());
				s2SQL.append("', '");
				s2SQL.append(  c->GetProfessor().GetName().c_str() );
				s2SQL.append("', '");		

				string str;	 
				for( list<StudentsGroup*>::const_iterator it = c->GetGroups().begin(); it != c->GetGroups().end(); ++it )
				{
					str += std::to_string(( *it )->GetId()).c_str();
					str += "/";
				}

	 			s2SQL.append(str );
				s2SQL.append("', '");		
				s2SQL.append(idcase.str().c_str());
				s2SQL.append("')");
			
				cout << s2SQL << endl;

 				PGresult *res2 = PQexec(conn, s2SQL.c_str());
 				if (PQresultStatus(res2) != PGRES_COMMAND_OK) {
        			printf("Insert courseevents record failed");
       				PQclear(res2);
       			}
       			printf("Insert courseevents record - OK\n");
  				s2SQL.clear();

  				idev++;
  			}
  		}	
  	}
  	PQfinish(conn);
  }


void CChildView::OnFileStart()
{
    Algorithm::GetInstance().Start();
}

void CChildView::OnFileTest()
{
      Algorithm::GetInstance().Test();
}

void CChildView::ReadDataFromDB()
{	 
	Configuration::GetInstance().ReadDatabase();
}

void CChildView::ReadDataTest()
{
	TestFitness::GetInstance().TestCalculateFitness();
}

int main(int argc, char* argv[])
{
	int i = 1;
	CChildView *a = new CChildView();
    a->ReadDataFromDB();

	bool test = (int)argv[1];
	if (!test) {
    	a->OnFileStart();
    	while (i <= 1) {
			a->Printer(i);
			i++;
		}	
	} else {
		a->ReadDataTest();
	 	a->OnFileTest();
	}
	return 0;
} 

