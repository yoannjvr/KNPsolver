/* 
 * File:   InstanceGen.hpp
 * Author: yoannjvr
 *
 * Created on 18 octobre 2015, 22:48
 */


#ifndef INSTANCEGEN_HPP
#define INSTANCEGEN_HPP

#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include "Item.hpp" 

class InstanceGen{
public: 
	//c=correlation, w=weight, n=number of items
	InstanceGen(double w, double n, double c);
	~InstanceGen();
	std::vector<Item*>& itemsVector();
	//Returns the wieght of the knapsack
	double W();
	//Returns the number of items in the instance
	double numOfItems();
        std::vector<Item*>& profitOnWeightVector();
private:
    std::vector<Item*> _profitOnWeightVector;
	std::vector<Item*> _items;
	double _fullW; 
	double _numOfItems;
};

#endif	/* INSTANCEGEN_HPP */

