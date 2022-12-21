#include "ActionAdd.h"

void ActionAdd::executeUndo() {
    repositoryUsed->removeTrenchCoat(addedTrenchCoat);
}

void ActionAdd::executeRedo() {
    repositoryUsed->addTrenchCoat(addedTrenchCoat);
}