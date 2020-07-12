#include "Crossbreed.h"
#include "Tools/Utility.h"
#include "GeneticManager.h"

int Crossbreed::generationMarker = 0;
/**
 * Retorna la nueva generacion generada a partir del parametro de entrada.
 * @param pListOfSpectrums
 *
 * @return
 */
vector<Spectrum *> *Crossbreed::getNextGenOfSpectrums(vector<Spectrum *> *pListOfSpectrums)
{
//    cout << "============> [CROSS" << generationMarker++ << "-START] <============\n";
    newListOfSpectrums =  new vector<Spectrum*>; //Release the spaces from the list, in case another generation has been generated before.
    matchEachSpectrum(pListOfSpectrums);
    return newListOfSpectrums;
}

void Crossbreed::matchEachSpectrum(vector<Spectrum *> *pListOfSpectrums) const {
    // Cross between each parent.
    for (int i = 0; i < pListOfSpectrums->size(); i++){
        Spectrum *first, *second;
        if (i == pListOfSpectrums->size() - 1)
        {
            first = pListOfSpectrums->at(i);
            second = pListOfSpectrums->at(0);
        }
        else
        {
            first = pListOfSpectrums->at(i);
            second = pListOfSpectrums->at(i + 1);
        }
        matchBrotherhood(first, second);
    }
//    cout << "============> [CROSS-END] <============" <<endl;
    cout << "~~~~~~~~~~~~~~> \' GEN " << generationMarker++ << " \' <~~~~~~~~~~~~~~"<< endl;
}

void Crossbreed::matchBrotherhood(Spectrum *pParent1, Spectrum *pParent2) const
{
    auto *brotherhood1 = pParent1->getBrotherhoodList();
    auto *brotherhood2 = pParent2->getBrotherhoodList();

    auto *bothCreations = new vector<Spectrum *>;
    auto* bestCreations = new vector<Spectrum *>;

    for (int i = 0; i < GeneticManager::totalSample; i++) {
        string firstCreation, secondCreation;
        Spectrum *firstGenes, *secondGenes;

        // firstCreation 1 Process
        firstCreation = Cross(decToBinSpectrum(brotherhood1->at(i)), decToBinSpectrum(brotherhood2->at(i)));
        firstGenes = binToDecString(firstCreation);
        bothCreations->push_back(firstGenes);
        // secondCreation 2 Process
        secondCreation = Cross(decToBinSpectrum(brotherhood2->at(i)), decToBinSpectrum(brotherhood1->at(i)));
        secondGenes = binToDecString(secondCreation);
        bothCreations->push_back(secondGenes);
        bestCreations->push_back(GeneticManager::chooseBestSpectrum(bothCreations));
    }
//    cout << " BEST LS " << bestCreations->size();
    newListOfSpectrums->push_back(GeneticManager::chooseBestSpectrum(bestCreations));
}

string Crossbreed::decToBinSpectrum(Spectrum *pSpectrum)
{
    string adn = '0' +
                 Utility::decToBinary((int) pSpectrum->getRouteSpeed()) +
                 Utility::decToBinary((int) pSpectrum->getChaseSpeed()) +
                 Utility::decToBinary(pSpectrum->getSightRange());
//    cout << "\t[DecToBin] - "<< pSpectrum->getId() <<"  " << adn << endl;
    return adn;
}

Spectrum *Crossbreed::binToDecString(const string& pAdnChain)
{
    auto *sonSpectrum = new Spectrum(GeneticManager::generateId());
    sonSpectrum->setRouteSpeed(verifyBin(stoi(pAdnChain.substr(1, 3))));
    sonSpectrum->setChaseSpeed(verifyBin(stoi(pAdnChain.substr(4, 3))));
    sonSpectrum->setSightRange(verifyBin(stoi(pAdnChain.substr(7, 3))));
//    cout << "\n\tBestSon: "; sonSpectrum->toString();
    return sonSpectrum;
}
int Crossbreed::verifyBin(int pBin)
{
    int dec = Utility::binToDec(pBin);
    if (dec == 0) return GeneticManager::minRandom;
    if (dec > GeneticManager::maxRandom) return GeneticManager::maxRandom;
    return dec;
}
string Crossbreed::Cross(const string& pGen1, const string& pGen2) const
{
    string adn = pGen1.substr(0, 5) + pGen2.substr (5);
    adn = CrossProbability(adn);
    return adn;
}

string Crossbreed::CrossProbability(string& pAdn) const
{
    int gen;
// Probability for Mutation : 8%
    gen = Utility::Random(100);
    if (mutationProbability >= gen)
    {
//        cout<< "\n\t * M % "<<gen;

        pAdn = Mutation(pAdn);
    }
// Probability for Inversion : 4%
    gen =  Utility::Random(100);
    if (inversionProbability >= gen)
    {
//        cout<< "\n\t * I % "<<gen;
        pAdn = Inversion(pAdn);
    }
    return pAdn;
}

string Crossbreed::Mutation(string &pAdn)
{
    int gen = Utility::Random(9);
    pAdn = replace(gen, 1, pAdn);
//    cout << "\t\t   [Mutation]  "<< gen << " " << pAdn << endl;
    return pAdn;
}

string Crossbreed::Inversion(string &pAdn) const {
    int gen = Utility::Random(6);
    pAdn = replace(gen, numOfGenesReversed, pAdn);
//    cout << "\t\t   [Inversion] "<< gen << " "<< pAdn << endl;
    return pAdn;
}

string Crossbreed::replace(int &pPos, int pLen, string &pStr)
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



