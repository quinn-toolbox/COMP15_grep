/*
 * Filename: NodeType.h
 * Contains: Interface of the template NodeType class 
 * Part of: Project 2 assignment "Gerp" for Comp 15 Fall 2018
 * Adapted from: HW5 provided NodeType class
 */

#ifndef NODE_TYPE_H_
#define NODE_TYPE_H_

using namespace std;

template<class E>
struct NodeType
{
    E info;
    NodeType *next;
};

#endif
