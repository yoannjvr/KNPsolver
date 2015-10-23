#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "InstanceGen.hpp"
#include "Item.hpp"

struct ItemSorting {

    bool operator()(const Item* i1, const Item * i2) {
        return (i1->profit() / i1->weight()) >= (i2->profit() / i2->weight());
    }

};

InstanceGen::InstanceGen(double w, double n, double c) : _fullW(w), _numOfItems(n) {
    srand(time(NULL));
    //Sample a random weight between 100000 and 100	
    int randomWeight = rand() % 10000 + 100;
    std::cout << "randoW = " << randomWeight << "\n";
    int correlationCoeff;

    Item* itemToAdd;
    int ratio = (int) (((double) 3 / 4) * w);
    for (int i = 0; i < n; i++) {

        int randItemWeight = rand() % ratio + 0;
        int randItemProfit = rand() % 1000 + 0;

        randItemProfit = (int) (((1.0 - c) * double(randItemProfit)) + (c * double(randItemWeight)));

        itemToAdd = new Item(randItemProfit, randItemWeight, i);
        this->_profitOnWeightVector.push_back(itemToAdd);
        std::sort(this->_profitOnWeightVector.begin(), this->_profitOnWeightVector.end(), ItemSorting());
        this->_items.push_back(itemToAdd);
        std::cout << "i = " << i << "\n";
    }
    std::cout << "out\n";
}

std::vector<Item*>& InstanceGen::itemsVector() {
    return _items;
}

double InstanceGen::W() {
    return _fullW;
}

double InstanceGen::numOfItems() {
    return _numOfItems;
}

std::vector<Item*>& InstanceGen::profitOnWeightVector() {
    return _profitOnWeightVector;
}
