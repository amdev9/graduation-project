class Test 
	def getGroups
        groups = Group.order(:id)
		groups
	end
	def method
		rooms = Room.order(:id)
		rooms
	end
	def getBest
		c = Algorithm.new.start
		c
	end
end


