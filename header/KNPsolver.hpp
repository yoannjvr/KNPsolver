/* 
 * File:   KNPsolver.hpp
 * Author: yoannjvr
 *
 * Created on 18 octobre 2015, 22:45
 */

#ifndef KNPSOLVER_HPP
#define	KNPSOLVER_HPP

#include <iostream>     
#include <algorithm> 
#include "InstanceGen.hpp"
#include "GlobalVar.hpp"
#include "Solution.hpp"

class KNPsolver {
public:
    KNPsolver();
    ~KNPsolver();

    void BABsolver(InstanceGen* I, Solution* sol);
    void greedySolver(InstanceGen* , Solution* );
    double LPsolver(InstanceGen* I, Solution* sol, int index, double currentW);
    void Flow();
    int Dynamic(InstanceGen* I);

private:
};


#endif	/* KNPSOLVER_HPP */

