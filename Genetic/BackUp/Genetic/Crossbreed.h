#ifndef BACKUP_CROSSBREED_H
#define BACKUP_CROSSBREED_H

#include "Spectrum.h"

#include <ctgmath>
#include <random>

class Crossbreed {

private:
    LinkedList<Spectrum*>* newPopulationSpectrums;
//    LinkedList<string>* newPopulationGens;
    const int mutationProbability = 8;
    const int inversionProbability = 4;
    const int numOfGenesReversed = 4;
    int genNumber = 1;

public:

    /**
     * Retorna la nueva generacion generada a partir del parametro de entrada.
     * @param pSelectedList
     *
     * @return
     */
    LinkedList<Spectrum *> *getNewGeneration(LinkedList<Spectrum *> *pSelectedList);

    void setNewPopulation(Spectrum *pParent1, Spectrum *pParent2);

    static string decToBinSpectrum(Spectrum *pSpectrum);

    static Spectrum *binToDecString(const string& pAdnChain);

    string Cross(const string& pGen1, const string& pGen2) const;

    string CrossProbability(string& pAdn) const;

    static string Mutation(string &pAdn);

    string Inversion(string &pAdn) const;

    static string replace(int &pPos, int pLen, string &pStr);

    static Spectrum *Fitness(Spectrum *pCandidate1, Spectrum *pCandidate2);

    void printPopulation();

    static int verifyBin(int pBin);
};


#endif //BACKUP_CROSSBREED_H
