# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/


$.ajax
	url: "/rooms"
	type: "POST"
	data:
		room:
			name: "posted"
			lab: true
			size: 100000

	success: (resp) ->
		alert "successfull" 
  		
  	 