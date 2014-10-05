class CreateClaGroups < ActiveRecord::Migration
  def change
    create_table :cla_groups do |t|
      t.integer :cla_id
      t.integer :group_id

      t.timestamps
    end
  end
end
