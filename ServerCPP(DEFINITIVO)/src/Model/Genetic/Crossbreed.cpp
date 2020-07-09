#include "Crossbreed.h"
#include "Tools/Utility.h"
#include "GeneticManager.h"

vector<Spectrum *> *Crossbreed::getNewGroup(vector<Spectrum *> *pSpectreGroup)
{
    cout << "___________________________________________________" <<endl;
    cout << "[CROSS"<<groupNumber++<<"-START]";
    newSpectrumGroup =  new vector<Spectrum*>;
    return matchEachSpectrum(pSpectreGroup);
}

vector<Spectrum *>* Crossbreed::matchEachSpectrum(vector<Spectrum *> *pSpectreGroup)
{
    // Cross between each parent.
    for (int i = 0; i < pSpectreGroup->size(); i++){
        Spectrum *first, *second;
        if (i == pSpectreGroup->size() - 1){
            first = pSpectreGroup->at(i);
            second = pSpectreGroup->at(0);
        }
        else{
            first = pSpectreGroup->at(i);
            second = pSpectreGroup->at(i + 1);
        }
        matchEachSibling(first, second);
    }
    printGroup();
    cout << "[CROSS-END]  " <<endl;
    return newSpectrumGroup;
}

void Crossbreed::matchEachSibling(Spectrum *pParent1, Spectrum *pParent2)
{
    auto *siblings1 = pParent1->getSiblingsList();
    auto *siblings2 = pParent2->getSiblingsList();

    auto *descendantSiblings = new vector<Spectrum *>;
    for (int i = 0; i < siblings1->size(); i++) {
        string genes1, genes2;
        Spectrum *descendant1, *descendant2;
        // Descendant 1 Process
        genes1 = Cross(decToBinSpectrum(siblings1->at(i)), decToBinSpectrum(siblings2->at(i)));
        descendant1 = binToDecString(genes1);
        descendantSiblings->push_back(descendant1);
        // Descendant 2 Process
        genes2 = Cross(decToBinSpectrum(siblings2->at(i)), decToBinSpectrum(siblings1->at(i)));
        descendant2 = binToDecString(genes2);
        descendantSiblings->push_back(descendant2);
    }
    newSpectrumGroup->push_back(chooseBestSibling(descendantSiblings));
}

Spectrum* Crossbreed::chooseBestSibling(vector<Spectrum *> *pDescendantSiblings) {
    Spectrum *best = pDescendantSiblings->at(0);
    for (auto & descendant : *pDescendantSiblings)
    {
        double sum1 = best->sum();
        double sum2 = descendant->sum();
        if (sum1 < sum2) best = descendant;
    }
    cout << "\n    * BestOne : "; best->toString();
    best->setSiblingsList(pDescendantSiblings);
    return best;
}

string Crossbreed::decToBinSpectrum(Spectrum *pSpectrum)
{
    string adn = '0' +
                 Utility::decToBinary(pSpectrum->getRouteSpeed()) +
                 Utility::decToBinary(pSpectrum->getChaseSpeed()) +
                 Utility::decToBinary(pSpectrum->getSightRange());
//    cout << "\t[DecToBin] - "<< pSpectrum->getId() <<"  " << adn << endl;
    return adn;
}

Spectrum *Crossbreed::binToDecString(const string& pAdnChain)
{
    auto *childSpectrum = new Spectrum(GeneticManager::generateId());
    childSpectrum->setRouteSpeed(verifyBin(stoi(pAdnChain.substr(1, 3))));
    childSpectrum->setChaseSpeed(verifyBin(stoi(pAdnChain.substr(4, 3))));
    childSpectrum->setSightRange(verifyBin(stoi(pAdnChain.substr(7, 3))));
//    cout << "\n\t\t  Child: "; childSpectrum->toString();
    return childSpectrum;
}
int Crossbreed::verifyBin(int pBin)
{
    int dec = Utility::binToDec(pBin);
    if (dec == 0) return 1;
    if (dec > 9) return 9;
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

void Crossbreed::printGroup()
{
    cout << "\n * Population :"<<endl << "\t[";
    for (auto & newPopulationSpectrum : *newSpectrumGroup)
    {
        cout<<"  "<<newPopulationSpectrum->getId();
    }
    cout << "  ]"<<endl;
}




