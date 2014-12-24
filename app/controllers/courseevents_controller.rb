class CourseeventsController < ApplicationController
  def index
  	#c = Algorithm.new
        # @c = Schedule.new.res
  	#gon.courseevents = Courseevent.order(:id)
     @courseevents = Courseevent.order(:id)
     @rooms = Room.order(:id)
     @groups = Group.order(:id)
 
      
 end

 def save_gridster
  ap params
  ap JSON.parse(params[:gridster_data])
  JSON.parse(params[:gridster_data]).each do |k,v|
    ap v
  end
  
  @courseevents = Courseevent.order(:id)
  @courseevents.each do |courseevent|
    courseevent = Courseevent.find_by_id(params[:id])
    courseevent.meetingday = params[:col]
    courseevent.meetingtime = params[:row]
    courseevent.courseduration = params[:size_y]
    courseevent.save
 end
   
 end

   
end
