//
// Created by kai on 3/1/16.
//Khuong Nguyen         101384005
//Instructor: Ivo George
//Class: CSCI 2312 002  Springs 2016
//HW#: PA2              Due Date: 03/02/2016

#include "Point.h"
#include <cmath>
#include <sstream>
#include <iostream>


class Point;
namespace Clustering{

    typedef Point * PointPtr;
    unsigned int Point:: __idGen = 0;

    Point::Point(int dim) {

        __id = __idGen++;       //Set __id = __idGen;

        __values = new double [dim];

        __dim = dim; // Parameter

        for (int i = 0; i < dim; ++i){
            __values[i]= 0.0;
        }

    }


    Point::Point(int dim, double * newdim) {
        __id = __idGen++;
        __values = newdim;
        __dim = dim;
    }

    // Accessors and Mutators

    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    double Point::getValue(int p) const {
        return __values[p];
    }

    void Point::setValue(int p, double value) {
        __values[p] = value;
    }

    // Big three: cpy ctor, overloaded operator=, dtor

    Point::Point(const Point & p1) {
        __id = p1.__id;
        __dim = p1.getDims();
        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i)
            __values[i] = p1.getValue(i);

    }

    Point & Point::operator=(const Point & other){
        if (this == &other){
            return *this;
        }
        else {
            for (int i= 0; i < __dim; ++i)
            {
                this ->__values[i] = other.getValue(i);
            }
            return *this;
        }
    }

    Point::~Point() {
        delete [] __values;
    }

    // Functions

    double Point::distanceTo(const Point &d) const {
        double sum= 0.0;

        for (int i = 0; i < __dim ; ++i){
            sum = pow(__values[i] - d.getValue(i) , 2);
        }
        return sqrt(sum);
    }

    // Overloaded operators

    // Members

    // Multiplication functions

    Point& Point::operator*=(double multip) {
        for (int i = 0; i < __dim; ++i){
            __values[i] = __values[i] * multip;
        }
        return *this;
    }

    // p1*2 = p2
    const Point Point::operator*(double multip) const {
        Point * other = new Point(__dim);

        for (int i = 0; i < __dim; ++i){
            other->__values[i] = __values[i] * multip;
        }
    }

    // Dividation functions

    Point& Point::operator/=(double divide) {
        for (int i = 0; i < __dim; ++i){
            __values[i]= __values[i] / divide;
        }
        return *this;
    }

    // p1/2 = p3
    const Point Point::operator/(double divide) const {
        Point *other = new Point(__dim);

        for (int i = 0; i < __dim; ++i){
            other->__values[i] = __values[i] / divide;
        }
    }

    double & Point::operator[](int index) {
        return __values[index];
    }

    // Friend functions

    Point& operator+=(Point & p1, const Point & p2) {
        Point *other = new Point(p2);

        for (int i = 0; i < p1.__dim; ++i){
            p1.__values[i] = p1.__values[i] + other->getValue(i);
        }
        delete other;
        return p1;
    }

    Point& operator-=(Point & p1, const Point & p2) {
        Point* other = new Point(p2);

        for (int i= 0; i < p1.__dim; ++i){
            p1.__values[i] = p1.__values[i] - other->getValue(i);
        }
        delete other;
        return p1;
    }

    const Point operator+(const Point & p1, const Point & p2) {
        Point * other = new Point(p1);
        *other += p2;
        return *other;
    }

    const Point operator-(const Point & p1, const Point & p2) {
        Point *other = new Point(p1);
        *other -= p2;
        return *other;
    }

    bool operator==(const Point & p1, const Point & p2) {
        bool results = true;

        if (p1.__id != p2.__id){
            return false;
        }
        if(p1.__dim != p2.__dim)
        {   return false;        }

        for (int i= 0; i< p1.getDims(); ++i){
            if (p1.__values[i] != p2.__values[i]){
                results = false;
            }
        }
        return results;
    }

    bool operator!=(const Point & p1, const Point &p2){
        return !(p1 == p2);
    }

    bool operator<(const Point &p1, const Point &p2){
        if (p1.__dim < p2.__dim)
        { return true;}
        if (p1.__dim > p2.__dim)
        { return false;}

        for (int i = 0; i < p1.getDims(); ++i){
            if (p1.__values[i] < p1.__values[i]){
                return true;
            }else
                return false;
        }
        return false;
    }

    bool operator>(const Point &p1, const Point &p2){
        if (p1.__dim > p2.__dim )
        { return true;}
        if (p1.__dim < p2.__dim)
        { return false;}

        for (int i = 0; i < p1.getDims(); ++i){
            if (p1.__values[i] > p2.__values[i])
            { return true;} else return false;
        }
        return false;
    }

    bool operator<=(const Point & p1, const Point &p2){
        if(p1 < p2)
        { return true;}
        if (p1>p2)
        { return false;}
        return true;
    }
    bool operator>=(const Point &p1, const Point &p2){
        if(p1 > p2){ return true;}
        if(p1 < p2) { return false;}

        return true;
    }

    std::ostream &operator<<(std::ostream & output, const Point &p){
        int i = 0;
        for (; i < p.getDims(); ++i){
            output << p.getValue(i);
            output << " , ";
        }

        output << p.getValue(i);
        return output;
    }

    std::istream &operator>>(std::istream &input, Point & p){
        double other;
        std:: string line;
        std:: string buff;
        int i = -1;
        while(getline(input,line)){

            std::stringstream lineS(line);
            while(getline(lineS, buff, ','))
            {
                other = std::stod (buff);
                p.setValue(++i, other);
            }
        }
        return input;
    }
}



