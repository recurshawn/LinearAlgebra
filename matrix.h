#include <iostream>
#include "vector.h"

#if !defined(MATRIX)
#define MATRIX // Double Inclusion Guard

enum matrix_type {ZERO, IDENTITY};
#define MIN(a,b) (a<b?a:b)

class Matrix {
public:
    float **values;
    int row, col;
    
    /**
     * @brief Construct a new Matrix object. Default constructor. Sets values to NULL or 0
     * 
     */
    Matrix() {
        values = NULL;
        row = col = 0;
    }

    /**
     * @brief Construct a new Matrix object
     * 
     * @param arg Vector object to be copied
     */
    Matrix(const Matrix &arg) {
        // Clear the old attributes first
        if ((row!=0) || (values!=NULL)) {
            // Go through the inital column
            for (int i=0; i<row; i++) {
                delete values[i];
            }
        }

        this->row = arg.row;
        this->col = arg.col;
        
        this->values = new float *[row];
        for (int i=0; i<row; i++) {
            this->values[i] = new float[col];
            for (int j=0; j<col; j++) {
                this->values[i][j] = arg.values[i][j];
            }
        }
    }

    /**
     * @brief Construct a new Matrix object
     * 
     * @param dimensions Dimensions of the matrix. Each element of the array corresponds to the size of one dimension
     * @param args The values to be filled into each cell
     */
    Matrix(int rows, int columns, const float *args[]) {
        this->row = rows;
        this->col = columns;
        
        this->values = new float *[row];
        for (int i=0; i<row; i++) {
            this->values[i] = new float[col];
            for (int j=0; j<col; j++) {
                this->values[i][j] = args[i][j];
            }
        }
    }

    /**
     * @brief Construct a new Matrix object
     * 
     * @param rows Number of rows
     * @param columns Number of cols
     * @param matrix_type type of matrix @code enum matrix_type {ZERO, IDENTITY} @endcode
     */
    Matrix(int rows, int columns, enum matrix_type arg) {
        this->row = rows;
        this->col = columns;

        this->values = new float *[row];
        for (int i=0; i<row; i++) {
            this->values[i] = new float[col];
            for (int j=0; j<col; j++) {
                if ((arg == IDENTITY) && (i==j))
                    this->values[i][j] = 1.0f;
                else
                    this->values[i][j] = 0.0f;
            }
        }
    }

    /* Matrix Operations (that I'm interested in) */
    /* Add
     * Subtract
     * Multiply - Matrix*Matrix & Matrix*Vector
     */
    Matrix add(const Matrix &arg);
    Matrix sub(const Matrix &arg);
    Matrix multiply(const Matrix &arg);
    Vector multiply(const Vector &arg);

    /* Operator Overload Bindings*/
    inline Matrix operator+ (const Matrix &arg) {
        return add(arg);
    }

    inline Matrix operator- (const Matrix &arg) {
        return sub(arg);
    }

    inline Matrix operator* (const Matrix &arg) {
        return multiply(arg);
    }

    inline Vector operator* (const Vector &arg) {
        return multiply(arg);
    }
};

Matrix Matrix::add(const Matrix &arg) {
    Matrix ans(MIN(this->row, arg.row), MIN(this->col, arg.col), ZERO);
    if ((this->row != arg.row) || (this->col != arg.col)) {
        std::cerr << "ERROR: The dimensions of operands don't match\n"
        << "Output will be a " << MIN(this->row, arg.row) << "x" << MIN(this->col, arg.col) << "matrix\n";
    }

    for (int i=0; i<MIN(this->row, arg.row); i++) {
        for (int j=0; j<MIN(this->col, arg.col); j++) {
            ans.values[i][j] = this->values[i][j] + arg.values[i][j];
        }
    }

    return ans;
}

Matrix Matrix::sub(const Matrix &arg) {
    Matrix ans(MIN(this->row, arg.row), MIN(this->col, arg.col), ZERO);

    if ((this->row != arg.row) || (this->col != arg.col)) {
        std::cerr << "ERROR: The dimensions of operands don't match\n"
        << "Output will be a " << MIN(this->row, arg.row) << "x" << MIN(this->row, arg.row) << "matrix\n";
    }

    for (int i=0; i<MIN(this->row, arg.row); i++) {
        for (int j=0; j<MIN(this->col, arg.col); j++) {
            ans.values[i][j] = this->values[i][j] - arg.values[i][j];
        }
    }

    return ans;
}

Matrix Matrix::multiply(const Matrix &arg) {

}

Vector Matrix::multiply(const Vector &arg) {

}

#endif //MATRIX