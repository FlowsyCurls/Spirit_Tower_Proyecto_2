#include "Crossbreed.h"
#include "../Tools/Utility.h"
#include "GeneticManager.h"

LinkedList<Spectrum *> *Crossbreed::getNewGeneration(LinkedList<Spectrum *> *pSelectedList)
{
    for (int i = 0; i<pSelectedList->size(); i++)
    {
        Spectrum *first, *second;
        if (i == pSelectedList->size()-1)
        {
            first = pSelectedList->at(i);
            second = pSelectedList->at(0);
        }
        else{
            first = pSelectedList->at(i);
            second = pSelectedList->at(i+1);
        }
        setNewPopulation(first, second);
    }
    printPopulation();
    return newPopulationSpectrums;
}

void Crossbreed::setNewPopulation(Spectrum *pParent1, Spectrum *pParent2)
{
    string adn1, adn2;
    Spectrum *child1, *child2, *fitness;

// Printing Parents
    cout << endl << "[Cross-Start]" <<endl<<endl;
    cout << "   Parent1 : "; pParent1->toString();
    cout << "   Parent2 : "; pParent2->toString();
    cout << endl;

// Printing Child1 Process
    cout << "\t\tBreeding Child1 ...";
    adn1 = Cross(decToBinSpectrum(pParent1), decToBinSpectrum(pParent2));
    child1 = binToDecString(adn1);
    cout << endl;

// Printing Child2 Process
    cout << "\t\tBreeding Child2 ...";
    adn2 = Cross(decToBinSpectrum(pParent2), decToBinSpectrum(pParent1));
    child2 = binToDecString(adn2);
    cout << endl;

// Choosing the best of the two children
    fitness = Fitness(child1, child2);
    newPopulationSpectrums->add(fitness);
    cout <<endl<< "[Cross-End]  "<< endl <<endl<<endl;
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
    string id = "SP-" + to_string(GeneticManager::getSpectrumCounter());
    auto *childSpectrum = new Spectrum(id);
    childSpectrum->setRouteSpeed(Utility::binToDec(stoi(pAdnChain.substr(1, 3))));
    childSpectrum->setChaseSpeed(Utility::binToDec(stoi(pAdnChain.substr(4, 3))));
    childSpectrum->setSightRange(Utility::binToDec(stoi(pAdnChain.substr(7, 3))));
    cout << "\t\t  Child: "; childSpectrum->toString();
    return childSpectrum;
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
// Original
    cout << "\n\t\t [ORIGINAL]      " << pAdn << endl;
// Probability for Mutation : 8%
    gen = Utility::Random(100);
    if (mutationProbability >= gen)
    {
        cout<< "\t\t  M % "<<gen <<endl;
        pAdn = Mutation(pAdn);
    }
// Probability for Inversion : 4%
    gen =  Utility::Random(100);
    if (inversionProbability >= gen)
    {
        cout<< "\t\t  I % "<<gen <<endl;
        pAdn = Inversion(pAdn);
    }
    return pAdn;
}

string Crossbreed::Mutation(string &pAdn)
{
    int gen = Utility::Random(9);
    pAdn = replace(gen, 1, pAdn);
    cout << "\t\t   [Mutation]  "<< gen << " " << pAdn << endl;
    return pAdn;
}

string Crossbreed::Inversion(string &pAdn) const {
    int gen = Utility::Random(6);
    pAdn = replace(gen, numOfGenesReversed, pAdn);
    cout << "\t\t   [Inversion] "<< gen << " "<< pAdn << endl;
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
            if (pStr[i] == '0')
            {
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

Spectrum *Crossbreed::Fitness(Spectrum *pCandidate1, Spectrum *pCandidate2)
{
    Spectrum *best;
    int sum1, sum2;
    sum1 = pCandidate1->getChaseSpeed() + pCandidate1->getRouteSpeed() + pCandidate1->getSightRange();
    sum2 = pCandidate2->getChaseSpeed() + pCandidate2->getRouteSpeed() + pCandidate2->getSightRange();
    (sum1 > sum2) ? best=pCandidate1 : best=pCandidate2;
    cout << "   Fitness : "; best->toString();
    return best;
}

void Crossbreed::printPopulation()
{
    cout << "[Cross-Population]"<<endl;
    for (int i=0; i<newPopulationSpectrums->size(); i++)
    {
        cout<<"  "<<newPopulationSpectrums->at(i)->getId();
    }
    cout<<endl;
}



