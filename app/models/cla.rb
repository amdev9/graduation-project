class Cla < ActiveRecord::Base
	validates :duration, inclusion: {in: 1..12}
	validates_presence_of :groups
	belongs_to :professor    	
	belongs_to :course
	has_many :cla_groups
	has_many :groups , :through => :cla_groups, :dependent => :destroy

	def professor_name
		professor.tname if professor
	end
   def course_name
		course.tname if course
	end
	 
	
end
