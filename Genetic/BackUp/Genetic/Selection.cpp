#include "Selection.h"

LinkedList<Spectrum *> *Selection::getSelected(LinkedList<Spectrum *> *pGeneration) {
    population = pGeneration;
    // Codigo y llamadas a otras funciones para seleccionar.
    return population;
}