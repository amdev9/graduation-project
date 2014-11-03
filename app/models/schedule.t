
DAY_HOURS=12 #Number of working hours per day
DAYS_NUM=5     #Number of days in week



module AlgorithmState
	#AS_USER_STOPED = 1
	AS_CRITERIA_STOPPED = 2
	AS_RUNNING = 3
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
      @slots.insert(DAY_HOURS*DAYS_NUM*Room.all.size, 0)
      # @slsize = DAY_HOURS*DAYS_NUM*Room.all.size
	  @criteria = []
	  @classes = Hash.new
	end
	attr_accessor   :mutationSize, :fitness, :numberOfCrossoverPoints, :crossoverProbability, :mutationProbability, :slots, :size, :classes, 	:criteria
	def getFitness
	    @fitness
	end
	def getMut
		@mutationSize
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
	def copy_constructor (setupOnly)  #
		n = Schedule.new(0,0,0,0)
		 if !setupOnly  
			n.slots = self.slots
			n.classes = self.classes
			n.criteria = self.criteria
			n.fitness = self.fitness
	 
		end
		n.numberOfCrossoverPoints = self.numberOfCrossoverPoints
		n.mutationSize = self.mutationSize
		n.crossoverProbability = self.crossoverProbability
		n.mutationProbability = self.mutationProbability
		return n
	end
	    
    def makeCopy 	
    	@a = self #
    	puts 'copied'
    	@a
    end
     def makeNewFromPrototype
    	@size = self.slots.size
    	newChromosome = self
    	c =  Cla.order(:id) #getCourseClasses					 
    	c.each do |it|
			nr = Room.all.size #getNumberOfRooms				#room.all.size
    		dur = it.duration # getDuration                         # cla.duration
    		day = rand(DAYS_NUM)  
		    room = rand(nr)
		    time = rand( DAY_HOURS + 1 - dur )
		    pos = day * nr * DAY_HOURS + room * DAY_HOURS + time
		 
		  	newChromosome.slots.each_with_index do |(x),i|
				slots.insert(pos + i, it) 
			end
			newChromosome.classes[pos] = it
		end
   		newChromosome.calculateFitness
		return newChromosome
   	end

   	def crossover (parent2)
		if  rand(100) > crossoverProbability 
			return self.copy_constructor(false)
		end
		n = self.copy_constructor (true)  ####&&&
		n.size = classes.size
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
				  n.slots.insert( int + i ,cclass)
				end
				}
			else
			    parent2.classes.each_with_index  {  |(nclass, nint), nindex| #index no need
				n.classes[:nclass]= nint
				for   i in 0.. nclass.duration - 1 		#cla.duration
				  n.slots.insert(nint + i , nclass)
				end
			}
			end
			if( cp[ i ] )
				first = !first
			end
			
			
		end 
	#	n.calculateFitness
		return n
	end


'''
	def calculateFitness
		score  = 0
	    numberOfRooms = Room.all.size  
		daySize = DAY_HOURS * numberOfRooms
		ci = 0
		classes.each_with_index { |(k,v),index| 
 
		# coordinate of time-space slot
		  p = k
		 day = p / daySize	
		 time = p % daySize
		 room = time / DAY_HOURS
		time = time % DAY_HOURS
		 dur = v.duration #getDuration 				#cla.duration 

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
		if criteria[ ci + 1 ] 
			score = score +1
			end

		# does current room have computers if they are required
		criteria[ ci + 2 ] = !cc.lab || ( cc.lab && r.lab )     #r.lab cc.lab
		if criteria[ ci + 2 ] 
			score = score + 1
			end

		 po = false
		 go = false
		# check overlapping of classes for professors and student groups
		i = numberOfRooms
		t = day * daySize + time
		total_overlap = false
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
							total_overlap = true#throw :total_overlap
							end
					end
				end
			end
			i = i - 1
			t += DAY_HOURS 
		end

     #catch (:total_overlap) do
if total_overlap == true
		 # professors have no overlaping classes?
		 if !po 
			score = score  + 1
		   end
		
		  criteria[ ci + 3 ] = !po

		 # student groups has no overlaping classes?
		 if  !go 
			score = score  + 1
		 end
		#criteria [ci + 4 ] = !go
		 ci +=5 
	 end
	}
	 
	  fitness = score / ( Cla.all.size * DAYS_NUM )   #C etInstance.getNumberOfCourseClasses
		end
		 '''
	


	end
 

