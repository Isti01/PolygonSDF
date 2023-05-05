#include "TestCommand.h"

using namespace psdf;

TestCommand::SharedPtr TestCommand::create()
{
    return SharedPtr(new TestCommand());
}

Polygon::SharedPtr TestCommand::perform(const Polygon::SharedPtr &polygon) const
{
    return polygon;
}

std::string TestCommand::getName() const
{
    return "TestCommand";
}
