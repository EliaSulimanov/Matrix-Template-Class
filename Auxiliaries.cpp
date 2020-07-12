#include "Auxiliaries.h"

data_struct::Dimensions::Dimensions( int row_t,  int col_t) : row(row_t), col(col_t) {}

std::string data_struct::Dimensions::toString() const {
    return "(" + std::to_string(row) + "," + std::to_string(col) + ")";
}

bool data_struct::Dimensions::operator==(const Dimensions& other) const {
    return (row==other.row) and (col==other.col);
}

bool data_struct::Dimensions::operator!=(const Dimensions& other) const {
    return not(*this==other);
}

int data_struct::Dimensions::getRow() const {
    return row;
}

int data_struct::Dimensions::getCol() const {
    return col;
}

std::string data_struct::printMatrix(const int* matrix,const Dimensions& dim){
    std::string matrix_str;
    int col_length = dim.getCol();
    for (int i = 0; i <dim.getRow(); i++) {
        for (int j = 0; j < col_length ; j++) {
            matrix_str+= std::to_string(*(matrix+col_length*i+j)) + " "; 
        }
        matrix_str+=  "\n";
    }
    matrix_str+=  "\n";
    return matrix_str;
}