class Course < ActiveRecord::Base
	belongs_to :cla
 
	def tname
		"#{name}"
	end
end

