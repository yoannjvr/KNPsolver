#include "Solution.hpp"

Solution::Solution() : _solValue(0.0), _solWeight(0.0) {
}

Solution::Solution(double value, double weight):_solValue(value), _solWeight(weight){
}

double Solution::solValue() {
    return _solValue;
}

std::list<Item*>& Solution::listOfItems() {
    return _listOfItems;
}

std::list<Item*>& Solution::listOfItems(std::list<Item*>& listToCopy) {
    for (std::list<Item*>::iterator iteItemsCopy = listToCopy.begin(); iteItemsCopy != listToCopy.end(); iteItemsCopy++) {
        _listOfItems.push_back((*iteItemsCopy));
    }
}

double Solution::solWeight() {
    return _solWeight;
}

void Solution::addItem(Item* i) {
    _listOfItems.push_back(i);
    _solValue += i->profit();
    _solWeight += i->weight();
}

void Solution::addFractedItem(double fraction, Item* i) {
    _listOfItems.push_back(i);
    _solValue += (i->profit()) * fraction;
    _solWeight += (i->weight()) * fraction;
}