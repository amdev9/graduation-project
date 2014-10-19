class Cla < ActiveRecord::Base
	has_one :professor    	
	has_one :course
	has_many :cla_groups
	has_many :groups , :through => :cla_groups, :dependency => :destroy

	def professor_name
		professor.tname if professor
	end
   def course_name
		course.tname if course
	end
	 
	
end
