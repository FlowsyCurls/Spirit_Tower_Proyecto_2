//
// Created by Jeykime on 7/20/2020.
//

#include "Population.h"

int Population::totalSpectres = 1;
int Population::populationCounter = 1;

Population::Population() = default;


int Population::getRandom() {
    return Utility::Random(minRandom, maxRandom);
}


void Population::generatePopulation() {
//    cout << "> Population : "<< populationCounter++ << endl;
    for (int k = 0; k < capacity; k++)
    {
        // Push Spectrum with random attributes.
         auto *spectrum = new Spectrum(generateId(), getRandom(), getRandom(), getRandom());
         listOfSpectres->push_back(spectrum);
//         spectrum->toString();
    }
//    cout << endl;
}


Spectrum *Population::getBreed() {
    breedList = new vector<Spectrum*>;
    // Cross between each spectrum.
    for (int i = 0; i < listOfSpectres->size(); i++){
        Spectrum *first, *second;
        if (i == listOfSpectres->size() - 1)
        {
            first = listOfSpectres->at(i);
            second = listOfSpectres->at(0);
        }
        else
        {
            first = listOfSpectres->at(i);
            second = listOfSpectres->at(i + 1);
        }
        getBreed_Cross(first, second);
    }
    listOfSpectres = breedList;
    return finest;
}


void Population::getBreed_Cross(Spectrum *pSp1, Spectrum *pSp2)
{
    auto* twinsList = new  vector<Spectrum*>; //tmp list to compare

    string firstTwin = Cross(decToBinSpectrum(pSp1), decToBinSpectrum(pSp2));  // Creation 1 Process
    string secondTwin = Cross(decToBinSpectrum(pSp2), decToBinSpectrum(pSp1));  // Creation 2 Process

    twinsList->push_back(binToDecString(firstTwin));
    twinsList->push_back(binToDecString(secondTwin));

    breedList->push_back(getFinest(twinsList));
//    breedList->back()->toString();
}


/**
* Choose best spectrum of the sample and return it.
* @param pList
* @return
*/
Spectrum * Population::getFinest()
{
    return getFinest(listOfSpectres);
}


Spectrum * Population::getFinest(vector<Spectrum*> *pList) {
    Spectrum *goat = pList->at(0); // El mejor empieza siendo el primero.
//    goat->toString();
    for (int h = 1; h < pList->size(); h++) {
//        pList->at(h)->toString();
        if (goat->compareStats(pList->at(h))) { // Compare each stats.
            goat = pList->at(h);
//            for (auto &g : *pList){
//                if (goat->compareVision(g)) { // Compare sight Range.
//                    goat = g;
//                }
//            }
        }
    }
    return goat;
}






string Population::generateId() {
    string id = "spectrum_" + to_string(totalSpectres++);
    return id;
}



string Population::decToBinSpectrum(Spectrum *pSpectrum)
{
    string adn = Utility::decToBinary((int) pSpectrum->getRouteSpeed()) +
                 Utility::decToBinary((int) pSpectrum->getChaseSpeed()) +
                 Utility::decToBinary(pSpectrum->getSightRange());
//    cout << "  [DecToBin] - "<< pSpectrum->getId() <<"  " << adn << endl;
    return adn;
}


Spectrum *Population::binToDecString(const string& pAdnChain)
{
    auto *sonSpectrum = new Spectrum(generateId());
    sonSpectrum->setRouteSpeed(Utility::binToDec(stoi(pAdnChain.substr(0, 3))));
    sonSpectrum->setChaseSpeed(Utility::binToDec(stoi(pAdnChain.substr(3, 3))));
    sonSpectrum->setSightRange(Utility::binToDec(stoi(pAdnChain.substr(6, 3))));
//    cout << "  [BinToDec] - "; sonSpectrum->toString();
    return sonSpectrum;
}


string Population::Cross(const string& pGen1, const string& pGen2)
{
    string adn = pGen1.substr(0, 5) + pGen2.substr (5);
    adn = CrossProbability(adn);
    return adn;
}


string Population::CrossProbability(string& pAdn)
{
    int gen;
// Probability for Mutation : 8%
    gen = Utility::Random(100);
    if (mutationProbability >= gen)
    {
//        cout<<" * M : YES\n";
        pAdn = Mutation(pAdn);
    }
// Probability for Inversion : 4%
    gen =  Utility::Random(100);
    if (inversionProbability >= gen)
    {
//        cout<<" * I : YES\n";
        pAdn = Inversion(pAdn);
    }
    return pAdn;
}


string Population::Mutation(string &pAdn)
{
    int gen = Utility::Random(7); // get a random number from 0 to 7.
    pAdn = replace(gen, 1, pAdn);
//    cout << gen << " " << pAdn << endl;
    return pAdn;
}


string Population::Inversion(string &pAdn) {
    int gen = Utility::Random(7);
    pAdn = replace(gen, numOfGenesReversed, pAdn);
//    cout << gen << " "<< pAdn << endl;
    return pAdn;
}


string Population::replace(int &pPos, int pLen, string &pStr)
{
    string temp, after;
    for (int i=0; i<pStr.size(); i++)
    {
        if (i < pPos || i > (pPos + pLen - 1))
        {
            temp += (pStr[i]);
        }
        else {
            if (pStr[i] == '0'){
                temp += ('1');
            }
            else
            {
                temp += ('0');
            }
        }
    }
    return temp;
}


