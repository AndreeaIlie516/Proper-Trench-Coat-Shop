#pragma once
#include "Action.h"
#include "FileRepository.h"
#include "TrenchCoat.h"

class ActionAdd : public Action {
private:
    TrenchCoat addedTrenchCoat;
    FileRepository* repositoryUsed;
public:
    ActionAdd(FileRepository* repository, TrenchCoat trenchCoat) :addedTrenchCoat{ trenchCoat }, repositoryUsed{ repository }{}

    void executeUndo() override;
    void executeRedo() override;

};
