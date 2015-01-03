# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  #alert courseevents
 

#alert  gon.courseevents if gon

  
jQuery ->
  str = $('.courseevents_class').data()
  gr = $('.rooms_class').data() 
  #alert  gr.rooms[0].id
  #alert  str.courseevents[0].roomname
  r= 0
  output = ""
  if typeof gr != 'undefined' 
    while r < gr.rooms.length 
      output = output + "<h4><b>" + "Аудитория "  + gr.rooms[r].name + "</b><br>" + "Вместимость: " +gr.rooms[r].size + "</b><br>" +  gr.rooms[r].lab  + "</h4><table style = 'table-layout: fixed; width: 100 %' class = 'table table-hover table-bordered'><thead>
        <tr>
       
        <th>Понедельник</th>
         <th>Вторник</th>
          <th>Среда</th>
         <th>Четверг</th>
        <th>Пятница</th>
         <th>Суббота</th>
          
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

        #alert "#{str.courseevents[i].roomname}" + " " + "#{gr.rooms[r].id}"
        if "#{str.courseevents[i].roomname}" == "#{gr.rooms[r].id}"
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
      output = output.replace(/true/g,"Лабораторная")
      output = output.replace(/false/g,"Не лабораторная")
    
      


      #$("p").html(str.toSource()) 
      r++
    document.getElementById("placeholder").innerHTML=output


  



