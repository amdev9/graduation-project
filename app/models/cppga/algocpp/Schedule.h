
#include <list>
#include <map>

#include "CourseClass.h"
#include <vector>

class CChildView;
class Schedule;
class Algorithm;

// Number of working hours per day
#define DAY_HOURS	12
// Number of days in week
#define DAYS_NUM	6 //5

enum AlgorithmState;

// Algorithm's observer
class ScheduleObserver
{

private:
	// Window which displays schedule
	
	CChildView* _window;
	// Called when algorithm starts execution
 

public:

	// Initializes observer 
	ScheduleObserver(): _window(NULL) {}
	// Frees used resources
	 
	~ScheduleObserver() {}
	 
	
	// Handles event that is raised when algorithm finds new best chromosome
	void NewBestChromosome(const Schedule& newChromosome);

	// Handles event that is raised when state of execution of algorithm is changed
	void EvolutionStateChanged(AlgorithmState newState);

	// Sets window which displays schedule
	inline void SetWindow(CChildView* window) { _window = window;} 

}; 

// Schedule chromosome
class Schedule
{

	//friend class ScheduleObserver;

private:

	// Number of crossover points of parent's class tables
	int _numberOfCrossoverPoints;

	// Number of classes that is moved randomly by single mutation operation
	int _mutationSize;

	// Probability that crossover will occure
	int _crossoverProbability;

	// Probability that mutation will occure
	int _mutationProbability;

	// Fitness value of chromosome
	float _fitness;

	// Flags of class requiroments satisfaction
	vector<bool> _criteria;

	// Time-space slots, one entry represent one hour in one classroom
	vector<list<CourseClass*>> _slots;

	// Class table for chromosome
	// Used to determine first time-space slot used by class
	 map<CourseClass*, int> _classes;

public:

	// Initializes chromosomes with configuration block (setup of chromosome)
	Schedule(int numberOfCrossoverPoints, int mutationSize,
		int crossoverProbability, int mutationProbability);

	// Copy constructor
	Schedule(const Schedule& c, bool setupOnly);

	// Makes copy ot chromosome
	Schedule* MakeCopy(bool setupOnly) const;

	// Makes new chromosome with same setup but with randomly chosen code
	Schedule* MakeNewFromPrototype() const;

	///
	void TestCorrection() const;
	///

	// Performes crossover operation using to chromosomes and returns pointer to offspring
	Schedule* Crossover(const Schedule& parent2) const;

	// Performs mutation on chromosome
	void Mutation();

	// Calculates fitness value of chromosome
	void CalculateFitness(int);

	// Returns fitness value of chromosome
	float GetFitness() const { return _fitness; }

	// Returns reference to table of classes
	inline const  map<CourseClass*, int>& GetClasses() const { return _classes; }

	// Returns array of flags of class requiroments satisfaction
	inline const vector<bool>& GetCriteria() const { return _criteria; }

	// Return reference to array of time-space slots
	inline const vector<list<CourseClass*>>& GetSlots() const { return _slots; }

};

// Genetic algorithm
class Algorithm
{

private:

	// Population of chromosomes
	vector<Schedule*> _chromosomes;

	// Inidicates wheahter chromosome belongs to best chromosome group
	vector<bool> _bestFlags;

	// Indices of best chromosomes
	vector<int> _bestChromosomes;

	// Number of best chromosomes currently saved in best chromosome group
	int _currentBestSize;

	// Number of chromosomes which are replaced in each generation by offspring
	int _replaceByGeneration;

	// Pointer to algorithm observer
	ScheduleObserver* _observer;

	// Prototype of chromosomes in population
	Schedule* _prototype;

	// Current generation
	int _currentGeneration;

	// State of execution of algorithm
	AlgorithmState _state;

	// Pointer to global instance of algorithm
	static Algorithm* _instance;

	// Synchronization of creation and destruction of global instance
 //static CCriticalSection _instanceSect;

public:

	// Returns reference to global instance of algorithm
	static Algorithm& GetInstance();

	// Frees memory used by gloval instance
	static void FreeInstance();

	// Initializes genetic algorithm
	Algorithm(int numberOfChromosomes, int replaceByGeneration, int trackBest,
		Schedule* prototype, ScheduleObserver* observer);

	// Frees used resources
	~Algorithm();

	// Starts and executes algorithm
	void Start();

	///
	void Test();
	///

	// Returns pointer to best chromosomes in population
	Schedule* GetBestChromosome() const;

	// Returns current generation
	inline int GetCurrentGeneration() const { return _currentGeneration; }

	// Returns pointe to algorithm's observer
	inline ScheduleObserver* GetObserver() const { return _observer; }

private:

	// Tries to add chromosomes in best chromosome group
	void AddToBest(int chromosomeIndex);

	// Returns TRUE if chromosome belongs to best chromosome group
	bool IsInBest(int chromosomeIndex);

	// Clears best chromosome group
	void ClearBest();

};

