class ChildView
	def initialize
		@schedule = nil
		@running = false
		Algorithm.getInstance.getObserver.setConsole
	end
	def setSchedule(schedule)
			#run new thread here
			@schedule = schedule.makeCopy(false)
			#unlock
	end
	def setNewState(state)
		@running = state == AS_RUNNING
	end
	def printer
		#lock
		if @schedule!=nil
			puts "Fitness: #{@schedule.getFitness} Generation: #{Algorithm.getInstance.getCurrentGeneration}"
			classes = @schedule.getClasses
			
			classes.each do |(x,v)|
				puts "#{x.course_id.name} #{x.professor_id.name}"
			end

		end
		#unlock
end