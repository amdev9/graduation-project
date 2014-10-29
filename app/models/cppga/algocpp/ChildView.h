class Schedule;
//enum AlgorithmState;

enum AlgorithmState
{
	//AS_USER_STOPED,
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

	// void Printer();					// basic output function
 
public:
void Printer();
	  void OnFileStart();
	
  void ReadDataFromDB();
	void InsertDataCBR();
 
 
};

