#include "AbstractODESolver.hpp"

//AbstractODESolver::AbstractODESolver(){}

/*AbstractODESolver::~AbstractODESolver(){
    delete _initial_value;
}*/

void AbstractODESolver::setOutputFolder(const std::string folder_path){
    CWD = folder_path;
}

void AbstractODESolver::useCompletePath(const bool flag){
    _use_complete_output_file = flag;
}

void AbstractODESolver::setStepSize(double h){
    if(h < 0 || h >=1){
        throw std::runtime_error("Invalid value for step size h. Must be between 0 and 1.");
    }
    _h = h;
}


void AbstractODESolver::setTimeInterval(double initial_t, double final_t){
    if(final_t <= initial_t){
        throw std::runtime_error("Invalid time interval.");
    }
    _final_time = final_t;
    _initial_time = initial_t;
}

void AbstractODESolver::setInitialValue(const Vector& y0){
    _initial_value = new Vector(y0);
}

double AbstractODESolver::getStepSize(){
    return _h;
}

double AbstractODESolver::getInitialTime(){
    return _initial_time;
}

double AbstractODESolver::getFinalTime(){
    return _final_time;
}

Vector& AbstractODESolver::getInitialValue(){
    return *_initial_value;
}

//void AbstractODESolver::solve(){}

void AbstractODESolver::openOutputFile(const std::string file_name){

    _output_file.setf(std::ios::scientific,std::ios::floatfield);
    _output_file.precision(7);

    std::string file_path;
    if(_use_complete_output_file){
        file_path = CWD + "/" + file_name;
    }else{
        file_path = file_name;
    }

    _output_file.open(file_path);

    if(!_output_file.is_open()){
        throw std::runtime_error("Error when opening the file to write the solution.");
    }

}

void AbstractODESolver::writeData(double t, double y){
    _output_file << std::setw(15) << t
                 << std::setw(15) << y << std::endl;
}

void AbstractODESolver::closeOutputFile(){
    _output_file.close();
}
