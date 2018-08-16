#include <iostream>

#if !defined(VECTOR)
#define VECTOR // double inclusion guard

class Vector {
public:
    float *value;
    int dimensions;

    /**
     * @brief Default Contructor. 0 dimensional. value points to NULL
     * 
     */
    Vector() {
        this->value = NULL;
        this->dimensions = 0;
    }

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
        for (int i=0; i<dimensions; i++) {
            value[i] = args[i];
        }
    }

    /**
     * @brief Copy Constructor, allows deep copy of values
     * 
     * @param arg Vector to be copied
     */
    Vector(const Vector &arg) {
        if (this->value != NULL)
            delete this->value;
        this->value = new float[arg.dimensions];
        this->dimensions = arg.dimensions;
        for (int i=0; i<dimensions; i++) {
            this->value[i] = arg.value[i];
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

    /* Assignment, ~just~ almost like the copy constructor */
    void operator=(Vector arg) {
        //this->value = new float[arg.dimensions];
        this->dimensions = arg.dimensions;
        for (int i=0; i<dimensions; i++) {
            this->value[i] = arg.value[i];
        }
    }

};

/**
 * @brief Vector-Vector addition
 * 
 * @param arg vector to be added to this vector
 * @return Vector 
 */
Vector Vector::add(Vector arg) {
    if (arg.dimensions != this->dimensions) {
        std::cerr << "ERROR: Dimensions of operands don't match\n"
        << "Output will be a " << dimensions << "dimensional vector\n";
    }

    float *ans_values = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_values[i] = this->value[i] + arg.value[i];
    }

    Vector ans(dimensions, ans_values);
    delete ans_values;

    return ans;
}


/**
 * @brief Vector-Scalar addition
 * 
 * @param arg scalar to be added elementwise to this vector
 * @return Vector 
 */
Vector Vector::add(float arg) {
    float *ans_values = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_values[i] = this->value[i] + arg;
    }

    Vector ans(dimensions, ans_values);
    delete ans_values;

    return ans;
}

/**
 * @brief Vector-Vector subtraction
 * 
 * @param arg vector to be subtracted from this vector
 * @return Vector 
 */
Vector Vector::subtract(Vector arg) {
    if (arg.dimensions != this->dimensions) {
        std::cerr << "ERROR: Dimensions of operands don't match\n"
        << "Output will be a " << dimensions << "dimensional vector\n";
    }

    float *ans_values = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_values[i] = this->value[i] - arg.value[i];
    }

    Vector ans(dimensions, ans_values);
    delete ans_values;

    return ans;
}

/**
 * @brief Vector-Scalar subtraction
 * 
 * @param arg scalar to be subtracted elementwise from this vector
 * @return Vector 
 */
Vector Vector::subtract(float arg) {
    float *ans_values = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_values[i] = this->value[i] - arg;
    }

    Vector ans(dimensions, ans_values);
    delete ans_values;

    return ans;
}

/**
 * @brief Additive inverse
 * 
 * @return Vector 
 */
Vector Vector::negate()  {
    float *ans_values = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_values[i] = -this->value[i];
    }

    Vector ans(dimensions, ans_values);
    delete ans_values;

    return ans;
}

/**
 * @brief Dot product
 * 
 * @param arg Vector to be multiplied elementwise to this vector
 * @return float 
 */
float  Vector::dot(Vector arg) {
    if (arg.dimensions != this->dimensions) {
        std::cerr << "ERROR: Dimensions of operands don't match\n"
        << "Vectors will be truncated to " << dimensions << "dimensions\n";
    }

    float ans = 0;
    for (int i=0; i<dimensions; i++) {
        ans += this->value[i] * arg.value[i];
    }

    return ans;
}

/**
 * @brief Scalar multiplication
 * 
 * @param arg scalar to be multiplied elementwise to this vector
 * @return Vector 
 */
Vector Vector::product(float arg) {
    float *ans_value = new float[dimensions];
    for (int i=0; i<dimensions; i++) {
        ans_value[i] = this->value[i] * arg;
    }

    Vector ans(dimensions, ans_value);
    delete ans_value;

    return ans;
}


#endif // VECTOR
