// ChildView.cpp : implementation of the CChildView class
//

 

#include "ChildView.h"

#include "Algorithm\Configuration.h"
#include "Algorithm\Room.h"
#include "Algorithm\Schedule.h"
#include <iostream>


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


	Invalidate();
}

void CChildView::SetNewState(AlgorithmState state)
{
	_running = state == AS_RUNNING;
}

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

const int ROOM_CELL_WIDTH = 85;
const int ROOM_CELL_HEIGHT = 50;

const int ROOM_MARGIN_WIDTH = 50;
const int ROOM_MARGIN_HEIGHT = 50;

const int ROOM_COLUMN_NUMBER = DAYS_NUM + 1;
const int ROOM_ROW_NUMBER = DAY_HOURS + 1;

const int ROOM_TABLE_WIDTH = ROOM_CELL_WIDTH * ROOM_COLUMN_NUMBER + ROOM_MARGIN_WIDTH;
const int ROOM_TABLE_HEIGHT = ROOM_CELL_HEIGHT * ROOM_ROW_NUMBER + ROOM_MARGIN_HEIGHT;

void CChildView::OnPaint() 
{
	CPaintDC wndDC(this);
	 
	CRect clientRect;
	GetClientRect( clientRect );

	CDC dc;
	CBitmap bmp;
	dc.CreateCompatibleDC( &wndDC );
	bmp.CreateCompatibleBitmap( &wndDC, clientRect.Width(), clientRect.Height() );
	dc.SelectObject( &bmp );


	int nr = Configuration::GetInstance().GetNumberOfRooms();
	for( int k = 0; k < nr; k++ )
	{
		for( int i = 0; i < ROOM_COLUMN_NUMBER; i++ )
		{
			for( int j = 0; j < ROOM_ROW_NUMBER; j++ )
			{
				int l = k % 2;
				int m = k / 2;

				CRect rect( 
					 ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + i * ROOM_CELL_WIDTH - 1,
					 ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + j * ROOM_CELL_HEIGHT - 1,
					 ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( i + 1 ) * ROOM_CELL_WIDTH,
					 ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( j + 1 ) * ROOM_CELL_HEIGHT );

				if( i == 0 || j == 0 )
					dc.Rectangle( rect );

				if( i == 0 && j == 0 )
				{
			
					rect.bottom -= rect.Height() / 2;
					dc.Rectangle( rect );

					CString str;
					str.Format( "Room: %s", Configuration::GetInstance().GetRoomById( k )->GetName().c_str() );
					dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

					rect.MoveToY( rect.bottom - 1 );

					rect.right -= rect.Width() / 2 + 7;
					dc.Rectangle( rect );

					str.Format( "Lab: %c", Configuration::GetInstance().GetRoomById( k )->IsLab() ? 'Y' : 'N' );
					dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

					rect.MoveToX( rect.right - 1 );
					rect.right += 14;

					str.Format( "Seats: %d", Configuration::GetInstance().GetRoomById( k )->GetNumberOfSeats() );
					dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
				}



				if( i == 0 && j > 0 )
				{
					CString str;
					str.Format( "%d - %d", 9 + j - 1, 9 + j );

					dc.DrawText( str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
				}

				if( j == 0 && i > 0 )
				{
					static const char* days[] = { "MON", "THU", "WED", "THR", "FRI", "SAT" };

					dc.DrawText( days[ i - 1 ], 3, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
				}
			}
		}
	}
 


	if( _schedule )
	{
		CString fit;
		fit.Format( "Fitness: %f, Generation: %d", _schedule->GetFitness(),
			Algorithm::GetInstance().GetCurrentGeneration() );

		dc.TextOutA( 10,  10, fit );

		const hash_map<CourseClass*, int>& classes = _schedule->GetClasses();
		int ci = 0;

	 
		if (_schedule->GetFitness()>=1) {
		for( hash_map<CourseClass*, int>::const_iterator it= classes.begin(); it != classes.end(); ++it, ci += 5 )
		{
			CourseClass* c = ( *it ).first;
			int p = ( *it ).second;

			int t = p % ( nr * DAY_HOURS );
			int d = p / ( nr * DAY_HOURS ) + 1;
			int r = t / DAY_HOURS;
			t = t % DAY_HOURS + 1;

			int l = r % 2;
			int m = r / 2;

			CRect rect( 
				 ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1,
				 ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1,
				ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH,
				 ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( t + c->GetDuration() ) * ROOM_CELL_HEIGHT );

			dc.Rectangle( rect );

			CString str;
			str.Format( "%s\n%s\n/", c->GetCourse().GetName().c_str(), c->GetProfessor().GetName().c_str() );

			for( list<StudentsGroup*>::const_iterator it = c->GetGroups().begin(); 
				it != c->GetGroups().end(); ++it )
			{
				str += ( *it )->GetName().c_str();
				str += "/";
			}

			if( c->IsLabRequired() )
				str += "\nLab";

			rect.top += 5;
			rect.bottom -= 5;
			rect.left += 5;
			rect.right -= 5;
			 
			
			dc.DrawText( str, rect, DT_CENTER | DT_WORDBREAK );
  
			dc.SetTextColor( RGB( 0, 0, 0 ) );
		
		}
		 

		int i = 0;
		for( vector<list<CourseClass*>>::const_iterator it = _schedule->GetSlots().begin();
			it != _schedule->GetSlots().end(); ++it, ++i )
		{
			if( ( *it ).size() > 1 )
			{
				int t = i % ( nr * DAY_HOURS );
				int d = i / ( nr * DAY_HOURS ) + 1;
				int r = t / DAY_HOURS;
				t = t % DAY_HOURS + 1;

				int l = r % 2;
				int m = r / 2;

				CRect rect( 
					ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + d * ROOM_CELL_WIDTH - 1,
					ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + t * ROOM_CELL_HEIGHT - 1,
					ROOM_TABLE_WIDTH * l + ROOM_MARGIN_WIDTH + ( d + 1 ) * ROOM_CELL_WIDTH,
					ROOM_TABLE_HEIGHT * m + ROOM_MARGIN_HEIGHT + ( t + 1 ) * ROOM_CELL_HEIGHT );

				dc.Rectangle( rect );
			}
		}
	}
	}	
	wndDC.BitBlt( 0, 0, clientRect.Width(), clientRect.Height(), &dc, 0, 0, SRCCOPY );
}

DWORD WINAPI StartAlg(LPVOID param)
{
	Algorithm::GetInstance().Start();
	return 0;
}

void CChildView::OnFileStart()
{
	DWORD tid;
	HANDLE thread = CreateThread( NULL, 0, StartAlg, NULL, 0, &tid );	//one thread exec . no need ahother
	CloseHandle( thread );
}



void CChildView::OnFileOpenConfiguration()
{
	CFileDialog dlg( TRUE, NULL, NULL, 0, 
		"Class Schedule Config Files (*.cfg)|*.cfg|All Files (*.*)|*.*|", this );

	 
	if( dlg.DoModal() == IDOK )
	{
		Configuration::GetInstance().ParseFile( dlg.GetFileName().GetBuffer() );

	Invalidate();
	}
}
