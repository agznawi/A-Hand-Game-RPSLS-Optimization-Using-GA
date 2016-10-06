#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "globals.h"

#include <random>
using std::uniform_int_distribution;
#include <array>
using std::array;

class Individual
{
public:
    static const int nGens = 100000;
    array<Hand, nGens> genome;
    float ro, pa, sc, li, sp;
    double fitness;
    int percentages[5] = {0};

    void genomeToPercent();
    Hand playHand();

public:
    Individual();
    Individual(array<Hand, nGens> genome);
};

#endif // INDIVIDUAL_H
