# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/


#$.ajax
#	url: "/rooms"
#	type: "POST"
#	data:
#		room:
#			name: "posted"
#			lab: true
#			size: 100000
#
#	success: (resp) ->
#		alert "successfull" 
  		
 $(document).ready ->
  $(".gridster ul").gridster({
      widget_margins: [10, 10]
      widget_base_dimensions: [140, 140]
      serialize_params: ($w, wgd) ->
      	id: $($w).attr("id")
      	col: wgd.col
      	row: wgd.row
      	size_x: wgd.size_x
      	size_y: wgd.size_y
      resize: {
      	enabled: true
      }
  });
  gridster = $(".gridster ul").gridster().data('gridster')
  gridData = gridster.serialize()
 
  alert gridData.toSource()
   
 