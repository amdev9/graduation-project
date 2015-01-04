 
class Schedule;

enum AlgorithmState
{
	AS_CRITERIA_STOPPED,
	AS_RUNNING
};

class CChildView  
{

public:

	CChildView();

	virtual ~CChildView();

private:

 
	Schedule* _schedule;

	bool _running;

public:

	void SetSchedule(const Schedule* schedule);
	void SetNewState(AlgorithmState state);


	
protected:

	 

protected:

  
public:
	void Printer(int icase);
	void OnFileStart();

	void OnFileTest();
	void ReadDataTest();
	  
  	void ReadDataFromDB();
};
