class CreateCourseevents < ActiveRecord::Migration
  def change
    create_table :courseevents do |t|
      t.string :groupname
      t.string :coursename
      t.integer :meetingday
      t.integer :meetingtime
      t.integer :courseduration
      t.boolean :lab
      t.string :roomname
      t.references :cbrcase, index: true

     # t.timestamps
    end
  end
end