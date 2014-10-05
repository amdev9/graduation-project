class Professor < ActiveRecord::Base
	belongs_to :cla
	def tname
		"#{name}"
	end
end
