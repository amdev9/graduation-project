class CreateRooms < ActiveRecord::Migration
  def change
    create_table :rooms do |t|
      t.string :name
      t.boolean :lab
      t.integer :size

      t.timestamps
    end
  end
end
