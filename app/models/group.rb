class Group < ActiveRecord::Base
	has_many :cla_groups
	has_many :cla, :through => :cla_groups, :dependent => :destroy
	
	def tname 
		"#{name}"
	end
end
