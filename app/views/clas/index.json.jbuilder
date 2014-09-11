json.array!(@clas) do |cla|
  json.extract! cla, :id, :professor_id, :course_id, :group_id, :duration, :lab
  json.url cla_url(cla, format: :json)
end
