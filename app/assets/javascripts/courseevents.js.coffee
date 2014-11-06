# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 
 

	#alert  gon.courseevents if gon
	
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
  </thead> <tr>"
	i=0
	while i < str.courseevents.length
		stringerDay = Array(str.courseevents[i].meetingday + 1).join "<td> . </td>"
		stringerTimes = Array(str.courseevents[i].meetingtime).join "<tr> <td>.</td><td>.</td><td>.</td><td>.</td><td>.</td><td>.</td></tr>"
		output = output + stringerTimes+stringerDay  + "<td><br>"+str.courseevents[i].roomname + "<br>"+str.courseevents[i].lab + "<br>"+str.courseevents[i].meetingtime + "<br>"+str.courseevents[i].meetingday + "<br>"+str.courseevents[i].courseduration + "<br>"+str.courseevents[i].coursename  + "<br>"+str.courseevents[i].profname + "<br>"+str.courseevents[i].groupname  + "</td></tr>"

		i++
	output = output + "</table>"

	
	document.getElementById("placeholder").innerHTML=output


	$("p").html(str.toSource()) 



	 