class Course < ActiveRecord::Base
	has_one :cla
 
	def tname
		"#{name}"
	end
end

