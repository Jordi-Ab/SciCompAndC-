#include "AbstractODESolver.hpp"

void AbstractODESolver::setOutputFolderPath(const std::string folder_path){
    _output_folder_path = folder_path;
    _use_complete_output_file = true;
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


double AbstractODESolver::getStepSize(){
    return _h;
}

double AbstractODESolver::getInitialTime(){
    return _initial_time;
}

double AbstractODESolver::getFinalTime(){
    return _final_time;
}

void AbstractODESolver::openOutputFile(const std::string file_name){

    _output_file.setf(std::ios::scientific,std::ios::floatfield);
    _output_file.precision(7);

    std::string file_path = file_name;
    if(_use_complete_output_file){
        file_path = _output_folder_path + "/" + file_path;
    }
    std::cout << "" << std::endl;
    std::cout << "Saving file on folder: ";
    std::cout << file_path << std::endl;
    std::cout << "" << std::endl;

    _output_file.open(file_path);

    if(!_output_file.is_open()){
        throw std::runtime_error("Error when opening the file to write the solution.");
    }
}

void AbstractODESolver::printHeader(const std::string class_name){
    std::cout << "" << std::endl;
    std::cout << "Approximating solution using "+class_name+" Method." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  Initial Time: " << getInitialTime() << std::endl;
    std::cout << "  Final Time: " << getFinalTime() << std::endl;
    std::cout << "  Step Size: " << getStepSize() << std::endl;
    std::cout << "  Number of Steps: " << getFinalTime()/getStepSize() << std::endl;
}

void AbstractODESolver::writeData(const double t, const Vector& us){
    _output_file << std::setw(15) << t;
       for (int i=0; i<us.GetSize(); i++){
           _output_file << std::setw(15) << us.Read(i);
       }
    _output_file << "\n"; // End of Line.
}

void AbstractODESolver::writeData(const double h, double e){
    _output_file << std::setw(15) << h;
    _output_file << std::setw(15) << e << std::endl;
}

void AbstractODESolver::printData(const double t, const Vector& us){
    if (us.GetSize() > 3){
        std::cout << "# Note: Printing only the first 3 ";
        std::cout << "components of the solution vector." << std::endl;
    }
    std::cout << "For time= " << t;
    int components_to_print = std::min(3, us.GetSize());
    for(int i=0; i<components_to_print; i++){
        std::cout << ", u[" << i << "]= " << us.Read(i);
    }
    std::cout << "\n"; // End of Line.
}

void AbstractODESolver::closeOutputFile(){
    _output_file.close();
}





