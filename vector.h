#if !defined(VECTOR)
#define VECTOR // double inclusion guard

class Vector {
private:
    float *value;
    int dimensions;
public:
    /**
     * @brief Construct a new Vector object
     * 
     * @param size the dimensions of the vector to be created
     * @param args the elements of the vector
     * @code Vector(3, {1,2,3}) @endcode
     * returns the 3D vector [1 2 3]
     */
    Vector(const int size, float args[]) {
        value = new float[size];
        dimensions = size;
        for (int i=0; i<dimensions; i++)
        {
            value[i] = args[i];
        }
    }

    ~Vector() {
        delete value;
    }

    /* Vector operations (that I'm interested in)
     * Addition - vector, scalar
     * Subtraction - vector, scalar
     * Negation - self (Vector)
     * Multiplication - vector (*, cross), scalar
    **/
    Vector add(Vector);         // Vector-Vector addition
    Vector add(float);          // Vector-Scalar addition
    Vector subtract(Vector);    // Vector-Vector subtraction
    Vector subtract(float);     // Vector-Scalar subtraction
    Vector negate();            // Unary Vector Negation
    float  dot(Vector);          // Vector-Vector Dot Product
    Vector product(float);      // Vector-Scalar Product


    /* Operator Overloading Bindings - to make life easier */    

    Vector operator+(Vector arg) {
        return this->add(arg);
    }

    Vector operator+(float arg) {
        return this->add(arg);
    } 

    Vector operator-(Vector arg) {
        return this->subtract(arg);
    }

    Vector operator-(float arg) {
        return this->subtract(arg);
    } 

    Vector operator-() {
        return this->negate();
    }      

    float operator*(Vector arg) {
        return this->dot(arg);
    }

    Vector operator*(float arg) {
        return this->product(arg);
    } 

};

/**
 * @brief Vector-Vector addition
 * 
 * @param arg vector to be added to this vector
 * @return Vector 
 */
Vector Vector::add(Vector arg) {

}


/**
 * @brief Vector-Scalar addition
 * 
 * @param arg scalar to be added elementwise to this vector
 * @return Vector 
 */
Vector Vector::add(float arg) {

}

/**
 * @brief Vector-Vector subtraction
 * 
 * @param arg vector to be subtracted from this vector
 * @return Vector 
 */
Vector Vector::subtract(Vector arg) {

}

/**
 * @brief Vector-Scalar subtraction
 * 
 * @param arg scalar to be subtracted elementwise from this vector
 * @return Vector 
 */
Vector Vector::subtract(float arg) {

}

/**
 * @brief Additive inverse
 * 
 * @return Vector 
 */
Vector Vector::negate()  {

}

/**
 * @brief Dot product
 * 
 * @param arg Vector to be multiplied elementwise to this vector
 * @return float 
 */
float  Vector::dot(Vector arg) {

}

/**
 * @brief Scalar multiplication
 * 
 * @param arg scalar to be multiplied elementwise to this vector
 * @return Vector 
 */
Vector Vector::product(float arg) {

}


#endif // VECTOR
