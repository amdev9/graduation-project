json.array!(@professors) do |professor|
  json.extract! professor, :id, :name
  json.url professor_url(professor, format: :json)
end
