#include "ActionRemove.h"

void ActionRemove::executeUndo() {
    repositoryUsed->addTrenchCoat(deletedTrenchCoat);
}

void ActionRemove::executeRedo() {
    repositoryUsed->removeTrenchCoat(deletedTrenchCoat);
}
