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
	//c=correlation
	InstanceGen(double w, double n, double c);
	~InstanceGen();
	std::vector<Item*>& itemsVector();
	double W();
	double numOfItems();
        std::vector<Item*>& profitOnWeightVector();
private:
        std::vector<Item*> _profitOnWeightVector;
	std::vector<Item*> _items;
	double _fullW; 
	double _numOfItems;
};

#endif	/* INSTANCEGEN_HPP */

