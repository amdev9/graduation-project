class Cla < ActiveRecord::Base
	belongs_to :professor   #fk - proffessor_id	
	belongs_to :course 		#fk - course_id
	belongs_to :group  		#fk - group_id

	def professor_name
		professor.tname if professor
	end
   def course_name
		course.tname if course
	end
	def group_name
		group.tname if group
	end
	

end
