# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 

#alert  gon.courseevents if gon

	
jQuery ->
	str = $('.courseevents_class').data()
	output = "<table><thead>
    <tr>
    
      <th>MON </th>
       <th>TUE</th>
        <th>WED</th>
       <th>THU</th>
      <th>FRI</th>
       <th>SAT</th>
      <th colspan=\"3\"></th>
 
    </tr>
  </thead>" 
	i=0
	result = []
	k = 0
	val = []
	while k < 6*12
  		val.push "<td></td>"
  		k++
   
	while i < str.courseevents.length
		tmp = str.courseevents[i].meetingday + 6* (str.courseevents[i].meetingtime - 1) - 1
		
		val.splice tmp, 1,"<td><br>"+str.courseevents[i].roomname + "<br>"+str.courseevents[i].lab + "<br>"+str.courseevents[i].meetingtime + "<br>"+str.courseevents[i].meetingday + "<br>"+str.courseevents[i].courseduration + "<br>"+str.courseevents[i].coursename  + "<br>"+str.courseevents[i].profname + "<br>"+str.courseevents[i].groupname  + "</td>"
		 

		i++
	j=0

	while j < 6*12
		if j%6 == 0
			output = output + "<tr>" + val.slice(j, j + 6).join ""
			output = output + "</tr>" 
	 
		j+=6 
	#alert output
	output = output + "</table>"
	
	
	document.getElementById("placeholder").innerHTML=output


	#$("p").html(str.toSource()) 




	



	 