class Cla < ActiveRecord::Base
	belongs_to :professor
	belongs_to :course
	belongs_to :group
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
