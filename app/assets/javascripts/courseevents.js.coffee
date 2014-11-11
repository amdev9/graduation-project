# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 
 #http://davidwalsh.name/demo/responsive-scalable-animations.php
#alert  gon.courseevents if gon

#var fruits = [".", ".", ".", "."];  1) initial full table values:   6*12  val = []; val.splice 0,6*12, Array(6*12).join "<td>.</td>"
#fruits.splice(0, 1, "Lemon");		2) then splice AT POSITION: 
#val.splice str.courseevents[i].meetingday * str.courseevents[i].meetingtime, 1,"<td><br>"+str.courseevents[i].roomname + "<br>"+str.courseevents[i].lab + "<br>"+str.courseevents[i].meetingtime + "<br>"+str.courseevents[i].meetingday + "<br>"+str.courseevents[i].courseduration + "<br>"+str.courseevents[i].coursename  + "<br>"+str.courseevents[i].profname + "<br>"+str.courseevents[i].groupname  + "</td>"

	
jQuery ->
	str = $('.courseevents_class').data()
	output = "<table><thead>
    <tr>
    <th>Hours</th>
      <th>MON</th>
       <th>WEN</th>
        <th>THU</th>
       <th>FRY</th>
      <th>SAT</th>
      <th colspan=\"3\"></th>
    </tr>
  </thead> <tr>" #delete tr
	i=0
	#val = []; val.splice 0,6*12, Array(6*12).join "<td>.</td>"
	val = []
	val.splice 0, 6 * 12, Array(6 * 12).join "<td>.</td>"
	while i < str.courseevents.length
		tmp = str.courseevents[i].meetingday * str.courseevents[i].meetingtime
		####if tmp == str.courseevents[i+1].meetingday * str.courseevents[i+1].meetingtime
		####	val2 = val
		
		val.splice tmp, 1,"<td><br>"+str.courseevents[i].roomname + "<br>"+str.courseevents[i].lab + "<br>"+str.courseevents[i].meetingtime + "<br>"+str.courseevents[i].meetingday + "<br>"+str.courseevents[i].courseduration + "<br>"+str.courseevents[i].coursename  + "<br>"+str.courseevents[i].profname + "<br>"+str.courseevents[i].groupname  + "</td>"
		stringerDay = Array(str.courseevents[i].meetingday + 1).join "<td> . </td>"
		stringerTimes = Array(str.courseevents[i].meetingtime).join "<tr> <td>.</td><td>.</td><td>.</td><td>.</td><td>.</td><td>.</td></tr>"
		output = output + stringerTimes+stringerDay  + "<td><br>"+str.courseevents[i].roomname + "<br>"+str.courseevents[i].lab + "<br>"+str.courseevents[i].meetingtime + "<br>"+str.courseevents[i].meetingday + "<br>"+str.courseevents[i].courseduration + "<br>"+str.courseevents[i].coursename  + "<br>"+str.courseevents[i].profname + "<br>"+str.courseevents[i].groupname  + "</td></tr>"

		i++
	#j=0
	#while j < 6*12
		#output = output + "<tr>" + val.slice (j, j+6).join("") + "</tr>" 
		####output = output +  "<tr>" + val2.slice (j, j+6).join("") + "</tr>" 
		#j+=6 
	
	output = output + "</table>"

	
	document.getElementById("placeholder").innerHTML=output


	$("p").html(str.toSource()) 
	
	



	 