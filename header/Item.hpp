/* 
 * File:   Item.hpp
 * Author: yoannjvr
 *
 * Created on 18 octobre 2015, 22:46
 */

#ifndef ITEM_HPP
#define	ITEM_HPP


class Item{
public: 
	Item(double p, double w, int k);
	~Item();
	int key();
	double profit() const;
	double weight() const;
	bool isInSolution();
        void isInSolution(bool);
private: 
	int _key;
	bool _isInSolution;
	double _profit; 
	double _weight;
	void profit(double p);
	void weight(double w);
};


#endif	/* ITEM_HPP */

