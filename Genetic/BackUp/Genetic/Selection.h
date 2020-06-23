#ifndef BACKUP_SELECTION_H
#define BACKUP_SELECTION_H

#include "Spectrum.h"

class Selection {

private:
    LinkedList<Spectrum*> *population = new LinkedList<Spectrum*>;

public:

    LinkedList<Spectrum*>* getSelected(LinkedList<Spectrum*> *pGeneration);
};

#endif //BACKUP_SELECTION_H
