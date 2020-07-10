#ifndef SERVER_CROSSBREED_H
#define SERVER_CROSSBREED_H


#include "Spectrum.h"

#include <random>

class Crossbreed {

private:
    vector<Spectrum*>* newSpectrumGroup = new vector<Spectrum*>;
//    LinkedList<string>* newPopulationGens;
    const int mutationProbability = 4;
    const int inversionProbability = 2;
    const int numOfGenesReversed = 4;
    int groupNumber = 2;

public:

    /**
     * Retorna la nueva generacion generada a partir del parametro de entrada.
     * @param pSpectreGroup
     *
     * @return
     */
    vector<Spectrum *> *getNewGroup(vector<Spectrum *> *pSpectreGroup);

    void matchEachSibling(Spectrum *pParent1, Spectrum *pParent2);

    static string decToBinSpectrum(Spectrum *pSpectrum);

    static Spectrum *binToDecString(const string& pAdnChain);

    string Cross(const string& pGen1, const string& pGen2) const;

    string CrossProbability(string& pAdn) const;

    static string Mutation(string &pAdn);

    string Inversion(string &pAdn) const;

    static string replace(int &pPos, int pLen, string &pStr);

    void printGroup();

    static int verifyBin(int pBin);

    vector<struct Spectrum *> * matchEachSpectrum(vector<Spectrum *> *pSpectreGroup);

    Spectrum * chooseBestSibling(vector<Spectrum *> *pDescendantSiblings);

    Spectrum *chooseBestDescendant(vector<Spectrum *> *pDescendantSiblings);
};



#endif //SERVER_CROSSBREED_H
