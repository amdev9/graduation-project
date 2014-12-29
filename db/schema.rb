# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20141229000914) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"
  enable_extension "hstore"

  create_table "cbrcases", force: true do |t|
    t.integer "numofcla"
    t.integer "numofprof"
    t.integer "numofgroups"
    t.integer "numofrooms"
  end

  create_table "cla_groups", force: true do |t|
    t.integer  "cla_id"
    t.integer  "group_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "clas", force: true do |t|
    t.integer  "professor_id"
    t.integer  "course_id"
    t.integer  "group_id"
    t.integer  "duration"
    t.boolean  "lab"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "courseevents", force: true do |t|
    t.string  "roomname"
    t.boolean "lab"
    t.integer "meetingtime"
    t.integer "meetingday"
    t.integer "courseduration"
    t.string  "coursename"
    t.string  "profname"
    t.string  "groupname"
    t.integer "cbrcase_id"
  end

  add_index "courseevents", ["cbrcase_id"], name: "index_courseevents_on_cbrcase_id", using: :btree

  create_table "courses", force: true do |t|
    t.string   "name"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "cla_id"
  end

  add_index "courses", ["cla_id"], name: "index_courses_on_cla_id", using: :btree

  create_table "groups", force: true do |t|
    t.string   "name"
    t.integer  "size"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "professors", force: true do |t|
    t.string   "name"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "cla_id"
  end

  add_index "professors", ["cla_id"], name: "index_professors_on_cla_id", using: :btree

  create_table "rooms", force: true do |t|
    t.string   "name"
    t.boolean  "lab"
    t.integer  "size"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "users", force: true do |t|
    t.string   "email",                  default: "", null: false
    t.string   "encrypted_password",     default: "", null: false
    t.string   "reset_password_token"
    t.datetime "reset_password_sent_at"
    t.datetime "remember_created_at"
    t.integer  "sign_in_count",          default: 0,  null: false
    t.datetime "current_sign_in_at"
    t.datetime "last_sign_in_at"
    t.inet     "current_sign_in_ip"
    t.inet     "last_sign_in_ip"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "users", ["email"], name: "index_users_on_email", unique: true, using: :btree
  add_index "users", ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true, using: :btree

end
