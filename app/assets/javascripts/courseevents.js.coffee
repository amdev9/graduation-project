# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 
 

	#alert  gon.courseevents if gon
	
jQuery ->
	str = $('.courseevents_class').data('courseevents')
	alert str.toSource()
	$("p").html(str.toSource())
 

	 
	 