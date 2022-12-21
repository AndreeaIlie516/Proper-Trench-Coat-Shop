#pragma once
#include "Action.h"
#include "FileRepository.h"
#include "TrenchCoat.h"

class ActionUpdate : public Action {
    TrenchCoat newTrenchCoat;
    TrenchCoat oldTrenchCoat;
    FileRepository* repositoryUsed;
public:
    void executeUndo() override;
    void executeRedo() override;
    ActionUpdate(FileRepository* repository, TrenchCoat oldTrenchCoat, TrenchCoat newTrenchCoat) :oldTrenchCoat{ oldTrenchCoat }, newTrenchCoat{ newTrenchCoat }, repositoryUsed{ repository }{}

};