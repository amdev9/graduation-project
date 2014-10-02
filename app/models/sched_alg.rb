

DAY_HOURS=12 #Number of working hours per day
DAYS_NUM=5     #Number of days in week

class Schedule
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

	def copy_constructor (  c, setupOnly)
		 if !setupOnly  
			@slots = c._slots
			@classes = c._classes
			@criteria = c._criteria
			@fitness = c._fitness
	 
		end
		@numberOfCrossoverPoints = c.@numberOfCrossoverPoints
		@mutationSize = c.@mutationSize
		@crossoverProbability = c.@crossoverProbability
		@mutationProbability = c.@mutationProbability
	end
   # copy constructor here NO NEED
    def makeCopy (setupOnly)	
    	Schedule.new(self, setupOnly)
    end
    def makeNewFromPrototype
    	size = @slots.size
    	newChromosome = Schedule.new(self, true)
    	c = Config.getCourseClasses			#create class Config
    	c.each do |it|
			nr = Config.getNumberOfRooms
    		dur = it.getDuration
    		day = rand(DAYS_NUM)  
		    room = rand(nr)
		    time = rand( DAY_HOURS + 1 - dur )
		    pos = day * nr * DAY_HOURS + room * DAY_HOURS + time
		 
		  	newChromosome.@slots.each_with_index do |i|
				@slots[pos + i] = it 
			end
			newChromosome.@classes[:it] = pos 
		end
   		newChromosome.calculateFitness
		return newChromosome
   	end
	 
	def crossover (  parent2)
		if  rand(100) > @crossoverProbability 
			return Schedule.new(self,false)
		end
		n = Shedule.new (self, true)
		size = @classes.size
		cp = []
		for i in @numberOfCrossoverPoints
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
			    @classes.each_with_index  {  |(cclass, int), cindex|  #index no need
				n.@classes[:cclass]= int
				for   i in 0..cclass.GetDuration() - 1 
				  n.@slots[ int + i ] << cclass
				end
			else
			    parent2.@classes.each_with_index  {  |(nclass, nint), nindex| #index no need
				n.@classes[:nclass]= nint
				for   i in 0.. nclass.GetDuration() - 1 		#getDuration
				  n.@slots[ nint + i ] << nclass
				end
			end
			if( cp[ i ] )
				first = !first
			end
			}
			}
		end 
		n.calculateFitness
		return n
	end
	
	def mutation
		if rand(100) > @mutationProbability
			return
		numberOfClasses = @classes.size
		size  = @slots.size
		for i in @mutationSize
			mpos = rand(numberOfClasses)
			pos1 = 0
			@classes.each_with_index { |(k,v),it|
				while mpos > 0
				  mpos= mpos - 1
				end
				pos1 = v
				cc1 = k
				 nr = Configuration::GetInstance().GetNumberOfRooms
					dur = cc1.GetDuration
					day = rand( DAYS_NUM)
					room = rand( nr)
					time = rand( DAY_HOURS + 1 - dur )
					pos2 = day * nr * DAY_HOURS + room * DAY_HOURS + time
 
	            for i in  0.. dur - 1 
					cl = @slots[ pos1 + i ]
					@slots.each { |it|  	
						if( it == cc1 )
							cl.delete_at( it );
							break
						end
					}
					end
					@slots[ pos2 + i ]<< cc1
				end
				@classes[ :cc1 ] = pos2
			}
		end
		calculateFitness
	end
	
	def calculateFitness
		score  = 0
	    numberOfRooms = Configuration::GetInstance().GetNumberOfRooms ####
		daySize = DAY_HOURS * numberOfRooms
		ci = 0
		@classes.each_with_index { |(k,v),index| 
 
		# coordinate of time-space slot
		  p = v 
		 day = p / daySize	
		 time = p % daySize
		 room = time / DAY_HOURS
		time = time % DAY_HOURS
		 dur = k.getDuration 		#####

		# check for room overlapping of classes			 
		ro = false
		for i in 0..dur-1
			if  @slots[ p + i ].size > 1 
				ro = true
				break
			end
		end

		#on room overlaping
		if( !ro )
			score = score + 1
		end
		@criteria[ ci + 0 ] = !ro

		 cc =  k
		 r = Configuration.getInstance.getRoomById( room )    #refferense! to roo,
		# does current room have enough seats
		@criteria[ ci + 1 ] = r.GetNumberOfSeats >= cc.GetNumberOfSeats
		if( @criteria[ ci + 1 ] )
			score = score +1
			end

		# does current room have computers if they are required
		@criteria[ ci + 2 ] = !cc.IsLabRequired || ( cc.IsLabRequired && r.IsLab )
		if( @criteria[ ci + 2 ] )
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
				cl = @slots[ t + i ]
				cl.each do |it|
					if  cc != it 
						# professor overlaps?
						if !po && cc.ProfessorOverlaps(it ) 
							po = true
						end
						# student group overlaps?
						if( !go && cc.GroupsOverlap(it) 
							go = true
						end
						# both type of overlapping? no need to check more
						if( po && go )
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
		if( !po )
			score = score  + 1
			end
		@criteria[ ci + 3 ] = !po

		# student groups has no overlaping classes?
		if( !go )
			score = score  + 1
			end
		@criteria[ ci + 4 ] = !go
	 ci +=5
	 }
	end
	 
	@fitness = score / ( Configuration.getInstance.getNumberOfCourseClasses * DAYS_NUM )
	end
end

end


Algorithm.instance = null

class Algorithm
	@chromosomes
	@bestFlags
	@bestChromosomes
	@currentBestSize
	@replaceByGeneration
	@observer
	@prototype
	@currentGeneration
	@state
	@instance
	@instanceSect
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
		if @replaceByGeneration < 1 
			@replaceByGeneration = 1
			end
		else if @replaceByGeneration > (numberOfChromosomes - trackBest)
			@replaceByGeneration = numberOfChromosomes - trackBest;
		end
	for i in 0..@chromosomes.size - 1 
		@chromosomes[ i ] = null
		@bestFlags[ i ] = false
	end
		
	end
	
   def getInstance
	if  @instance == NULL 
		prototype = Schedule.new( 2, 2, 80, 3)
		@instance = new Algorithm( 100, 8, 5, prototype, new ScheduleObserver() ); ##
	 end
	return @instance
   end
	def freeInstance
		@instance = null
	end
	def start
		if !prototype
			return
	    end
		if( @state == AS_RUNNING )
			return
			end
			@state = AS_RUNNING	
		
	clearBest
	i = 0
	@chromosomes.each do |it|
		it = @prototype.makeNewFromPrototype
		addToBest(i)
		i = i + 1
	end
	@currentGeneration = 0 
	while( true )
		best=getBestChromosomes
		if best.getFitness >= 1
		@state = AS_CRITERIA_STOPPED
		break
		end
		
		 
		for  j in 0.. @replaceByGeneration 		 
			 p1 = @chromosomes[ rand(@chromosomes.size)]	
			p2 = @chromosomes[ rand( @chromosomes.size) ]

			offspring[ j ] = p1.crossover( p2 )	  
			offspring[ j ].mutation						 
		end
	for  j in 0..@replaceByGeneration  
			loop do
				#select chromosome for replacement randomly
				ci = rand(@chromosomes.size)		
			 break if( IsInBest( ci ) )	
			end			 
  
			@chromosomes[ ci ] = offspring[ j ]			 
			addToBest( ci )          #######realization
		end

		 
		    if  best != getBestChromosome() && @observer 
			@observer.NewBestChromosome( getBestChromosome)
		    end
		@currentGeneration = @currentGeneration + 1
	end
	
	    if( @observer )
		 
		@observer.EvolutionStateChanged( @state )
	    end
	
end
	def stop
		if  @state == AS_RUNNING  
			@state = AS_USER_STOPED
	end
	def getBestChromosome
		@chromosomes[ @bestChromosomes[ 0 ] ]
	end
	def addToBest (chromosomeIndex)
		if ( @currentBestSize == @bestChromosomes.size && 
		@chromosomes[ @bestChromosomes[ @currentBestSize - 1 ] ].getFitness >= 
		@chromosomes[ chromosomeIndex ].getFitness ) || @bestFlags[ chromosomeIndex ] 
			return
		end
		
		i = @currentBestSize
    while i > 0
		if  i < @bestChromosomes.size
			if @chromosomes[ @bestChromosomes[ i - 1 ] ].getFitness > 
				@chromosomes[ chromosomeIndex ].GetFitness 
				break
			end
			@bestChromosomes[ i ] = _bestChromosomes[ i - 1 ]
		
		else
			@bestFlags[ @bestChromosomes[ i - 1 ] ] = false
		end
		@bestChromosomes[ i ] = chromosomeIndex
		@bestFlags[ chromosomeIndex ] = true

	if @currentBestSize < @bestChromosomes.size 
		@currentBestSize= @currentBestSize + 1
	end
	i = i-1
	end
	end
	
	def isInBest( chromosomeIndex)
		return @bestFlags[ chromosomeIndex ]
	end
	
	def clearBest()
	for i in 0.. @bestFlags.size() - 1 
		@bestFlags[ i ] = false
	end
	@currentBestSize = 0
	end

end