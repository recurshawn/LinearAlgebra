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
    Matrix(const Matrix &arg) : Matrix() {
        // Clear the old attributes first
        if ((row!=0) || (values!=NULL)) {
            // Go through the inital column
            for (int i=0; i<row; i++) {
                delete values[i];
            }
        }

        row = arg.row;
        col = arg.col;
        
        values = new float *[row];
        for (int i=0; i<row; i++) {
            values[i] = new float[col];
            for (int j=0; j<col; j++) {
                values[i][j] = arg.values[i][j];
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
        row = rows;
        col = columns;
        
        values = new float *[row];
        for (int i=0; i<row; i++) {
            values[i] = new float[col];
            for (int j=0; j<col; j++) {
                values[i][j] = args[i][j];
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
        row = rows;
        col = columns;

        values = new float *[row];
        for (int i=0; i<row; i++) {
            values[i] = new float[col];
            for (int j=0; j<col; j++) {
                if ((arg == IDENTITY) && (i==j))
                    values[i][j] = 1.0f;
                else
                    values[i][j] = 0.0f;
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

/**
 * @brief Add two matrices together
 * 
 * @param arg the matrix to be added to this matrix
 * @return Matrix
 */
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

/**
 * @brief Subtract one matrix from another
 * 
 * @param arg Matrix to be subtracted from this matrix
 * @return Matrix
 */
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

/**
 * @brief Multiply two matrices together 
 * 
 * @param arg Matrix to be multiplied with this matrix
 * @return Matrix
 */
Matrix Matrix::multiply(const Matrix &arg) {
    if (this->col != arg.row) {
        std::cerr << "ERROR: Cannot multiply matrices [" 
        << this->row << "][" << this->col << "]x[" << arg.row << "][" << arg.col << "]\n"
        << "Empty matrix will be returned.\n";
        return Matrix();
    }

    Matrix ans(this->row, arg.col, ZERO);

    for (int i=0; i<ans.row; i++) {
        for (int j=0; j<ans.col; j++) {
            for (int k=0; k<arg.row; k++) {
                ans.values[i][j] += this->values[i][k] * arg.values[k][j];
            }
        }
    }

    return ans;
}

/**
 * @brief Multiply a vector with this matrix
 * 
 * @param arg Vector to be multiplied with this matrix
 * @return Vector 
 */
Vector Matrix::multiply(const Vector &arg) {
    if (this->col != arg.dimensions) {
        std::cerr << "ERROR: Cannot multiply matrice and vector [" 
        << this->row << "][" << this->col << "]x[" << arg.dimensions << "]\n"
        << "Empty vector will be returned.\n";
        return Vector();
    }

    Vector ans(this->row);

    for (int i=0; i<ans.dimensions; i++) {
        for( int j=0; j<this->col; j++) {
            ans.value[i] += this->values[i][j] * arg.value[j];
        }
    }

    return ans;
}

#endif //MATRIX