#ifndef MATRIKS_HPP
#define MATIRIKS_HPP

#include <iostream>
#include <vector>

template<class T>
class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<T>> matriks;
    T defaultVal = T();

public:
    Matrix(int r, int c) : rows(r), cols(c), matriks(r, std::vector<T>(c, T())) {}
    ~Matrix() {}

    void setDefault(int i, int j){
        matriks[i][j] = defaultVal;
    }

    void set(int i, int j, T value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            matriks[i][j] = value;
        }
    }

    T get(int i, int j) const {
        return matriks[i][j];
    }

    std:: pair<int,int> isInMatrix(T value){
        for (int i =0; i< rows; i++){
            for(int j = 0; j<cols; j++){
                if (matriks[i][j] == value){
                    return std::pair(i,j);
                }
            }
        }
        return std::pair(-1,-1);
    }

    int getRows(){
        return rows;
    }

    int getCols(){
        return cols;
    }

};

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}



#endif