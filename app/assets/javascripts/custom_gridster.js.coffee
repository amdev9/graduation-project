$(document).ready ->
  gridster = $(".gridster > ul").gridster({
      widget_margins: [10, 10],
      widget_base_dimensions: [140, 140]
      helper: 'clone'
      resize: 
      	enabled: true
       
  }).data('gridster');
  gridData = gridster.serialize()
  alert gridData.toSource()

 