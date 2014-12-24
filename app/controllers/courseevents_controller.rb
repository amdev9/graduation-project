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
  # v is
  # {
  #         "id" => "2",
  #        "col" => "4",
  #        "row" => "1",
  #     "size_x" => "1",
  #     "size_y" => "2"
  # }

  params[:gridster_data].each do |k,v|
    Courseevent.find(v['id']).update(meetingday: v['col'], meetingtime: v['row'], courseduration: v['size_y'])
  end
  render nothing: true
 end

   
end
