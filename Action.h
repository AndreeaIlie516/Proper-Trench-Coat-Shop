#pragma once
#include "FileRepository.h"
#include "TrenchCoat.h"

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};
