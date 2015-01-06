# Place all the behaviors and hooks related to the matching controller here.
# All this logic will automatically be available in application.js.
# You can use CoffeeScript in this file: http://coffeescript.org/  
  
jQuery ->
  str = $('.courseevents_class').data()
  gr = $('.rooms_class').data() 
  g = $('.groups_class').data()
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
      
      courseGroups = []
      it = 0
      while it < str.courseevents.length
        if "#{str.courseevents[it].roomname}" == "#{gr.rooms[r].id}"          
          asd = 0
          courseGroups[it] = []
          while asd < str.courseevents[it].groupname.split('/').length-1  
            das = 0
            while das < g.groups.length
              if "#{g.groups[das].id}" == "#{str.courseevents[it].groupname.split('/')[asd]}"
                courseGroups[it].push(g.groups[das].name)
              das++
            asd++  
        it++


      while i < str.courseevents.length
        tmp = str.courseevents[i].meetingday + 6* (str.courseevents[i].meetingtime - 1) - 1

        if "#{str.courseevents[i].roomname}" == "#{gr.rooms[r].id}"
          val.splice tmp, 1,"<td class='success'>#" +str.courseevents[i].meetingtime + "#<br>Продолжительность: "+str.courseevents[i].courseduration + "<br><b>"+str.courseevents[i].coursename  + "</b><br><b>"+str.courseevents[i].profname + "</b><br>Группы:<br>"+  courseGroups[i].join("/") + "</td>"
          
        i++
      
      j=0

      while j < 6*12
        if j%6 == 0
          output = output + "<tr>" + val.slice(j, j + 6).join ""
          output = output + "</tr>" 
     
        j+=6 
    
      output = output + "</table>"
      output = output.replace(/true/g,"Лабораторная")
      output = output.replace(/false/g,"Не лабораторная")
      output = output.replace(/#1#<br>/g,"8:30-9:00 <br>")
      output = output.replace(/#2#<br>/g,"9:00-10:30 <br>")
      output = output.replace(/#3#<br>/g,"10:45-11:40 <br>")
      output = output.replace(/#4#<br>/g,"11:50-12:15 <br>")
      output = output.replace(/#5#<br>/g,"13:00-14:30 <br>")
      output = output.replace(/#6#<br>/g,"14:45-15:00 <br>")
      output = output.replace(/#7#<br>/g,"15:10-16:15 <br>")
      output = output.replace(/#8#<br>/g,"16:15-18:20 <br>")

      output = output.replace(/#9#<br>/g,"18:30-19:30 <br>")
      output = output.replace(/#10#<br>/g,"19:30-20:30 <br>")
      output = output.replace(/#11#<br>/g,"21:30-22:30 <br>")
      output = output.replace(/#12#<br>/g,"22:30-23:30 <br>")

      #$("p").html(str.toSource()) 
      r++
    document.getElementById("placeholder").innerHTML=output
    


  



