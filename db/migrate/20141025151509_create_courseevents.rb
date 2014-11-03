class CreateCourseevents < ActiveRecord::Migration
  def change
    create_table :courseevents do |t|
      t.string :roomname
      t.boolean :lab
      t.integer :meetingtime
      t.integer :meetingday
      t.integer :courseduration
      t.string :coursename
      t.string :profname
      t.string :groupname
      
      t.references :cbrcase, index: true

     # t.timestamps
    end
  end
end
