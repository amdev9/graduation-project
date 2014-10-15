
class Schedule;
enum AlgorithmState;



class CChildView : public CWnd
{

public:

	CChildView();

	virtual ~CChildView();

private:

	CCriticalSection _sect;

	Schedule* _schedule;

	bool _running;

public:

	void SetSchedule(const Schedule* schedule);
	void SetNewState(AlgorithmState state);


	
protected:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

	afx_msg void OnPaint();					// basic output function
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnFileStart();
	
	afx_msg void OnFileOpenConfiguration();
	
 
 
};

