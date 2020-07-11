#include <iomanip>
#include "GeneticManager.h"
#include "Tools/Utility.h"
#include "../Spectres/Spectre.h"

int GeneticManager::totalSample = 10;
int GeneticManager::totalSpectres = 0;
int GeneticManager::minRandom = 5;
int GeneticManager::maxRandom = 6;

/*
 * Set the attributes of the first population.
 */
void GeneticManager::setPrimaryGroup()
{
    printListOfSpectres();
//    cout << "============> [MANAGER-START] <============ "<< endl;
    cout << "~~~~~~~~~~~~~~> \' GEN " << Crossbreed::generationMarker++ << " \'<~~~~~~~~~~~~~~"<< endl;

    auto *temporalList = new vector<Spectrum *>;

    // Por cada Spectre (interfaz) en la lista estática listOfSpectres, genero un Spectrum en la lista temporal.
    for (int j = 0; j < Spectre::listOfSpectres->size();  j++)
    //    for (int j = 0; j < Spectre::listOfSpectres->size();  j++)
    {

    // PRIMERO CREO 10 ESPECTROS EN UNA LISTA POR CADA SPECTRUM NECESITADO EN LA LISTA DE SPECTRES.
        auto *list = new vector<Spectrum *>(); // lista en donde meto los espectros.

        for (int k = 0; k < GeneticManager::totalSample; k++)  // totalSample es el tamaño de la muestra.
        {
            // Create List of Spectrum with random attributes.
            auto *spectrum = new Spectrum(generateId(), getRandom(), getRandom(), Utility::Random(1, 2));
            list->push_back(spectrum);
//            spectrum->toString();
        }

    // SEGUNDO : SELECCIONO EL MEJOR DE LOS 10 ESPECTROS EN LA LISTA.
        Spectrum* chosen = chooseBestSpectrum(list);
    // TERCERO : SETEAR LA LISTA DE HERMANOS A LA LISTA DE TODA LA MUESTRA, INCLUYENDO AL MEJOR.
        chosen->setBrotherhoodList(list); // Utilizada más adelante para la reproducción.
        temporalList->push_back(chosen);
    }
    listOfSpectrums = temporalList;
    assignToSpectre(temporalList);

//    cout << "============> [MANAGER-END] <============"<<endl;
}

/*
 * Set the attributes of the next population.
 */
void GeneticManager::setGroup()
{
    listOfSpectrums = crossbreed->getNextGenOfSpectrums(listOfSpectrums);
    assignToSpectre(listOfSpectrums);
}

/**
 * Choose best spectrum of the sampl
 * @param pList
 * @return
 */
Spectrum* GeneticManager::chooseBestSpectrum(vector<Spectrum *> *pList) {
//    cout << "{\n";
    Spectrum *goat = pList->at(0); // El mejor empieza siendo el primero.
//    goat->toString();

    for (int h = 1; h < pList->size(); h++)
    {
        auto* spectrum = pList->at(h);
//        spectrum->toString();

        // Compare each attribute.
        // FIRST GET THE FASTEST
        int betterSpeed = 0;
        if ( spectrum->getRouteSpeed() <= goat->getRouteSpeed() )
            betterSpeed++;
        if ( spectrum->getChaseSpeed() < goat->getChaseSpeed() )
            betterSpeed++;
        if (betterSpeed == 2){
            goat = spectrum;
        }
    }
//    cout << "}\n";
//    cout << "+ Better Speed  > "; goat->toString();
    // THEN GET THE FASTEST WITH LONGEST VISION RANGE
    for (auto & g : *pList)
    {
        if (g->getSightRange() > goat->getSightRange())
            if (g->getChaseSpeed() <= goat->getChaseSpeed()  && g->getRouteSpeed() <= goat->getRouteSpeed() ) {
//                cout << "+ Better Vision > "; g->toString();
                goat = g;
            }
    }

    goat->setBrotherhoodList(pList);
//    cout << "* GOAT : "; goat->toString(); cout << endl;
    return goat;
}


/**
 * Assign attributes of each spectrum in the parameter list to each spectre in the static list, respectively.
 * @param pList
 */
void GeneticManager::assignToSpectre(vector<Spectrum *> *pList) {
    for (int j = 0; j < Spectre::listOfSpectres->size(); j++)
    {
        auto* spectre = Spectre::listOfSpectres->at(j);
        auto* spectrum = pList->at(j);
        spectre->setRouteVelocity(speedsDiccionary[spectrum->getRouteSpeed()]);
        spectre->setPersuitVelocity(speedsDiccionary[spectrum->getChaseSpeed()]);
        spectre->setVisionRange(spectrum->getSightRange());
    }
    printListOfSpectres();
}

/**
 * Generate id for the spectrum
 * @return
 */
string GeneticManager::generateId(){
    string id = "spectrum_" + to_string(totalSpectres);
    return id;
}

/**
 * Increase total spectres counter
 */
void GeneticManager::increaseTotalSpectrums()
{
    totalSpectres++;
}

/**
 * Get a random number using utility class.
 * @return
 */
int GeneticManager::getRandom() {
    return Utility::Random(minRandom, maxRandom);
}

/**
 * Print the list of spectres.
 */
void GeneticManager::printListOfSpectres() {
//    cout << "------------> Spectres Static List <------------" << endl;
    for(auto & spectre : *Spectre::listOfSpectres)
    {
        cout << std::setprecision(1) << std::fixed <<
             spectre->getId() << " |\t" <<
             spectre->getRouteVelocity() << "   " <<
             spectre->getPersuitVelocity() << "   " <<
             spectre->getVisionRange() << endl;
    }
    cout <<endl;
}

/**
 * Setter for attribute listOfSpectrum.
 * @param listOfSpectrum
 */
void GeneticManager::setListOfSpectrum(vector<Spectrum *> *listOfSpectrum) {
    GeneticManager::listOfSpectrums = listOfSpectrum;
}

void GeneticManager::loadGenetic() {
    if (isPrimary){
        isPrimary = false;
        return setPrimaryGroup();
    }
    setGroup();
}




