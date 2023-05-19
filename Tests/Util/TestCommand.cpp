#include "TestCommand.h"

using namespace psdf;

TestCommand::SharedPtr TestCommand::create()
{
    return SharedPtr(new TestCommand());
}

Shape::SharedPtr TestCommand::perform(const Shape::SharedPtr &polygon) const
{
    return polygon;
}

std::string TestCommand::getName() const
{
    return "TestCommand";
}
