#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <memory>
# include <iostream>
# include <iomanip>
# include <vector>

template <class T> class Matrix;
template <class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat);

template <class T>
class Matrix{
public:
    // Constructors
    Matrix() = default;
    Matrix(unsigned rows, unsigned columns): rows(rows), columns(columns){
        if (rows != 0 && columns != 0) {
            createData(rows, columns);
        }
    }

    Matrix(const Matrix& other): rows(other.rows), columns(other.columns) {
        if (other.data && &other != this) {
            createAndCopyData(other);
        } else {
            rows = 0;
            columns = 0;
            data = nullptr;
        }
    }

    Matrix(std::vector<std::vector<T>> rawData){ // Requires []operator and .length()
        if (checkIntegrity(rawData)){
            rows = rawData.size();
            columns = rawData[0].size();
            createData(rows, columns);
            for (int row = 0; row < rows; ++row) {
                for (int column = 0; column < columns; ++column) {
                    data[row][column] = rawData[row][column];
                }
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this->rows) { // Matrix data existed before
            if (this->rows == other.rows && this->columns == other.columns) { // Matrixes are the same size
                copyData(other);
            } else {
                deleteData();
                createAndCopyData(other);
                this->rows = other.rows;
                this->columns = other.columns;
            }
        } else {
            this->rows = other.rows;
            this->columns = other.columns;
            createAndCopyData(other);
        }
        return (*this);
    }

    // Move semantics
    Matrix(Matrix&& other) = delete;
    Matrix& operator=(Matrix&& other) = delete;

    // Destructors
    ~Matrix(){
        if (data) {
            deleteData();
        }
    }

    // Overloads
    T* operator[](size_t i){
        return data[i];
    }

    Matrix operator+(const Matrix& rhs){
        Matrix mat;

        if (this->rows == rhs.rows && this->columns == rhs.columns) {
            mat.createData(this->rows, this->columns);
            for (int row = 0; row < this->rows; ++row) {
                for (int column = 0; column < this->columns; ++column) {
                    mat.data[row][column] = this->data[row][column] + rhs.data[row][column];
                }
            }
            mat.rows = this->rows;
            mat.columns = this->columns;
        }
        return mat;
    }

     Matrix operator-(const Matrix& rhs){
        Matrix mat;

        if (this->rows == rhs.rows && this->columns == rhs.columns) {
            mat.createData(this->rows, this->columns);
            for (int row = 0; row < this->rows; ++row) {
                for (int column = 0; column < this->columns; ++column) {
                    mat.data[row][column] = this->data[row][column] - rhs.data[row][column];
                }
            }
            mat.rows = this->rows;
            mat.columns = this->columns;
        }
        return mat;
    }

    Matrix operator*(const Matrix& rhs){
        Matrix mat;

        if (this->columns == rhs.rows) {
            mat.rows = this->rows;
            mat.columns = rhs.columns;
            mat.createData(mat.rows, mat.columns);
            thisColumnsRhsRows(mat, rhs);
        }
        return mat;
    }

    Matrix operator*(int scalar){
        Matrix mat(rows, columns);

        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                mat.data[row][column] = this->data[row][column] * scalar;
            }
        }
        return mat;
    }

    // Friends
    friend std::ostream& operator<< <T>(std::ostream& os, const Matrix<T>& mat);

private:
    T**                                         data = nullptr;
    // std::unique_ptr<std::unique_ptr<T>>      data = nullptr;
    unsigned                                    rows = 0;
    unsigned                                    columns = 0;

    void    createData(unsigned r, unsigned c){
        data = new T*[r];
        for (int row = 0; row < r; ++row) {
            data[row] = new T[c];
            for (int column = 0; column < c; ++column) {
                data[row][column] = 0;
            }
        }

        // data = std::make_unique<std::unique_ptr<T>>(r);
        // for (int row = 0; row < r; ++row) {
        //     data[row] = std::make_unique<T>(c);
        //     for (int column = 0; column < c; ++column) {
        //         data[row][column] = 0;
        //     }
        // }
    }

    void    createAndCopyData(const Matrix& other){
        // data = std::make_unique<std::unique_ptr<T>>(other.rows);
        data = new T*[other.rows];
        for (int row = 0; row < other.rows; ++row) {
            // data[row] = std::make_unique<T>(other.columns);
            data[row] = new T[other.columns];
            for (int column = 0; column < other.columns; ++column) {
                data[row][column] = other.data[row][column];
            }
        }
    }

    void    copyData(const Matrix& other){
        for (int row = 0; row < other.rows; ++row) {
            for (int column = 0; column < other.columns; ++column) {
                data[row][column] = other.data[row][column];
            }
        }
    }

    void    deleteData(){
        for (int row = 0; row < rows; ++row) {
            delete[] data[row];
        }
        delete[] data;
    }

    T      rowSum(unsigned rowNumber){
        T sum;

        if (rowNumber < 0 || rowNumber >= rows)
            return sum;
        for (int column = 0; column < columns; ++column) {
            sum += data[rowNumber][column];
        }
        return sum;
    }
    
    T      columnSum(unsigned columnNumber){
        T sum;

        if (columnNumber < 0 || columnNumber >= columns)
            return sum;
        for (int row = 0; row < rows; ++row) {
            sum += data[row][columnNumber];
        }
        return sum;
    }

    void    thisColumnsRhsRows(Matrix& mat, const Matrix& rhs) {
        for (int row = 0; row < mat.rows; ++row) { // For every row in the final matrix
            for (int column = 0; column < mat.columns; ++column) { // For every column in the final matrix
                for (int column_in_this = 0; column_in_this < this->columns; ++column_in_this) {
                    mat.data[row][column] += this->data[row][column_in_this] * rhs.data[column_in_this][column];
                }
            }
        }
    }

    bool    checkIntegrity(std::vector<std::vector<T>> rawData){
        unsigned row_len = 0;
        unsigned col_len = 0;

        if (rawData.size() > 0) {
            for (int i = 0; i < rawData.size(); ++i) {
                if (i == 0)
                    col_len = rawData[i].size();
                else {
                    if (col_len != rawData[i].size())
                        return false;
                }
            }
            return true;
        }
        return false;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat){
    os << "Matrix of [" << mat.rows << "][" << mat.columns << "]\n";
    for (int row = 0; row < mat.rows; ++row) {
        row == 0 || row == mat.rows - 1 ? os << "[ " : os << "| ";
        for (int column = 0; column < mat.columns; ++column) {
            os << std::setw(13) << mat.data[row][column] << " ";
        }
        row == mat.rows - 1 || row == 0 ? os << "]\n" : os << "|\n";
    }
    return os;
}


// class MatrixBuilder {
// public:
//     Matrix& BuildMatrix(unsigned rows, unsigned columns){
        

//     }
// private:

// };

#endif