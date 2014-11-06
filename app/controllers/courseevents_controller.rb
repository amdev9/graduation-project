class CourseeventsController < ApplicationController
  def index
  	#c = Algorithm.new
  	#@c = Schedule.new.res
  	#gon.courseevents = Courseevent.order(:id)
     @courseevents = Courseevent.order(:id)
  end

   
end
