#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include <iostream>
#include <string>

#include <cmath>

namespace data_struct {
	typedef int units_t;
	
	class Dimensions {
        int row, col;
    public:
        Dimensions( int row_t,  int col_t);
        std::string toString() const;
        bool operator==(const Dimensions& other) const;
        bool operator!=(const Dimensions& other) const;
        int getRow() const ;
        int getCol() const ;
    };
    
    std::string printMatrix(const int* matrix,const Dimensions& dim);

    template<class ITERATOR_T>
    std::ostream& printMatrix(std::ostream& os,ITERATOR_T begin,
                                ITERATOR_T end, unsigned int width){
        unsigned int row_counter=0;
        for (ITERATOR_T it= begin; it !=end; ++it) {
            if(row_counter==width){
                row_counter=0;
                os<< std::endl;
            }
            os <<*it<<" ";
            row_counter++;
        }
        os<< std::endl;
        return os;
	}	
}

#endif
