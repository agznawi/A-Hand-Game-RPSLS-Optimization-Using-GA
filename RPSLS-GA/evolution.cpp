#include "evolution.h"
#include "globals.h"

#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::uniform_int_distribution;
using std::uniform_real_distribution;
#include <array>
using std::array;


string Evolution::x[5] = {"rock", "paper", "scissors", "lizard", "spock"};

Individual Evolution::crossover(Individual indiv1, Individual indiv2)
{
    uniform_int_distribution<int> rCut(1, 10);

    array<Hand, Individual::nGens> genome;
    for(int i = 0; i < Individual::nGens; i++)
    {
        int swap = rCut(rmt) ; // Select random crossover point
        genome.at(i) = (swap <= 6)? indiv1.genome.at(i) :
                                    indiv2.genome.at(i);
    }

    return genome;
}


void Evolution::mutate(Individual &indiv)
{
    uniform_int_distribution<int> rGene(0, Individual::nGens-1);
    uniform_int_distribution<int> rValue(rock, spock);
    int gene = rGene(rmt); // Select random location
    Hand value = static_cast<Hand>(rValue(rmt));

    indiv.genome.at(gene) = value;

}


void Evolution::calculatePopulationScore(Population &pop)
{
    static int numOfMatches = 99999;
    int popCnt = pop.getPopulationCount();

    // loop over all population
    for(int i = 0; i < popCnt; i++)
    {
        Individual &indiv1 = pop.getIndividual(i);
        double worstScore = (unsigned)~0;
        indiv1.fitness = 0.0;
        float score;

        //** AGAINST EACH OTHER **//
//        score = 0.0;
//        static int numOfOpponents = pop.getPopulationCount()/4-1;
//        uniform_int_distribution<int> rOpponent(0, numOfOpponents);
//        for(int opp = 0; opp < popCnt; opp++)
//        {
//            Individual &indiv2 = pop.getIndividual(rOpponent(rmt));
////            Individual &indiv2 = pop.getIndividual(opp);
//            for(int matches = 0; matches < numOfMatches; matches++)
//            {
//                Hand h1 = indiv1.playHand();
//                Hand h2 = indiv2.playHand();
//                int result = getMatchResult(h1, h2);
//                if(result >= tie)
//                    score += result;
//            }
//            if(worstScore > score)
//                worstScore = score;
//        }

//        //** AGAINST RANDOM **//
//        score = 0.0;
//        for(int randOpp = 0; randOpp < 100; randOpp++)
//        {
//            Individual randIndiv;
//            for(int matches = 0; matches < numOfMatches; matches++)
//            {
//                Hand h1 = indiv1.playHand();
//                Hand h2 = randIndiv.playHand();
//                int result = getMatchResult(h1, h2);
//                if(result >= tie)
//                    score += result;
//            }
//            if(worstScore > score)
//                worstScore = score;
//        }

        //** AGAINST ROCK **//
        score = 0.0;
        for(int matches = 0; matches < numOfMatches; matches++)
        {
            Hand h1 = indiv1.playHand();
            int result = getMatchResult(h1, rock);
            if(result >= tie)
                score += result;
        }
        if(worstScore > score)
            worstScore = score;

        //** AGAINST PAPER **//
        score = 0.0;
        for(int matches = 0; matches < numOfMatches; matches++)
        {
            Hand h1 = indiv1.playHand();
            int result = getMatchResult(h1, paper);
            if(result >= tie)
                score += result;
        }
        if(worstScore > score)
            worstScore = score;

        //** AGAINST SCISSORS **//
        score = 0.0;
        for(int matches = 0; matches < numOfMatches; matches++)
        {
            Hand h1 = indiv1.playHand();
            int result = getMatchResult(h1, scissors);
            if(result >= tie)
                score += result;
        }
        if(worstScore > score)
            worstScore = score;

        //** AGAINST LIZARD **//
        score = 0.0;
        for(int matches = 0; matches < numOfMatches; matches++)
        {
            Hand h1 = indiv1.playHand();
            int result = getMatchResult(h1, lizard);
            if(result >= tie)
                score += result;
        }
        if(worstScore > score)
            worstScore = score;

        //** AGAINST SPOCK **//
        score = 0.0;
        for(int matches = 0; matches < numOfMatches; matches++)
        {
            Hand h1 = indiv1.playHand();
            int result = getMatchResult(h1, spock);
            if(result >= tie)
                score += result;
        }
        if(worstScore > score)
            worstScore = score;

//        indiv1.score /= numOfMatches;
          indiv1.fitness = worstScore/numOfMatches + 0.001;
    }
}

int Evolution::selectIndividual(Population pop)
{
    double sum = pop.getFitnessSum();
    uniform_real_distribution<double> randSelector(0, sum);
    double selector = randSelector(rmt);

    int index = 0;
    while(selector >= 0.0)
        selector -= pop.getIndividual(index++).fitness;
    return abs(index-1);
}


int Evolution::getMatchResult(int hand1, int hand2)
{
    static const int scores[5][5] =
                //    Rock       Paper       Scissors       Lizard        Spock
    { /*Rock    */ {tie      , -paperWin  , rockWin     , rockWin     , -spockWin} ,
      /*Paper   */ {paperWin , tie        , -scissorWin , -lizardWin  ,  paperWin} ,
      /*Scissors*/ {-rockWin , scissorWin , tie         , scissorWin  , -spockWin} ,
      /*Lizard  */ {-rockWin , lizardWin  , -scissorWin , tie         , lizardWin} ,
      /*Spock   */ {spockWin , -paperWin  , spockWin    , -lizardWin  , tie      } };
    return scores[hand1][hand2];
}
