# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 
 

	#alert  gon.courseevents if gon
	
jQuery ->
	str = $('.courseevents_class').data('courseevents')
	alert str.toSource()
	$("p").html(str.toSource())
 

	 
	 #javascript 	 change to coffee
 var output="<ul>";
  for (var i in str) {
            output+="<li>" + str[i].firstName + " " + str[i].lastName + "--" + str[i].joined.month+"</li>";
        }

        output+="</ul>";
        document.getElementById("placeholder").innerHTML=output;
  });
  

$("#secondElementId").offset({ top: meetingtimevalue, left: meetingdayvalue})


#get
var p = $("#elementId");
var offset = p.offset();