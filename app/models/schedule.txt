

DAY_HOURS=12 #Number of working hours per day
DAYS_NUM=5     #Number of days in week

class Schedule
def res 
	result = `/home/alex/diplom/gaschedule/app/models/cppga/algocpp/a.out` 
	result
end 
	end
'''

class CChildView

	include AlgorithmState
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

	include AlgorithmState
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
	end

		#Handles event that is raised when state of execution of algorithm is changed
	def evolutionStateChanged( newState)

		if _window != nil
			_window.setNewState( newState )
		end
		newState != AS_RUNNING ? releaseEvent : blockEvent  ##????
	end
end 
 





class Schedule

	include AlgorithmState
		@mutationSize 
		@numberOfCrossoverPoints 
	    @crossoverProbability 
		@mutationProbability  
		@fitness
	
	def initialize ( numberOfCrossoverPoints,  mutationSize,
				    crossoverProbability,  mutationProbability)
		@mutationSize = mutationSize
		@numberOfCrossoverPoints = numberOfCrossoverPoints
	    @crossoverProbability = crossoverProbability
		@mutationProbability = mutationProbability
		@fitness = 0
     ###
      @slots = []
	  @criteria = []
	  @classes = Hash.new
	end
	attr_accessor  :mutationSize, :numberOfCrossoverPoints, :crossoverProbability, :mutationProbability, :fitness
	
	def getFitness
	    @fitness
	end
	def getClasses
		@classes
	end
	def getCriteria
		@criteria
	end
	def getSlots
		@slots
	end
	def copy_constructor (  c, setupOnly)
		 if !setupOnly  
			@slots = c.slots
			@classes = c.classes
			@criteria = c.criteria
			@fitness = c.fitness
	 
		end
		@numberOfCrossoverPoints = c.numberOfCrossoverPoints
		@mutationSize = c.mutationSize
		@crossoverProbability = c.crossoverProbability
		@mutationProbability = c.mutationProbability
	end
   # copy constructor here NO NEED
    def makeCopy (setupOnly)	
    	Schedule.new(self, setupOnly)
    end
    def makeNewFromPrototype
    	size = slots.size
    	newChromosome = Schedule.new(self, true)
    	c =  Cla.order(:id) #getCourseClasses					 
    	c.each do |it|
			nr = Room.all.size #getNumberOfRooms				#room.all.size
    		dur = it.duration # getDuration                         # cla.duration
    		day = rand(DAYS_NUM)  
		    room = rand(nr)
		    time = rand( DAY_HOURS + 1 - dur )
		    pos = day * nr * DAY_HOURS + room * DAY_HOURS + time
		 
		  	newChromosome.slots.each_with_index do |i|
				slots[pos + i] = it 
			end
			newChromosome.classes[:it] = pos 
		end
   		newChromosome.calculateFitness
		return newChromosome
   	end
	 
	def crossover (  parent2)
		if  rand(100) > crossoverProbability 
			return Schedule.new(self,false)
		end
		n = Shedule.copy_constructor (self, true)  ####&&&
		size = classes.size
		cp = []
		for i in numberOfCrossoverPoints
			if i > 0
				while true
					p = rand(size)
					if( !cp[ p ] )
					cp[ p ] = true
					break
					end
				i=i-1
				end
			end
		end
	    first = rand(2) == 0
	  
		for  i in size
			
			if( first )
			    classes.each_with_index  {  |(cclass, int), cindex|  #index no need
				n.classes[:cclass]= int
				for   i in 0..cclass.duration - 1 			#cla.duration.GetDuration()
				  n.slots[ int + i ] << cclass
				end
				}
			else
			    parent2.classes.each_with_index  {  |(nclass, nint), nindex| #index no need
				n.classes[:nclass]= nint
				for   i in 0.. nclass.duration - 1 		#cla.duration
				  n.slots[ nint + i ] << nclass
				end
			}
			end
			if( cp[ i ] )
				first = !first
			end
			
			
		end 
		n.calculateFitness
		return n
	end
	
	def mutation
		if rand(100) > mutationProbability
			return
		numberOfClasses = classes.size
		size  = slots.size
		for i in 0..mutationSize
			mpos = rand(numberOfClasses)
			pos1 = 0
			classes.each_with_index { |(k,v),it|
				while mpos > 0
				  mpos= mpos - 1
				end
				pos1 = v
				cc1 = k
				 nr = Room.all.size #getNumberOfRooms   			#Room.all.size 
					dur = cc1.duration #getDuration			#cla.duration
					day = rand( DAYS_NUM)
					room = rand( nr)
					time = rand( DAY_HOURS + 1 - dur )
					pos2 = day * nr * DAY_HOURS + room * DAY_HOURS + time
 
	            for i in  0.. dur - 1 
					cl = slots[ pos1 + i ]
					slots.each { |it|  	
						if( it == cc1 )
							cl.delete_at( it )
							break
						end
					}
				end
					slots[ pos2 + i ]<< cc1
				classes[ :cc1 ] = pos2
			}
		end
		calculateFitness
	end
	
	def calculateFitness
		score  = 0
	    numberOfRooms = Room.all.size #getNumberOfRooms		 #Room.all.size
		daySize = DAY_HOURS * numberOfRooms
		ci = 0
		classes.each_with_index { |(k,v),index| 
 
		# coordinate of time-space slot
		  p = v 
		 day = p / daySize	
		 time = p % daySize
		 room = time / DAY_HOURS
		time = time % DAY_HOURS
		 dur = k.duration #getDuration 				#cla.duration 

		# check for room overlapping of classes			 
		ro = false
		for i in 0..dur-1
			if  slots[ p + i ].size > 1 
				ro = true
				break
			end
		end

		#on room overlaping
		if( !ro )
			score = score + 1
		end
		criteria[ ci + 0 ] = !ro

		 cc =  k
		 r =  Room.find(room) #getInstance.getRoomById( room )    #Room.find(room)
		# does current room have enough seats
		criteria[ ci + 1 ] = (r.size >= cc.size) #getNumberOfSeats >= cc.getNumberOfSeats   #r.size ..
		if( criteria[ ci + 1 ] )
			score = score +1
			end

		# does current room have computers if they are required
		criteria[ ci + 2 ] = !cc.lab || ( cc.lab && r.lab )     #r.lab cc.lab
		if( criteria[ ci + 2 ] )
			score = score + 1
			end

		 po = false
		 go = false
		# check overlapping of classes for professors and student groups
		i = numberOfRooms
		t = day * daySize + time
		while i > 0 
			# for each hour of class
			for  i in 0..dur - 1 
			
				# check for overlapping with other classes at same time
				cl = slots[ t + i ]
				cl.each do |it|
					if  cc != it 
						# professor overlaps?
						if !po && (cc.professor == it.professor )   #cc.professor = it.professor
							po = true
						end
						# student group overlaps?
						if !go && (cc.group == it.group) #groupsOverlap
							go = true
						end
						# both type of overlapping? no need to check more
						if  po && go 
							throw :total_overlap
							end
					end
				end
			end
			i = i - 1
			t += DAY_HOURS 
		end

     catch (:total_overlap) do

		# professors have no overlaping classes?
		if !po 
			score = score  + 1
			end
		criteria[ ci + 3 ] = !po

		# student groups has no overlaping classes?
		if  !go 
			score = score  + 1
		    end
		   
		   criteria [ci + 4 ] = !go
		ci +=5 
	 end
	}
	 
	  fitness = score / ( Cla.all.size * DAYS_NUM )   #C etInstance.getNumberOfCourseClasses
	end
end  

end


Algorithm.instance = nil

class Algorithm
	
	include AlgorithmState
	
	@chromosomes
	@bestFlags
	@bestChromosomes
	@currentBestSize
	@replaceByGeneration
	#@observer
	@prototype
	@currentGeneration
	@state
	@instance
	@instanceSect
	attr_accessor :chromosomes, :bestFlags, :bestChromosomes, :currentBestSize, :replaceByGeneration, :prototype, :currentGeneration,
		:state, :instance, :instanceSect
	def initialize( numberOfChromosomes,  replaceByGeneration,  trackBest,
					prototype) #ScheduleObserver* observer) 
					 @replaceByGeneration = replaceByGeneration
					 @currentBestSize = 0
					 @prototype = prototype
					# @observer = observer
					 @currentGeneration = 0 
					 @state = AS_USER_STOPED
	if numberOfChromosomes < 2 
		numberOfChromosomes = 2
	end
	if trackBest < 1 
		trackBest = 1
	end
		if replaceByGeneration < 1 
			replaceByGeneration = 1
			end
		if replaceByGeneration > (numberOfChromosomes - trackBest)   #ELSE IF
			replaceByGeneration = numberOfChromosomes - trackBest
			end
	for i in 0..chromosomes.size - 1 
		chromosomes[ i ] = nil
		bestFlags[ i ] = false
	end
		
	end
	 
	def getCurrentGeneration
		@currentGeneration
	end
   
	def freeInstance
		@instance = nil
	end



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



	def start
		if !prototype
			return
	    end
		if( state == AS_RUNNING )
			return
			end
			state = AS_RUNNING	
		
	clearBest
	i = 0
	chromosomes.each do |it|
		it = prototype.makeNewFromPrototype
		addToBest(i)
		i = i + 1
	end
	currentGeneration = 0 
	while( true )
		best=getBestChromosome
		if best.getFitness >= 1
		state = AS_CRITERIA_STOPPED
		break
		end
		
		 
		for  j in 0.. replaceByGeneration 		 
			 p1 = chromosomes[ rand(chromosomes.size)]	
			p2 = chromosomes[ rand( chromosomes.size) ]

			offspring[ j ] = p1.crossover( p2 )	  
			offspring[ j ].mutation						 
		end
	for  j in 0..replaceByGeneration  
			loop do
				#select chromosome for replacement randomly
				ci = rand(chromosomes.size)		
			 break if( isInBest( ci ) )	
			end			 
  
			chromosomes[ ci ] = offspring[ j ]			 
			addToBest( ci )          #######realization
		end

		 
		    if  best != getBestChromosome && observer 					########################!11
			observer.newBestChromosome( getBestChromosome)   ###ITOG
		    end
		currentGeneration = currentGeneration + 1
	end
	
	    if( observer )
		 
		observer.evolutionStateChanged( state )				###############################1!11
	    end
	

	
	
	def getBestChromosome
		chromosomes[ bestChromosomes[ 0 ] ]
	end

	def addToBest (chromosomeIndex)
		if ( currentBestSize == bestChromosomes.size && 
		chromosomes[ bestChromosomes[ currentBestSize - 1 ] ].getFitness >= 
		chromosomes[ chromosomeIndex ].getFitness ) || bestFlags[ chromosomeIndex ] 
			return
		end
		
		i = currentBestSize
    while i > 0
		if  i < bestChromosomes.size
			if chromosomes[ bestChromosomes[ i - 1 ] ].getFitness > 
				chromosomes[ chromosomeIndex ].getFitness 
				break
			end
			bestChromosomes[ i ] = bestChromosomes[ i - 1 ]
		
		else
			bestFlags[ bestChromosomes[ i - 1 ] ] = false
		end
		bestChromosomes[ i ] = chromosomeIndex
		bestFlags[ chromosomeIndex ] = true

	if currentBestSize < bestChromosomes.size 
		currentBestSize= currentBestSize + 1
	end
	i = i-1
	end
	end
	
	def isInBest( chromosomeIndex)
		return bestFlags[ chromosomeIndex ]
	end
	
	def clearBest
	    for i in 0.. bestFlags.size - 1 
		bestFlags[ i ] = false
	    end
	    currentBestSize = 0
	    return
	end
  end
end
 '''
