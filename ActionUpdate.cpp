#include "ActionUpdate.h"

void ActionUpdate::executeUndo() {
    repositoryUsed->removeTrenchCoat(newTrenchCoat);
    repositoryUsed->addTrenchCoat(oldTrenchCoat);
}

void ActionUpdate::executeRedo() {
    repositoryUsed->removeTrenchCoat(oldTrenchCoat);
    repositoryUsed->addTrenchCoat(newTrenchCoat);
}