

class CChildView

def initialize
	_schedule = nil
	_running  = false
	Algorithm.getInstance.getObserver.setWindow(self)
end
	def setSchedule(  schedule)
	if _schedule != nil
	  _schedule = nil
	end
	_schedule = schedule.makeCopy( false )
	end
	
	def setNewState(state)
	  _running = state == AS_RUNNING
end
def printer
  if  _schedule!=nil 
	puts "Fitness: #{_schedule.getFitness} , Generation: #{Algorithm.getInstance.getCurrentGeneration}"	
	classes = _schedule.getClasses
	ci = 0
	classes.each { |(c,p)|
		t = p % ( nr * DAY_HOURS )
		d = p / ( nr * DAY_HOURS ) + 1
		r = t / DAY_HOURS
		t % DAY_HOURS + 1
		l = r % 2;
		m = r / 2;
		puts "#{c.getCourse.getName}\n#{c.getProfessor.getName}\n" 
		
	ci +=5
	}
  end

end
end

module AlgorithmState
	AS_USER_STOPED = 1
	AS_CRITERIA_STOPPED = 2
	AS_RUNNING = 3
end


class ScheduleObserver
def initialize
	_window = nil
	 
end
def setWindow( window) 
 _window = window
 end


#Handles event that is raised when algorithm finds new best chromosome
def newBestChromosome( newChromosome)
	if _window != nil
		_window.setSchedule( newChromosome )
end

#Handles event that is raised when state of execution of algorithm is changed
def evolutionStateChanged( newState)

	if _window != nil
		_window.setNewState( newState )
	newState != AS_RUNNING ? releaseEvent : blockEvent  ##????

end
 
include AlgorithmState
Algorithm._instance = nil

def getInstance

	#Thread.new
	if _instance == nil 
		// make prototype of chromosomes
	    prototype =   Schedule.new( 2, 2, 80, 3 )
		// make new global instance of algorithm using chromosome prototype
		_instance =  Algorithm.new( 100, 8, 5, prototype, new ScheduleObserver() )
	end
	return _instance;
end

def getObserver
	return _observer
end

def stop

#thread

	if _state == AS_RUNNING 
		_state = AS_USER_STOPED
		end
	#lock.Unlock()
end

