class AddClaRefToCourses < ActiveRecord::Migration
  def change
    add_reference :courses, :cla, index: true
  end
end
