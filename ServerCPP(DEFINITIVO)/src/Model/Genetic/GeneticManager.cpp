#include "GeneticManager.h"
#include "Tools/Utility.h"
#include "../Spectres/Spectre.h"

int GeneticManager::totalSpectres = 1;

void GeneticManager::setPrimaryGroup()
{
    cout << "[MANAGER-START]\tFIRST GENERATION" << endl;
    auto *genList = new vector<Spectrum *>;

    for (int j = 0; j < this->spectresPerLvl; j++)
    {
        //First Spectrum.
        auto *spectrum = new Spectrum(generateId(),getRandom(), getRandom(), getRandom());
        vector<Spectrum *> *list = spectrum->getSiblingsList();
        list->push_back(spectrum);

//        cout << "\nGroup "<<j+1 << endl;
//        spectrum->toString();

        //Siblings of the foregoing spectrum :
        for (int k = 0; k < this->totalSample; k++)
        {
            // Create List of Spectrum with random attributes.
            auto *siblingsList = new vector<Spectrum *>;
            auto *sibling = new Spectrum(generateId(), getRandom(), getRandom(), getRandom());
            list->push_back(sibling);
//            sibling->toString();
        }
        // Return the best spectrum as the main one.
        genList->push_back(chooseBestDescendant(spectrum->getSiblingsList()));

    }
    spectrumGroup = genList;
    setGroup();
    cout << endl << "[MANAGER-END]"<<endl;
}

Spectrum* GeneticManager::chooseBestDescendant(vector<Spectrum *> *pDescendantSiblings) {
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

/*
 * Pass the genetic attributes from SpectrumList to SpectreList, received in param, to be used in game.
 */
void GeneticManager::setGroup()
{
    auto* spectres =  Spectre::listOfSpectres;
    for (int i = 0; i <= spectres->size(); i++)
    {
        auto* spectre = spectres->at(i);
        spectre->setRouteVelocity(spectrumGroup->at(i)->getRouteSpeed());
        spectre->setRouteVelocity(spectrumGroup->at(i)->getRouteSpeed());
        spectre->setRouteVelocity(spectrumGroup->at(i)->getRouteSpeed());

        cout << "SetGroup" << endl;
        spectre->printSpectre();
    }
}

/**
 *
 * @return
 */
vector<Spectrum *> *GeneticManager::getNextGroup()
{
    vector<Spectrum*>* newGen = crossbreed->getNewGroup(spectrumGroup);
    return nullptr;
}

/**
 * Generate id for the spectrum
 * @return
 */
string GeneticManager::generateId(){
    string id = "spectre_" + to_string(totalSpectres);
    return id;
}

/**
 * Get the number of the total spectrums sample created.
 * @return
 */
int GeneticManager::getTotalSpectrums()
{
    return totalSpectres;
}

/**
 * Increase total spectres counter
 */
void GeneticManager::increaseTotalSpectrums()
{
    totalSpectres++;
}

/**
 * Decrease total spectre counter.
 */
void GeneticManager::decreaseTotalSpectrums()
{
    totalSpectres--;
}

/**
 * Get a random number using utility class.
 * @return
 */
int GeneticManager::getRandom() {
    return Utility::Random(1,initialVariability);
}