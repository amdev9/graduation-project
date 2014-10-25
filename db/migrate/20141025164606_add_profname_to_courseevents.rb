class AddProfnameToCourseevents < ActiveRecord::Migration
  def change
    add_column :courseevents, :profname, :string
  end
end
