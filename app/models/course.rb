class Course < ActiveRecord::Base
	has_many :cla
 
	def tname
		"#{name}"
	end
end

