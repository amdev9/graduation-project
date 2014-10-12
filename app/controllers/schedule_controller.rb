class ScheduleController < ApplicationController
  def index
  	#c = Algorithm.new
  	@c = Schedule.new.res
  	
  end
end
