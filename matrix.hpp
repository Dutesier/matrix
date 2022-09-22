#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <memory>

template <class T>
class Matrix{
    //using std::unique_ptr<T> = uniqueTptr;
public:
    Matrix() = default;
    Matrix(unsigned rows, unsigned columns): rows(rows), columns(columns){
        data = new T*[rows];
        for (int row = 0; row < rows; ++row) {
            data[row] = new T[columns];
        }
    }

    ~Matrix(){
        if (data) {
            for (int row = 0; row < rows; ++row) {
                delete[] data[row];
            }
            delete[] data;
        }
    }

    T* operator[](size_t i){
        return data[i];
    }

private:
    T**                     data = nullptr;
    unsigned                rows;
    unsigned                columns;
};

#endif