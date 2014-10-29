
#include "ChildView.h"

#include "Configuration.h"
#include "Room.h"
#include "Schedule.h"
#include <iostream>
#include <stdio.h>

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

void CChildView::Printer() 
{
	 
 
	int nr = Configuration::GetInstance().GetNumberOfRooms();
	 
	for( int k = 1; k < nr+1; k++ )
	{
		for( int i = 0; i < ROOM_COLUMN_NUMBER; i++ )
		{
			for( int j = 0; j < ROOM_ROW_NUMBER; j++ )
			{
				int l = k % 2;
				int m = k / 2;
			 

				if( i == 0 || j == 0 )
	//				dc.Rectangle( rect );

				if( i == 0 && j == 0 )
				{
					 
		
 
					string str;
					//#roomname
					printf( "\nRoom: %s", Configuration::GetInstance().GetRoomById( k )->GetName().c_str() );
					 
					//#lab
					printf( " Lab: %c", Configuration::GetInstance().GetRoomById( k )->IsLab() ? 'Y' : 'N' );
					 
					printf( " Seats: %d \n", Configuration::GetInstance().GetRoomById( k )->GetNumberOfSeats() );
					
				}



				if( i == 0 && j > 0 )
				{
					//string str;
				//	 printf( "%d - %d\n", 9 + j - 1, 9 + j );

					 
				}

				if( j == 0 && i > 0 )
				{
					static const char* days[] = { "MON", "THU", "WED", "THR", "FRI", "SAT" };

					cout << days[ i - 1 ] << " "; 
				}
			
			}
		}
	}
 

//cout << _schedule << endl;
_schedule  = Algorithm::GetInstance().GetBestChromosome();
	if( _schedule )
	{
		 
		printf( "\nFitness: %f, Generation: %d\n", _schedule->GetFitness(),
			Algorithm::GetInstance().GetCurrentGeneration() );

		 

		const  map<CourseClass*, int>& classes = _schedule->GetClasses();
		int ci = 0;

	 
		if (_schedule->GetFitness()>=1) {
		for(  map<CourseClass*, int>::const_iterator it= classes.begin(); it != classes.end(); ++it, ci += 5 )
		{
			CourseClass* c = ( *it ).first;
			int p = ( *it ).second;

			int t = p % ( nr * DAY_HOURS );
			int d = p / ( nr * DAY_HOURS ) + 1;
			int r = t / DAY_HOURS;
			t = t % DAY_HOURS + 1;

			int l = r % 2;
			int m = r / 2;

			cout  << t << "-" << d << "-"<<c->GetDuration()  << endl;   //#meetingtime #meetingday #duration
		

			string str;
			printf( "%s\n%s\n/", c->GetCourse().GetName().c_str(), c->GetProfessor().GetName().c_str() );
			//#coursename #profname
			//string str;
			for( list<StudentsGroup*>::const_iterator it = c->GetGroups().begin(); 
				it != c->GetGroups().end(); ++it )
			{
				str += ( *it )->GetName().c_str();
				str += "/";
			}

			if( c->IsLabRequired() )
				str += "\nLab";				//#lab

					
			cout << str << endl;		//#groups
		}
		 
		 	}
	}	
	 


 
		int i = 0;
		for( vector<list<CourseClass*>>::const_iterator it = _schedule->GetSlots().begin();
			it != _schedule->GetSlots().end(); ++it, ++i )
		{
		//	cout << ( *it ).size() << endl;
			if( ( *it ).size() >= 1 )
			{
				int t = i % ( nr * DAY_HOURS );
				int d = i / ( nr * DAY_HOURS ) + 1;
				int r = t / DAY_HOURS;
				t = t % DAY_HOURS + 1;

				int l = r % 2;
				int m = r / 2;
				cout << l<< "-"<<m<< " m"<<endl;

		//	//	CRect rect( 
			//cout <<	ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1 <<endl;
			//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1 <<endl;
			//		cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH<<endl;
				//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( t + 1 ) * ROOM_CELL_HEIGHT <<endl;

			//	dc.Rectangle( rect );
			 
			
			}
		}

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

void CChildView::InsertDataCBR() {
	Configuration::GetInstance().InsertCBR();
}

int main()
{


	CChildView *a = new CChildView();
	a->ReadDataFromDB();
	//a->OnFileStart();
	//a->Printer();
	a->InsertDataCBR();	 
	return 0;
} 

