class Professor < ActiveRecord::Base
	has_many :clas
	def tname
		"#{name}"
	end
end
