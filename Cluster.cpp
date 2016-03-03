//
// Created by kai on 3/1/16.
//Khuong Nguyen         101384005
//Instructor: Ivo George
//Class: CSCI 2312 002  Springs 2016
//HW#: PA2              Due Date: 03/02/2016

#include <cassert>
#include <cstdlib>
#include "Cluster.h"
#include <sstream>


namespace Clustering {

    LNode::LNode(const Point &p, LNodePtr n) : point(p) {
        next = n;
    }

    void Cluster::__cpy(LNodePtr pts) {
        if (pts == NULL){
            __points = NULL;
            __size = 0;
            return;
        }
        LNodePtr previousPtr = pts;
        LNodePtr current_ptr = __points = new LNode(previousPtr->point, NULL);

        while (previousPtr->next != NULL){
            previousPtr = previousPtr->next;
            current_ptr->next = new LNode(previousPtr->point, NULL);
            current_ptr = current_ptr->next;
        }
    }

    bool Cluster::__in(const Point &p) const {
        bool results = false;

        LNodePtr current_ptr = __points;
        while (current_ptr != NULL){
            if (current_ptr->point == p ){
                results = true;
                break;
            }
            current_ptr = current_ptr->next;

        }
        return results;
    }
    Cluster::Cluster() {
        __size = 0;
        __points = NULL;
    }

    // The big three: cpy ctor, overloaded operator=, dtor

    Cluster::Cluster(const Cluster & p) : __size(p.__size){
        __cpy(p.__points);
    }

    Cluster& Cluster::operator=(const Cluster &p) {
        if(*this != p){
            LNodePtr cursor = __points;
            LNodePtr next_ptr;

            while (cursor != NULL){
                next_ptr = cursor->next;
                delete cursor;
                cursor = next_ptr;
                __size--;
            }
        }
        else { return *this;}
        LNodePtr p2 = p.__points;
        for (int i = 0; i <p.getSize() ; ++i) {
            add(p2->point);
            if(p2->next != NULL){
                p2 = p2->next;
            }

        }
        return *this;
    }

    Cluster::~Cluster() {
        LNodePtr  cursor = __points;
        LNodePtr  next_ptr;

        while (cursor != NULL){
            next_ptr= cursor->next;
            delete cursor;
            cursor = next_ptr;
            if(next_ptr != NULL){
                next_ptr = next_ptr->next;
            }
        }
    }

    //Getters/Setters
    int Cluster::getSize() const {
        return __size;
    }

    // Set functions: They allow calling c1.add(c2.remove(p));

    void Cluster::add(const Point &p) {
        LNodePtr newNode = new LNode(p,NULL);
        LNodePtr current;
        LNodePtr previous_Ptr;
        newNode ->point = p;

        if(__points == NULL){
            __points = newNode;
            newNode->next = NULL;
        }
        else
        {
            current = __points;
            previous_Ptr = NULL;

            while(current != NULL && current->point <= p){
                previous_Ptr = current;
                current = current->next;
            }
            if (previous_Ptr == NULL){
                __points = newNode;
                newNode->next = current;
            }
            else
            {
                previous_Ptr->next = newNode;
                newNode->next = current;
            }
        }
        __size ++;
    }

    const Point &Cluster::remove(const Point &p) {
        LNodePtr current;
        LNodePtr previous_Ptr = __points;

        if(__points== NULL){
            return p;
        }
        if (__points->point == p){
            current = __points->next;
            delete __points;
            __points = current;
        }
        else
        {
            current = __points;

            while(current != NULL && current->point != p){
                previous_Ptr = current;
                current = current->next;
            }
            if(current->point == p){
                previous_Ptr->next = current->next;
                delete current;
            }
            else
            {
                std::cout << "This is invalid point. \n" << std::endl;
            }
        }
        __size--;
        return p;
    }

    bool Cluster:: contains(const Point &theWantedOne) // I'm getting tired of p
    {
        bool answer = false;
        LNodePtr cursor = __points;

        for (cursor = __points; cursor != NULL; cursor = cursor->next)
        {
            if (cursor->point == theWantedOne)
                answer = true;
        }
        return answer;


    }

// Overloaded operators

// Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const // notice: const
    {
        LNodePtr current = __points;

        if (current != NULL)
        {
            for (int i=0; i<index; i++)
            {
                current = current->next;
            }
        }
        return current->point;

    }

// Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &p)
    {
        LNodePtr current = __points;
        current->point += p;
        __size++;
    }

    Cluster &Cluster::operator-=(const Point &p)
    {
        remove(p);
        __size--;
    }

// Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster &p) // union
    {
        LNodePtr current = p.__points;

        while (current != NULL){
            if (!contains(current->point))
            {
                add(current->point);
            }
            current = current->next;
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &p) // (asymmetric) difference
    {
        LNodePtr current = p.__points;

        while (current != NULL){
            if (__in(current->point)){
                remove(current->point);
            }
            current = current->next;
        }
        return *this;
    }

// Friends: IO
    std::ostream &operator<<(std::ostream &out, const Cluster &p)
    {
        LNodePtr cursor = p.__points;
        for ( ; cursor != NULL; cursor = cursor->next)
            out << cursor->point << std::endl;
    }

    std::istream &operator>>(std::istream &in, Cluster &p)
    {
        std:: string temp;
        while (getline(in,temp) && in.peek()){
            int line = std::count(temp.begin(), temp.end(), ",");
            Point a(line + 1);
            std::stringstream other(temp);
            other >> a;
            p.add(a);
        }
    }

// Friends: Comparison
    bool operator==(const Cluster &p1, const Cluster &p2)
    {
        if (p1.__size != p2.__size)
            return false;

        LNodePtr p1current = p1.__points;
        LNodePtr p2current = p2.__points;
        while (p1current != NULL)
        {
            if (p1current->point != p2current->point )
            {
                return false;
            }
            else
            {
                p2current = p2current->next;
                p1current = p1current->next;
            }
        }
        return true;
    }

    bool operator!=(const Cluster &p1, const Cluster &p2){
        return !(p1 == p2);
    }

    // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &p1, const Point &p2) {
        Cluster p(p1);
        p +=p2;
        return p;
    }
    const Cluster operator-(const Cluster &p1, const Point &p2){
        Cluster p(p1);
        p -= p2;
        return p;
    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &p1, const Cluster &p2) // union
    {

    }
    const Cluster operator-(const Cluster &, const Cluster &) {

    }
}