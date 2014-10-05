class AddClaRefToProfessors < ActiveRecord::Migration
  def change
    add_reference :professors, :cla, index: true
  end
end
