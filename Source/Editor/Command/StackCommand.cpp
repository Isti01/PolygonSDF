#include "StackCommand.h"

using namespace psdf;

bool StackCommand::canMerge(const StackCommand::SharedPtr &) const
{
    return false;
}

StackCommand::SharedPtr StackCommand::merge(const StackCommand::SharedPtr &pOther)
{
    if (canMerge(pOther)) {
        return shared_from_this();
    }
    return nullptr;
}
