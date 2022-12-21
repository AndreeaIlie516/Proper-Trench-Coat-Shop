#include <iostream>
#include "ActionFilter.h"


void ActionFilter::executeUndo() {
    for (int i = 0; i < deletedTrenchCoats.size(); ++i) {
        repositoryUsed->addTrenchCoat(deletedTrenchCoats[i]);
    }
}

void ActionFilter::executeRedo() {
    for (int i = 0; i < deletedTrenchCoats.size(); ++i)
        repositoryUsed->removeTrenchCoat(deletedTrenchCoats[i]);
}
