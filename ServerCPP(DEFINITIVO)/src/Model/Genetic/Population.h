//
// Created by Jeykime on 7/20/2020.
//

#ifndef SERVER_POPULATION_H
#define SERVER_POPULATION_H


#include "Spectrum.h"
#include "Tools/Utility.h"

class Population {
private:
    //ATTRIBUTES
    const static int capacity = 10;
    const static int maxRandom = 2;
    const static int minRandom = 0;
    const static int mutationProbability = 5;
    const static int inversionProbability = 3;
    const static int numOfGenesReversed = 3;
    static int totalSpectres;
    static int populationCounter;

    //METHODS
    vector<Spectrum*>* listOfSpectres = new  vector<Spectrum*>;
    vector<Spectrum*>* breedList = new  vector<Spectrum*>;
    Spectrum* finest;

    static int getRandom();
    static string generateId();

    void getBreed_Cross(Spectrum *pSp1, Spectrum *pSp2);
    static Spectrum * getFinest(vector<Spectrum*> *pList);

    static string Cross(const string &pGen1, const string &pGen2) ;
    static string CrossProbability(string &pAdn);

    static string decToBinSpectrum(Spectrum *pSpectrum);
    static Spectrum *binToDecString(const string &pAdnChain);

    static string replace(int &pPos, int pLen, string &pStr);
    static string Mutation(string &pAdn);
    static string Inversion(string &pAdn);


public:
    //CONSTRUCTOR
    Population();

    //METHODS
    void generatePopulation();
    Spectrum *getBreed();
    Spectrum *getFinest();
};


#endif //SERVER_POPULATION_H
