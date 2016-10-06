#include "globals.h"
#include "individual.h"
#include "population.h"
#include "evolution.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <array>

using namespace std;

random_device r;
mt19937 rmt(r());

void printGenerationInfo(Population pop, int count, int generation, double bestFitness);
void saveBestIndividuals(ofstream &fout, Individual bestIndiv, int generation, double bestFitness);
bool ELITISM = true;
int elite = 1;
const int POP_SIZE = 5; // Population size
int disp = 5;


int main()
{
    Population pop(POP_SIZE);
    Evolution::calculatePopulationScore(pop);
//    Evolution::calculateFitness(pop);

    ofstream fout("output.txt");
    fout << "Generation | Best ever | Fitness | "
         << "rock  | paper | sciss | lizar | spock\n" << flush;

    pop.sortByFitness(); // Only for displaying purpose
    float bestFitness = pop.getIndividual(0).fitness;
    Individual bestIndiv = pop.getIndividual(0);
    bestIndiv.genomeToPercent();
    printGenerationInfo(pop, disp, 0, bestFitness);
    saveBestIndividuals(fout, bestIndiv, 0, bestFitness);
//    getchar();

    for(int generation = 1;; generation++)
    {
        vector<Individual> newPopulation;

        if(ELITISM)
            for(int i = 0; i < elite; i++)
                newPopulation.push_back(pop.individuals.at(i));

        for(int i = elite; i < POP_SIZE; i++)
        {
            // Select
            int parent1 = Evolution::selectIndividual(pop);
            int parent2 = Evolution::selectIndividual(pop);

            // Crossover
            Individual newIndiv =
                    Evolution::crossover(pop.getIndividual(parent1),
                                         pop.getIndividual(parent2));

            // Mutate
            uniform_int_distribution<int> r(1, 100);
            if(r(rmt) <= 10)
                Evolution::mutate(newIndiv);

            newPopulation.push_back(newIndiv);
        }
        pop.individuals = newPopulation;

        Evolution::calculatePopulationScore(pop);
//        Evolution::calculateFitness(pop);

        // Print and save generation result
        system("clear");
        pop.sortByFitness();
        pop.getIndividual(0).genomeToPercent();
        bestIndiv.genomeToPercent();
        if(bestIndiv.ro != pop.getIndividual(0).ro || // something is wrong
           bestIndiv.pa != pop.getIndividual(0).pa || // check if bestIndiv changes
           bestIndiv.sc != pop.getIndividual(0).sc ||
           bestIndiv.li != pop.getIndividual(0).li ||
           bestIndiv.sp != pop.getIndividual(0).sp)
        {
            bestIndiv = pop.getIndividual(0);
            saveBestIndividuals(fout, bestIndiv, generation, bestFitness);
        }

        if(bestIndiv.fitness > bestFitness) // probabily pop.getIndividual(0).fitness is better
            bestFitness = bestIndiv.fitness;
        printGenerationInfo(pop, disp, generation, bestFitness);
//        getchar();
    }
}

void printGenerationInfo(Population pop, int count, int generation, double bestFitness)
{
    int popSize = pop.getPopulationCount();
    float avg = 0;
    for(int i = 0; i < popSize; i++)
        avg += pop.getIndividual(i).fitness;
    avg /= popSize;

    cout << "Generation = " << generation
         << setprecision(5) << fixed
         << ", best fitness so far = " << bestFitness << endl
         << "Best fit = " << pop.getIndividual(0).fitness <<
            " | Worst fit = " << pop.getIndividual(popSize-1).fitness <<
            " | Avg fit = " << avg << endl
         << "                                "
//         << "rock  | paper | sciss | lizar | spock\n";
         << "rock    | paper   | scissor | lizard  | spock\n";

    for(int i = 0; i < count; i++)
    {
        if(i == elite)
            cout << endl;
        Individual &indiv = pop.getIndividual(i); // a COPY of individual
        indiv.genomeToPercent();
        cout << "Indiv" << left << setw(2) << i << " fitness = "
             << setw(8) << setprecision(5) << fixed
             << indiv.fitness << " for: "
             << setprecision(3) << fixed
             << setw(6) << indiv.ro << "% | "
             << setw(6) << indiv.pa << "% | "
             << setw(6) << indiv.sc << "% | "
             << setw(6) << indiv.li << "% | "
             << setw(6) << indiv.sp << "%\n";
    }
}

void saveBestIndividuals(ofstream &fout, Individual bestIndiv, int generation, double bestFitness)
{
    bestIndiv.genomeToPercent();
    fout << left << setw(10) << generation << " | "
         << setw(9) << setprecision(5) << bestFitness << " | "
         << setw(7) << setprecision(5) << fixed
         << bestIndiv.fitness << " | "
         << setw(4) << setprecision(3) << fixed
         << bestIndiv.ro << "% | "
         << setw(4) << bestIndiv.pa << "% | "
         << setw(4) << bestIndiv.sc << "% | "
         << setw(4) << bestIndiv.li << "% | "
         << setw(4) << bestIndiv.sp << "%\n"
         << flush;
}

