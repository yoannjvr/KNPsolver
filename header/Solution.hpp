/* 
 * File:   Solution.hpp
 * Author: yoannjvr
 *
 * Created on 18 octobre 2015, 22:47
 */

#ifndef SOLUTION_HPP
#define	SOLUTION_HPP

#include <list>

#include "Item.hpp"

class Solution{
public:
	Solution();
        Solution(double value, double weight);
	~Solution();

	double solValue();
	std::list<Item*>& listOfItems();
	std::list<Item*>& listOfItems(std::list<Item*>& listToCopy);
	void addItem(Item* i);
	double solWeight();
        void addFractedItem(double fraction, Item* i);
private:
	double _solValue;
	double _solWeight;
	std::list<Item*> _listOfItems;
};

#endif	/* SOLUTION_HPP */

