#include "Item.hpp"

Item::Item(double p, double w, int k):_profit(p), _weight(w), _key(k), _isInSolution(false){
}

Item::~Item(){}
double Item::profit() const{
	return _profit;
}
double Item::weight() const{
	return _weight;
}
bool Item::isInSolution(){
	return _isInSolution; 
}

void Item::isInSolution(bool b){
    _isInSolution = b;
}

int Item::key(){
	return _key;
}
 
void Item::profit(double p){
	_profit = p;
}
void Item::weight(double w){
	_weight = w; 
}

