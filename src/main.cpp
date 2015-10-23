/* 
 * File:   main.cpp
 * Author: yoannjvr
 *
 * Created on 18 octobre 2015, 22:44
 */


#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "InstanceGen.hpp"
#include "Solution.hpp"
#include "KNPsolver.hpp"
#include "myClock.h"

/*
 * 
 */
void printInstance(InstanceGen* I) {
    std::cout << "Number of items :" << I->numOfItems() << "\n";
    std::cout << "Weight = " << I->W() << "\n";
    for (int i = 0; i < I->itemsVector().size(); i++) {
        std::cout << "item " << i << " (" << I->itemsVector().at(i)->profit() << ", " << I->itemsVector().at(i)->weight() << ", " << I->itemsVector().at(i)->key() << ")\n";
    }
    for (int i = 0; i < I->profitOnWeightVector().size(); i++) {
        std::cout << "item " << i << " (" << I->profitOnWeightVector().at(i)->profit() << ", " << I->profitOnWeightVector().at(i)->weight() << ", " << I->profitOnWeightVector().at(i)->key() << ")\n";
    }
}

void printSolution(Solution* sol) {
    std::cout << "Value of the solution = " << sol->solValue() << " and " << sol->solWeight() << "used\n";
    std::cout << "Items in the solutions :(profit, weight ,key)\n";
    int max = sol->listOfItems().size();
    for (int i = 0; i < max; i++) {
        std::cout << "item " << i << " (" << sol->listOfItems().front()->profit() << ", " << sol->listOfItems().front()->weight() << ", " << sol->listOfItems().front()->key() << ")\n";
        sol->listOfItems().pop_front();
    }
}

void writeSolution(std::string I, Solution* sol, MyClock clock, std::string fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (file) {
        file << I << "&&" << clock.elapsedTime() << "&&" << sol->solValue() << "&&" << sol->solWeight() << "\n";
        int max = sol->listOfItems().size();
        for (int i = 0; i < max; i++) {
            file << "&&" << "(" << sol->listOfItems().front()->profit() << "," << sol->listOfItems().front()->weight() << "," << sol->listOfItems().front()->key() << ")";
            sol->listOfItems().pop_front();
        }
        file << "\n";
        file.close();
    } else
        std::cerr << "Error while opening the file!!\n";
}

void writeDynSolution(std::string I, int value, int weight, MyClock clock, std::string fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (file) {
        file << I << "&&" << clock.elapsedTime() << "&&" << value << "&&" << weight << "\n";
        file.close();
    } else
        std::cerr << "Error while opening the file!!\n";
}

void writeInstance(InstanceGen* I, std::string Ins, std::string fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (file) {
        file << Ins << "&&";
        for (std::vector<Item*>::iterator i = I->itemsVector().begin(); i != I->itemsVector().end(); i++) {
            file << "(" <<((*i)->profit())<<", "<<((*i)->weight())<<","<<((*i)->key())<<")"<<"&&";
        }
        file<<"\n";
        file.close();
    } else
        std::cerr << "Error while opening the file!!\n";
}

int main(int argc, char const *argv[]) {
    InstanceGen* instance = new InstanceGen(atof(argv[1]),atoi(argv[2]), 0.0);
    std::ostringstream s;
    s << "(" << atof(argv[1]) << ", " << atoi(argv[2]) <<","<<0.0 << ")";
    std::string i = s.str();
    writeInstance(instance, i, "instance.csv");
    printInstance(instance);

    KNPsolver* KNPsol = new KNPsolver();
    Solution* sol = new Solution();
    MyClock greedyC;
    greedyC.start();
    KNPsol->greedySolver(instance, sol);
    greedyC.end();
    printSolution(sol);
    writeSolution(i, sol,greedyC,"greedyResults.csv");

    INC = sol->solValue();

    Solution* LPsol = new Solution();
    MyClock LPC;
    LPC.start();
    KNPsol->LPsolver(instance, LPsol, 0, 0.0);
    LPC.end();
    printSolution(LPsol);
    writeSolution(i, LPsol,LPC, "LPResults.csv");

    Solution* BABsolution = new Solution();
    MyClock BABC;
    BABC.start();
    KNPsol->BABsolver(instance, BABsolution);
    BABC.end();
    printSolution(BABsolution);
    writeSolution(i, BABsolution, BABC,"BABResults.csv");


            int dynResult;
    int wUsed = 0;
    MyClock DynC;
    DynC.start();
    dynResult = KNPsol->Dynamic(instance);
    DynC.end();
    std::cout << "DYNAMIC value = " << dynResult << "\n";
    for (int i = 0; i < instance->numOfItems(); i++) {
        if (instance->profitOnWeightVector().at(i)->isInSolution()) {
            wUsed += (int) instance->profitOnWeightVector().at(i)->weight();
            std::cout << "item " << i << " (" << instance->profitOnWeightVector().at(i)->profit() << ", " << instance->profitOnWeightVector().at(i)->weight() << ", " << instance->profitOnWeightVector().at(i)->key() << ")\n";
        }
    }
    std::cout << "DYN Weight = " << wUsed << "\n";
    writeDynSolution(i, dynResult, wUsed, DynC, "DynResults.csv");

    return 0;
}


