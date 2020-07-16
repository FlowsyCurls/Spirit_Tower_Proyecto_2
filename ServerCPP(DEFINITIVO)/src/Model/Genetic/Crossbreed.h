#ifndef SERVER_CROSSBREED_H
#define SERVER_CROSSBREED_H


#include "Spectrum.h"

#include <random>

class Crossbreed {

private:
    vector<Spectrum*>* newListOfSpectrums = new vector<Spectrum*>;
    const int mutationProbability = 8;
    const int inversionProbability = 2;
    const int numOfGenesReversed = 2;

public:

    static int generationMarker;


    vector<Spectrum *> *getNextGenOfSpectrums(vector<Spectrum *> *pListOfSpectrums);
    void matchEachSpectrum(vector<Spectrum *> *pListOfSpectrums) const;
    void matchBrotherhood(Spectrum *pParent1, Spectrum *pParent2) const;

    static string decToBinSpectrum(Spectrum *pSpectrum);
    static Spectrum *binToDecString(const string& pAdnChain);
    static int verifyBin(int pBin);

    string Cross(const string& pGen1, const string& pGen2) const;
    string CrossProbability(string& pAdn) const;

    static string Mutation(string &pAdn);
    string Inversion(string &pAdn) const;
    static string replace(int &pPos, int pLen, string &pStr);


};



#endif //SERVER_CROSSBREED_H
