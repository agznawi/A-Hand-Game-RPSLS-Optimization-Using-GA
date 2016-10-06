#include "individual.h"
#include "globals.h"

#include <random>
using std::uniform_int_distribution;
using std::discrete_distribution;
#include <algorithm>
using std::random_shuffle;


Individual::Individual()
{
    uniform_int_distribution<int> rHandProp(0, 40);
    int roP = rHandProp(rmt);
    int paP = rHandProp(rmt);
    int scP = rHandProp(rmt);
    int liP = rHandProp(rmt);
    int spP = rHandProp(rmt);
    discrete_distribution<int> disc({roP, paP, scP, liP, spP});
//    discrete_distribution<int> disc({100, 100, 100, 100, 100});

    for(unsigned int i = 0; i < nGens; i++)
        genome.at(i) = static_cast<Hand>(disc(rmt));
}


Individual::Individual(array<Hand, nGens> genome)
{
    this->genome = genome;
}


void Individual::genomeToPercent()
{
    static const float div = nGens / 100.0;
    for(int i = 0; i < 5; i++)
        percentages[i] = 0;
    for(unsigned int i = 0; i < nGens; i++)
        percentages[genome.at(i)]++;

    ro = percentages[rock]/div;
    pa = percentages[paper]/div;
    sc = percentages[scissors]/div;
    li = percentages[lizard]/div;
    sp = percentages[spock]/div;
}


Hand Individual::playHand()
{
    static int index = 0;
    if(index >= nGens)
    {
        index = 0;
        random_shuffle(genome.begin(), genome.end());
    }
    return genome[index++];
}
