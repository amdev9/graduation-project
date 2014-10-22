 

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

/*
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_START, &CChildView::OnFileStart)
	ON_COMMAND(ID_FILE_OPEN_CONFIGURATION, &CChildView::OnFileOpenConfiguration)
	

END_MESSAGE_MAP()

// CChildView message handlers
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}
*/
const int ROOM_CELL_WIDTH = 3;
const int ROOM_CELL_HEIGHT = 2;

const int ROOM_MARGIN_WIDTH = 2;
const int ROOM_MARGIN_HEIGHT = 2;

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
			 

//			CRect rect( 
				//	 cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + i * ROOM_CELL_WIDTH - 1 <<endl;
				//	cout <<  ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + j * ROOM_CELL_HEIGHT - 1 <<endl;
				//	cout <<  ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( i + 1 ) * ROOM_CELL_WIDTH<<endl;
				//	 cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( j + 1 ) * ROOM_CELL_HEIGHT <<endl;

				if( i == 0 || j == 0 )
	//				dc.Rectangle( rect );

				if( i == 0 && j == 0 )
				{
					 
			
					// rect.bottom -= rect.Height() / 2;
					// dc.Rectangle( rect );
 
					string str;
					printf( "\nRoom: %s", Configuration::GetInstance().GetRoomById( k )->GetName().c_str() );
					// dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

					// rect.MoveToY( rect.bottom - 1 );

					// rect.right -= rect.Width() / 2 + 7;
					// dc.Rectangle( rect );

					printf( " Lab: %c", Configuration::GetInstance().GetRoomById( k )->IsLab() ? 'Y' : 'N' );
					// dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

					// rect.MoveToX( rect.right - 1 );
					// rect.right += 14;

					printf( " Seats: %d \n", Configuration::GetInstance().GetRoomById( k )->GetNumberOfSeats() );
					// dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
				}



				if( i == 0 && j > 0 )
				{
					//string str;
				//	 printf( "%d - %d\n", 9 + j - 1, 9 + j );

					// dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
				}

				if( j == 0 && i > 0 )
				{
					static const char* days[] = { "MON", "THU", "WED", "THR", "FRI", "SAT" };

					cout << days[ i - 1 ] << " ";//, 3, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
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


			// CRect rect( 
			// cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1 <<endl;
			// cout<< ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1 <<endl;
			// cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH<<endl;
			// cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT +  (t + c->GetDuration() ) *ROOM_CELL_HEIGHT  <<endl;
cout  << t << "--" << d <<endl;
			// dc.Rectangle( rect );

			string str;
			printf( "%s\n%s\n/", c->GetCourse().GetName().c_str(), c->GetProfessor().GetName().c_str() );

			//string str;
			for( list<StudentsGroup*>::const_iterator it = c->GetGroups().begin(); 
				it != c->GetGroups().end(); ++it )
			{
				str += ( *it )->GetName().c_str();
				str += "/";
			}

			if( c->IsLabRequired() )
				str += "\nLab";

/*			rect.top += 5;
			rect.bottom -= 5;
			rect.left += 5;
			rect.right -= 5;
			 
			
			dc.DrawText( str, rect, DT_CENTER | DT_WORDBREAK );
  
			dc.SetTextColor( RGB( 0, 0, 0 ) );
*/			
			cout << str << endl;
		}
		 
		 	}
	}	
	 
}

/* hz za4em
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
				//cout << l<<m<< " m"<<endl;

		//	//	CRect rect( 
			//cout <<	ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1 <<endl;
			//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1 <<endl;
			//		cout << ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH<<endl;
				//	cout << ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( t + 1 ) * ROOM_CELL_HEIGHT <<endl;

			//	dc.Rectangle( rect );
			 
			
			}
		}

*/


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

int main()
{


	CChildView *a = new CChildView();
	a->ReadDataFromDB();
	a->OnFileStart();
		a->Printer();
		 
		  //     Configuration::GetInstance().ReadDatabase();
	 // Algorithm::GetInstance().Start();

	//a->ReadDataFromDB();

//	a->OnFileStart();
	return 0;
} 

