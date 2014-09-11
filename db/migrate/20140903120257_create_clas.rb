class CreateClas < ActiveRecord::Migration
  def change
    create_table :clas do |t|
      t.integer :professor_id
      t.integer :course_id
      t.integer :group_id
      t.integer :duration
      t.boolean :lab

      t.timestamps
    end
  end
end
