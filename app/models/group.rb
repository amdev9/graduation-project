class Group < ActiveRecord::Base
	has_many :clas, :dependent => :destroy

	def tname 
		"#{name}"
	end
end
