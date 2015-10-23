#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>

#include "KNPsolver.hpp"
#include "Item.hpp"
#include "GlobalVar.hpp"
#include "InstanceGen.hpp"
#include "Solution.hpp"

struct ItemSorting {

    bool operator()(const Item* i1, const Item* i2) {
        return (i1->profit() / i1->weight()) >= (i2->profit() / i2->weight());
    }
};

KNPsolver::KNPsolver() {
}

void KNPsolver::BABsolver(InstanceGen* I, Solution* sol) {

    //Vector to store the bool x_{i}
    std::vector<bool> fixationVector;

    std::vector<bool> bestFixVector;

    for (int i = 0; i < I->itemsVector().size(); i++) {
        fixationVector.push_back(false);
        bestFixVector.push_back(false);
    }

    //Creating two solutions
    //currentSolution corresponds to the solution we are working on
    Solution* currentSolution = new Solution();

    Solution* copySol = new Solution();
    //bestSolution corresponds to the best Solution we have found for the moment
    Solution* bestSolution = new Solution();
    //double to store the value of the remaining weight in the knapsack

    double currentW = 0.0;
    double bestW = 0.0;
    double remainingWeight = I->W();

    Solution* greedySol = new Solution();
    greedySolver(I, greedySol);

    bool computedByGreedy = true;

    LB = greedySol->solValue();
    std::cout << "LB computed = " << LB << "\n";
    Solution* LPsol = new Solution();
    ;
    UB = LPsolver(I, LPsol, 0, 0.0);
    std::cout << "UB computed = " << UB << "\n";
    double currentValue = 0.0;
    double bestValue = 0.0;

    int fixationIndex = 0;

    while (1) {
        //std::cout << "In the while\n";
        if (fixationIndex == I->numOfItems()) {
            //std::cout << "All items set : LB = " << LB << " and currentValue = " << currentValue << "\n";
            fixationIndex--;
            if (currentValue > LB) {
                for (int i = 0; i < fixationVector.size(); i++) {
                    bestFixVector[i] = fixationVector[i];
                }
                bestValue = currentValue;
                bestW = currentW;
                LB = currentValue;
                computedByGreedy = false;
            }
            //backtrack(I, fixationVector, fixationIndex, currentValue, remainingWeight);
            while (fixationIndex > 0) {
                if (fixationVector[fixationIndex] == true) {
                    currentValue -= I->profitOnWeightVector().at(fixationIndex)->profit();
                    currentW -= I->profitOnWeightVector().at(fixationIndex)->weight();
                    fixationVector[fixationIndex] = false;
                    fixationIndex++;
                    break;
                }
                if (fixationVector[fixationIndex] == false) {
                    fixationVector[fixationIndex] = false;
                    fixationIndex--;
                    //std::cout << "fI = " << fixationIndex << "\n";
                }
            }
            if (fixationIndex == 0) {
                if (fixationVector[0] == true) {
                    currentValue = 0.0;
                    currentW = 0.0;
                    fixationVector[0] = false;
                    fixationIndex++;
                } else {
                    break;
                }
            }
        } else if ((fixationIndex < I->numOfItems())) {
            //std::cout << "AT the " << fixationIndex << " item and numOfItem = " << I->numOfItems() << "\n";
            //forward(I, fixationVector, fixationIndex, currentValue, remainingWeight);
            LPsol = new Solution(currentValue, currentW);
            double result = LPsolver(I, LPsol, fixationIndex, currentW);
            //std::cout << "result = " << result << "\n";
            if (result > LB) {
                if ((currentW + I->profitOnWeightVector().at(fixationIndex)->weight()) <= remainingWeight) {
                    currentW += I->profitOnWeightVector().at(fixationIndex)->weight();
                    currentValue += I->profitOnWeightVector().at(fixationIndex)->profit();
                    fixationVector[fixationIndex] = true;
                    //std::cout << "fixVector[" << fixationIndex << "] = " << fixationVector[fixationIndex] << "\n";
                } else
                    fixationVector[fixationIndex] = false;
                fixationIndex++;
            } else {
                while (fixationIndex > 0) {
                    if (fixationVector[fixationIndex] == false) {
                        fixationIndex--;
                    }
                    if (fixationVector[fixationIndex] == true) {
                        currentValue -= I->profitOnWeightVector().at(fixationIndex)->profit();
                        currentW -= I->profitOnWeightVector().at(fixationIndex)->weight();
                        fixationVector[fixationIndex] = false;
                        fixationIndex++;
                        break;
                    }
                }
                if (fixationIndex == 0) {
                    if (fixationVector[0] == true) {
                        currentValue = 0.0;
                        currentW = 0.0;
                        fixationVector[0] = false;
                        fixationIndex++;
                    } else {
                        break;
                    }
                }
            }
        }

    }
    for (int i = 0; i < bestFixVector.size(); i++) {
        //std::cout << "bfv[" << i << "]=" << bestFixVector[i] << "\n";
        if (bestFixVector[i] == true) {
            sol->addItem(I->profitOnWeightVector().at(i));
        }
    }
    std::cout << "computedByGreedy? " << computedByGreedy << "\n";
}

double KNPsolver::LPsolver(InstanceGen* I, Solution* sol, int index, double currentW) {
    std::vector<Item*>::iterator iteItem = (I->profitOnWeightVector().begin());
    int i = 0;
    if (index > 0)
        while (i < index) {
            i++;
            iteItem++;
        }
    while ((iteItem != I->profitOnWeightVector().end()) && ((((*iteItem)->weight()) + (sol->solWeight())) <= (I->W()))) {
        sol->addItem((*iteItem));
        iteItem++;
    }
    if ((iteItem != I->profitOnWeightVector().end()) && ((I->W() - sol->solWeight()) > 0)) {

        double fraction = (double) (((double) (I->W() - sol->solWeight())) / ((double) (*iteItem)->weight()));
        sol->addFractedItem(fraction, (*iteItem));
    }
    return sol->solValue();
}

void KNPsolver::greedySolver(InstanceGen* I, Solution * greedySol) {
    for (std::vector<Item*>::iterator iteItem = (I->profitOnWeightVector().begin()); iteItem != I->profitOnWeightVector().end(); iteItem++) {
        //std::cout << ((*iteItem)->weight()) << " + " << (greedySol->solWeight()) << " = " << (((*iteItem)->weight()) + (greedySol->solWeight())) << " <=" << (I->W()) << "? " << ((((*iteItem)->weight()) + (greedySol->solWeight())) <= (I->W())) << "\n";
        if ((((*iteItem)->weight()) + (greedySol->solWeight())) <= (I->W()))
            greedySol->addItem((*iteItem));
    }
}

int KNPsolver::Dynamic(InstanceGen* I) {
    Solution* LPSol = new Solution();
    LPsolver(I, LPSol, 0, 0.0);

    int sumW = 0;

    for (int i = 0; i < (int) I->numOfItems(); i++) {
        sumW += (int) I->itemsVector().at(i)->weight();
    }
    std::cout << "sum= " << sumW << " W = " << I->W() << " int? " << ((int) I->W());
    sumW = std::max(sumW, (int) I->W());
    std::cout << " maxW = " << sumW << "\n";

    int criticalIndex = LPSol->listOfItems().size() - 1;
    int criticalW = 0;
    int criticalP = 0;
    std::vector<Item*>::iterator iteItemC = I->profitOnWeightVector().begin();
    int i = 0;
    while (i < criticalIndex) {
        criticalW += ((int) (*iteItemC)->weight());
        criticalP += ((int) (*iteItemC)->profit());
        i++;
        iteItemC++;
    }
    std::vector<Item*>::iterator iteItemA = iteItemC;
    std::vector<Item*>::iterator iteItemB = iteItemA;
    iteItemB--;
    int indexA = criticalIndex;
    int indexB = criticalIndex - 1;
    int *V;

    V = new int[sumW + 1];

    for (int i = 0; i < criticalW; i++) {
        V[i] = 0;
    }
    for (int i = criticalW; i < (sumW + 1); i++) {
        V[i] = criticalP;
    }

    int maxA = 0;
    int maxB = 0;
    int max = 0;
    bool boolA;
    bool boolB;

    for (int i = 0; i < (sumW + 1); i++) {
        while ((iteItemA != I->profitOnWeightVector().begin()) && (iteItemB != I->profitOnWeightVector().end())) {
            maxA = 0;
            maxB = 0;
            max = 0;
            boolA = false;
            boolB = false;
            for (int t = 0; t < 2; t++) {
                if ((t == 0) && (iteItemA != I->profitOnWeightVector().begin())) {
                    iteItemA--;
                    if ((i + ((int) (*iteItemA)->weight())) <= sumW) {
                        //std::cout << "firts\n";
                        maxA = std::max(V[i], V[i + ((int) (*iteItemA)->weight())] - ((int) (*iteItemA)->profit()));
                        if (maxA == V[i])
                            boolA = false;
                        else
                            boolA = true;
                    } else {
                        maxA = 0;
                    }
                } else if ((t == 1)&&(iteItemB != I->profitOnWeightVector().end())) {
                    iteItemB++;
                    if ((i - ((int) (*iteItemB)->weight())) >= 0) {
                        //std::cout << "second\n";
                        maxB = std::max(V[i], V[i - ((int) (*iteItemB)->weight())] + ((int) (*iteItemB)->profit()));
                        if (maxB == V[i])
                            boolB = false;
                        else
                            boolB = true;
                    } else {
                        maxB = 0;
                    }
                }
            }
            max = std::max(maxA, maxB);

            if (max == maxA) {
                //std::cout << "maxA  " << (iteItemA != I->profitOnWeightVector().end()) << "\n";
                V[i] = maxA;
                if (iteItemA != I->profitOnWeightVector().begin())
                    (*iteItemA)->isInSolution(boolA);
            } else {
                //std::cout << "maxB\n";
                V[i] = maxB;
                if (iteItemB != I->profitOnWeightVector().end())
                    (*iteItemB)->isInSolution(boolB);
            }
        }
        iteItemA = iteItemC;
        iteItemB = iteItemC;
        iteItemB--;
    }
    int result = V[((int) I->W())];
    delete[] V;
    return result;
}
