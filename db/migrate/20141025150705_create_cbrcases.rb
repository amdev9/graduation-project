class CreateCbrcases < ActiveRecord::Migration
  def change
    create_table :cbrcases do |t|
      t.integer :numofcla
      t.integer :numofprof
      t.integer :numofgroups
      t.integer :numofrooms

      t.timestamps
    end
  end
end
