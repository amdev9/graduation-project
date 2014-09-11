json.array!(@groups) do |group|
  json.extract! group, :id, :name, :size
  json.url group_url(group, format: :json)
end
