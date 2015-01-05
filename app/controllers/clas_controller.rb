class ClasController < ApplicationController
  before_action :set_cla, only: [:show, :edit, :update, :destroy]

  # GET /clas
  # GET /clas.json
  def index
    @clas = Cla.all
  end

  # GET /clas/1
  # GET /clas/1.json
  def show
  end

  # GET /clas/new
  def new
    @cla = Cla.new
  end

  # GET /clas/1/edit
  def edit
  end

  # POST /clas
  # POST /clas.json
  def create
    @cla = Cla.new(cla_params)

    respond_to do |format|
      if @cla.save
        format.html { redirect_to @cla, notice: 'Новое занятие успешно сохранено.' }
        format.json { render :show, status: :created, location: @cla }
      else
        format.html { render :new }
        format.json { render json: @cla.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /clas/1
  # PATCH/PUT /clas/1.json
  def update
    respond_to do |format|
      if @cla.update(cla_params)
        format.html { redirect_to @cla, notice: 'Измененное занятие успешно сохранено.' }
        format.json { render :show, status: :ok, location: @cla }
      else
        format.html { render :edit }
        format.json { render json: @cla.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /clas/1
  # DELETE /clas/1.json
  def destroy
    @cla.destroy
    respond_to do |format|
      format.html { redirect_to clas_url, notice: 'Занятие успешно удалено.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_cla
      @cla = Cla.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def cla_params
      params.require(:cla).permit(:professor_id, :course_id,  :duration, :lab, :group_ids => [])
    end
end
