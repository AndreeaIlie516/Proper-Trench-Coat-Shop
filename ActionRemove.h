#pragma once
#include "Action.h"
#include "FileRepository.h"
#include "TrenchCoat.h"

class ActionRemove : public Action {
    TrenchCoat deletedTrenchCoat;
    FileRepository* repositoryUsed;
public:
    void executeUndo() override;
    void executeRedo() override;
    ActionRemove(FileRepository* repository, TrenchCoat trenchCoat) :deletedTrenchCoat{ trenchCoat }, repositoryUsed { repository }{}

};

