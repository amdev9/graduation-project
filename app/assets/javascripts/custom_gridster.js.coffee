$(document).ready ->
  gridster = $(".gridster > ul").gridster({
      widget_margins: [30, 4],
      widget_base_dimensions: [130, 100]
      min_cols: 6
      max_cols: 6
      max_rows: 12
      helper: 'clone'
      resize: 
        enabled: true
      serialize_params:  ($w, wgd) ->
         return (
            id:  $($w).attr('id'),
            col: wgd.col,
            row: wgd.row,
            size_x: wgd.size_x,
            size_y: wgd.size_y
          )
  }).data('gridster');

  $('#save_gridster_data').click ->
    #alert gridster.serialize().toSource() 
    $.ajax
      url:"/save_gridster",
      type: "PUT",
      data: 
        gridster_data: gridster.serialize()
      dataType: 'json'

  $('#hideshow').click ->
    $('#correction-content').toggle('hide')
  $('#save_gridster_data').click ->
    $('#proverka').show('show')

