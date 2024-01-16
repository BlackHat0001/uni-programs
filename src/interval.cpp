//---------- FILE interval.cpp
// Contains the implementation of the operators and methods defined in interval.h
//
// Copyright Daniel Marcovecchio
//
// Dependencies: iostream - For logging/printing purposes using std::cout, interval.h for declaration of interfaces
//----------

#include "interval.h"

/** Default Constructor
 * Initializes an interval with default values.
 */
interval::interval() {}

/** Overloaded Constructor
 * Initializes an interval with the same minimum and maximum values.
 *
 * @param _minMax The common value for both minimum and maximum.
 */
interval::interval(float _minMax) : min(_minMax), max(_minMax) {}

/** Overloaded Constructor
 * Initializes an interval with specified minimum and maximum values.
 *
 * @param _min The minimum value for the interval.
 * @param _max The maximum value for the interval.
 */
interval::interval(float _min, float _max) : min(_min), max(_max) {}

/** Copy Constructor
 * Initializes an interval by copying the values from another interval.
 *
 * @param x The interval to copy values from.
 */
interval::interval(interval &x) : min(x.min), max(x.max) {}

/** Destructor
 * Destructs the interval object.
 */
interval::~interval() {}

/** Assignment Operator Overload
 * Assigns the values of another interval to this interval.
 *
 * @param _b The interval to assign values from.
 * @return The interval after assignment.
 */
interval interval::operator=(const interval &_b) {
    this->max = _b.min;
    this->min = _b.min;
}

/** Addition Operator Overload
 * Adds two intervals element-wise.
 *
 * @param _b The interval to add.
 * @return The resulting interval.
 */
interval &interval::operator+(interval &_b) const {
    //{cmin, cmax}={amin+ bmin, amax+ bmax}
    return *(new interval(min + _b.min, max + _b.max));
}

/** Addition Assignment Operator Overload
 * Adds another interval to this interval element-wise.
 *
 * @param _b The interval to add.
 * @return A reference to this interval after addition.
 */
interval &interval::operator+=(interval &_b) {
    min += _b.min;
    max += _b.max;
    return *this;
}

/** Addition Operator Overload
 * Adds a float value to each element of the interval.
 *
 * @param _b The float value to add.
 * @return The resulting interval.
 */
interval &interval::operator+(float &_b) const {
    return *(new interval(min + _b, max + _b));
}

/** Addition Operator Overload
 * Adds an interval to a float value element-wise.
 *
 * @param _a The float value.
 * @param _b The interval to add.
 * @return The resulting interval.
 */
interval &operator+(float &_a, interval &_b) {
    return (_b + _a);
}

/** Subtraction Operator Overload
 * Subtracts two intervals element-wise.
 *
 * @param _b The interval to subtract.
 * @return The resulting interval.
 */
interval &interval::operator-(interval &_b) const {
    //{cmin, cmax}={amin- bmax, amax+ bmin}
    return *(new interval(min - _b.max, max + _b.min));
}

/** Subtraction Assignment Operator Overload
 * Subtracts another interval from this interval element-wise.
 *
 * @param _b The interval to subtract.
 * @return A reference to this interval after subtraction.
 */
interval &interval::operator-=(interval &_b) {
    min -= _b.max;
    max += _b.min;
    return *this;
}

/** Subtraction Operator Overload
 * Subtracts a float value from each element of the interval.
 *
 * @param _b The float value to subtract.
 * @return The resulting interval.
 */
interval &interval::operator-(float &_b) const {
    return *(new interval(min - _b, max + _b));
}

/** Subtraction Operator Overload
 * Subtracts an interval from a float value element-wise.
 *
 * @param _a The float value.
 * @param _b The interval to subtract.
 * @return The resulting interval.
 */
interval &operator-(float &_a, interval &_b) {
    return (_b - _a);
}

/** Multiplication Operator Overload
 * Multiplies two intervals element-wise.
 *
 * @param _b The interval to multiply.
 * @return The resulting interval.
 */
interval &interval::operator*(interval &_b) const {
    // {cmin, cmax}={ The minimum of amin*bmin, amin*bmax, amax*bmin, amax*bmax
    // The maximum of amin*bmin, amin*bmax, amax*bmin, amax*bmax }

    // First we define our matrix of our 4 operation combinations, for a multiplication
    float mat[4];
    mat[0] = min * _b.min;
    mat[1] = min * _b.max;
    mat[2] = max * _b.min;
    mat[3] = max * _b.max;

    // Now we define two variables that store our highest and lowest found
    float lowestFound = mat[0];
    float highestFound = mat[0];

    // Now we loop to find the highest and lowest operation result
    for (int i = 0; i < 4; ++i) {
        if (mat[i] < lowestFound) {
            lowestFound = mat[i];
        }
        if (mat[i] > highestFound) {
            highestFound = mat[i];
        }
    }

    // Return a reference to this new interval
    return *(new interval(lowestFound, highestFound));
}

/** Multiplication Assignment Operator Overload
 * Multiplies this interval by another interval element-wise.
 *
 * @param _b The interval to multiply.
 * @return A reference to this interval after multiplication.
 */
interval &interval::operator*=(interval &_b) const {
    return (*this * _b);
}

/** Division Operator Overload
 * Divides two intervals element-wise.
 *
 * @param _b The divisor interval.
 * @return The resulting interval.
 */
interval &interval::operator/(interval &_b) const {
    // {cmin, cmax}={ The minimum of amin*bmin, amin*bmax, amax*bmin, amax*bmax
    // The maximum of amin*bmin, amin*bmax, amax*bmin, amax*bmax }

    // First we define our matrix of our 4 operation combinations, for a division
    float mat[4];
    mat[0] = min / _b.min;
    mat[1] = min / _b.max;
    mat[2] = max / _b.min;
    mat[3] = max / _b.max;

    // Now we define two variables that store our highest and lowest found
    float lowestFound = mat[0];
    float highestFound = mat[0];

    // Now we loop to find the highest and lowest operation result
    for (int i = 0; i < 4; ++i) {
        if (mat[i] < lowestFound) {
            lowestFound = mat[i];
        }
        if (mat[i] > highestFound) {
            highestFound = mat[i];
        }
    }

    // Return a reference to this new interval
    return *(new interval(lowestFound, highestFound));
}

/** Division Assignment Operator Overload
 * Divides this interval by another interval element-wise.
 *
 * @param _b The divisor interval.
 * @return A reference to this interval after division.
 */
interval &interval::operator/=(interval &_b) const {
    return (*this / _b);
}

/** Get Minimum Value
 * Returns the minimum value of the interval.
 *
 * @return The minimum value.
 */
float interval::getMin() const {
    return min;
}

/** Get Maximum Value
 * Returns the maximum value of the interval.
 *
 * @return The maximum value.
 */
float interval::getMax() const {
    return max;
}

/** Stream Insertion Operator Overload
 * Outputs the interval values to the output stream.
 *
 * @param out The output stream.
 * @param c The interval to output.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &out, const interval &c) {
    out << c.min << " " << c.max << "\n";
    return out;
}

/** Stream Extraction Operator Overload
 * Inputs the interval values from the input stream.
 *
 * @param in The input stream.
 * @param c The interval to input values into.
 * @return The input stream.
 */
std::istream &operator>>(std::istream &in, interval &c) {
    in >> c.min;
    in >> c.max;
    return in;
}
