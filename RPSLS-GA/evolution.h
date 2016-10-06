#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "globals.h"
#include "individual.h"
#include "population.h"

#include <string>
using std::string;

class Evolution
{
public:
    static string x[5];
    static Individual crossover(Individual indiv1, Individual indiv2);
    static void mutate(Individual &indiv);
    static void calculatePopulationScore(Population &pop);
    static void calculateFitness(Population &pop);
    static int selectIndividual(Population pop);

    static int getMatchResult(int hand1, int hand2);
};

#endif // EVOLUTION_H
