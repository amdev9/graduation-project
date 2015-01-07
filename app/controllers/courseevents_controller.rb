class CourseeventsController < ApplicationController
  def index
    
     if  params[:d] == "true"
          @c = Schedule.new.res
         @courseevents = Courseevent.order(:id)
      
     @rooms = Room.order(:id)
     @groups = Group.order(:id)
 
    #end
     else
  	#c = Algorithm.new
        # @c = Schedule.new.res
  	#gon.courseevents = Courseevent.order(:id)

    #search id in cbracases where params
    #for id search in courseevetn
 #if != nil ... else .. generate 
    @clasize = Cla.all.size
    @profsize =Professor.all.size
    @groupsize = Group.all.size
    @roomsize = Room.all.size
    # @cbrcase = Cbrcase.select("id").find_or_initialize_by(numofcla: @clasize,  numofprof: @profsize, numofgroups: @groupsize, numofrooms: @roomsize)  #where ( "numofcla = 2
    #      p @cbrcase.id
    # unless @cbrcase.id.nil?
      
    #      @courseevents = Courseevent.order(:id).where (["cbrcase_id = :cbrid" ,{ cbrid: @cbrcase.id.to_s}])
    # else
    #     #run program genetic algo
         # @c = Schedule.new.res
         @courseevents = Courseevent.order(:id)
    #end
     @rooms = Room.order(:id)
     @groups = Group.order(:id)
 
      end
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
  #run program test
  params[:gridster_data].each do |k,v|
    if v['id'] != "freeslots"
    Courseevent.find(v['id']).update(meetingday: v['col'], meetingtime: v['row'], courseduration: v['size_y'])
    end
  end
  @c = Schedule.new.test
  p @c
  
  render nothing: true
  if @c != "1"
    flash[:alert] = "Расписание не сохранено"


  else
   flash[:notice] = "Расписание успешно сохранено" 
   
  end

 end

   def generate
     @c = Schedule.new.res
    @courseevents = Courseevent.order(:id)

    end

end
