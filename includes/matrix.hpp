#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <memory>
# include <iostream>
# include <iomanip>
# include <vector>

template <class T, unsigned R, unsigned C> class Matrix;
template <class T, unsigned R, unsigned C> std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& mat);

template <class T, unsigned R, unsigned C>
class Matrix{
public:
    // Constructors
    Matrix(): rows(R), columns(C){
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

    // Matrix(std::vector<std::vector<T>> rawData){ // Requires []operator and .length()
    //     if (checkIntegrity(rawData)){
    //         rows = rawData.size();
    //         columns = rawData[0].size();
    //         createData(rows, columns);
    //         for (unsigned row = 0; row < rows; ++row) {
    //             for (unsigned column = 0; column < columns; ++column) {
    //                 data[row][column] = rawData[row][column];
    //             }
    //         }
    //     }
    // }

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
            for (unsigned row = 0; row < this->rows; ++row) {
                for (unsigned column = 0; column < this->columns; ++column) {
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
            for (unsigned row = 0; row < this->rows; ++row) {
                for (unsigned column = 0; column < this->columns; ++column) {
                    mat.data[row][column] = this->data[row][column] - rhs.data[row][column];
                }
            }
            mat.rows = this->rows;
            mat.columns = this->columns;
        }
        return mat;
    }


    Matrix operator*(int scalar){
        Matrix mat;

        for (unsigned row = 0; row < rows; ++row) {
            for (unsigned column = 0; column < columns; ++column) {
                mat.data[row][column] = this->data[row][column] * scalar;
            }
        }
        return mat;
    }

    // Getters
    T** getData() const {
        return data;
    }

    T   getDataAt(unsigned r, unsigned c) const {
        if (r >= R || c >= C)
            return static_cast<T>(0);
        return data[r][c];
    }

    // Setters
    void setDataAt(T d, unsigned r, unsigned c){
        if (r >= R || c >= C)
            return;
        this->data[r][c] = d;
    }


    // Friends
    friend std::ostream& operator<< <T, R, C>(std::ostream& os, const Matrix<T, R, C>& mat);

private:
    T**                                         data = nullptr;
    // std::unique_ptr<std::unique_ptr<T>>      data = nullptr;
    unsigned                                    rows = 0;
    unsigned                                    columns = 0;

    void    createData(unsigned r, unsigned c){
        data = new T*[r];
        for (unsigned row = 0; row < r; ++row) {
            data[row] = new T[c];
            for (unsigned column = 0; column < c; ++column) {
                data[row][column] = 0;
            }
        }

        // data = std::make_unique<std::unique_ptr<T>>(r);
        // for (unsigned row = 0; row < r; ++row) {
        //     data[row] = std::make_unique<T>(c);
        //     for (unsigned column = 0; column < c; ++column) {
        //         data[row][column] = 0;
        //     }
        // }
    }

    void    createAndCopyData(const Matrix& other){
        // data = std::make_unique<std::unique_ptr<T>>(other.rows);
        data = new T*[other.rows];
        for (unsigned row = 0; row < other.rows; ++row) {
            // data[row] = std::make_unique<T>(other.columns);
            data[row] = new T[other.columns];
            for (unsigned column = 0; column < other.columns; ++column) {
                data[row][column] = other.data[row][column];
            }
        }
    }

    void    copyData(const Matrix& other){
        for (unsigned row = 0; row < other.rows; ++row) {
            for (unsigned column = 0; column < other.columns; ++column) {
                data[row][column] = other.data[row][column];
            }
        }
    }

    void    deleteData(){
        for (unsigned row = 0; row < rows; ++row) {
            delete[] data[row];
        }
        delete[] data;
    }

    T      rowSum(unsigned rowNumber){
        T sum;

        if (rowNumber < 0 || rowNumber >= rows)
            return sum;
        for (unsigned column = 0; column < columns; ++column) {
            sum += data[rowNumber][column];
        }
        return sum;
    }
    
    T      columnSum(unsigned columnNumber){
        T sum;

        if (columnNumber < 0 || columnNumber >= columns)
            return sum;
        for (unsigned row = 0; row < rows; ++row) {
            sum += data[row][columnNumber];
        }
        return sum;
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

template <class T, unsigned R, unsigned C>
std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& mat){
    os << "Matrix of [" << R << "][" << C << "]\n";
    for (unsigned row = 0; row < R; ++row) {
        row == 0 || row == R - 1 ? os << "[ " : os << "| ";
        for (unsigned column = 0; column < C; ++column) {
            os << std::setw(13) << mat.data[row][column] << " ";
        }
        row == R - 1 || row == 0 ? os << "]\n" : os << "|\n";
    }
    return os;
}


// !WARNING! This gets complicated here...
// Ideally we want to only multiply two matrixes M1 and M2 if:
//      M1 is of size Y Rows by X Columns AND
//      M2 is of size X Rows by Z Columns (where Z and Y might or might not be the same)
// This will create a Matrix M3 of size Y Rows by Z Columns.
// Putting it in terms of the function bellow:
// LHS is M1, RHS is M2 and MAT is M3
// SHARED is X, LHSROWS is Y and RHSCOLS is Z
// Fun stuff :)
template <class T, unsigned SHARED, unsigned LHSROWS, unsigned RHSCOLS>
Matrix<T, LHSROWS, RHSCOLS> operator*(const Matrix<T, LHSROWS, SHARED>&lhs, const Matrix<T, SHARED, RHSCOLS>& rhs){
    Matrix<T, LHSROWS, RHSCOLS> mat;
    T** lhsData = lhs.getData();
    T** rhsData = rhs.getData();
    T** matData = mat.getData();

    for (unsigned row = 0; row < LHSROWS; ++row) { // For every row in the final matrix
        for (unsigned column = 0; column < RHSCOLS; ++column) { // For every column in the final matrix
            for (unsigned column_in_this = 0; column_in_this < SHARED; ++column_in_this) {
                matData[row][column] += lhsData[row][column_in_this] * rhsData[column_in_this][column];
            }
        }
    }
    return mat;
}

std::string MatrixProductSize(int m1rows, int m1cols, int m2rows, int m2cols);

#endif
