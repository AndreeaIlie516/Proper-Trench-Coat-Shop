#pragma once
#include "Action.h"
#include "FileRepository.h"
#include "TrenchCoat.h"
#include <vector>

class ActionFilter : public Action {
    std::vector<TrenchCoat> deletedTrenchCoats;
    FileRepository* repositoryUsed;
public:
    void executeUndo() override;
    void executeRedo() override;
    ActionFilter(FileRepository* repository, std::vector<TrenchCoat> trenchCoatList) :deletedTrenchCoats{ trenchCoatList }, repositoryUsed{ repository }{}

};