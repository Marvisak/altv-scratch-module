#include <string>
#include <memory>
#include <cmath>
#include "NestedBlock/RoundBlock/Operators/OperatorsMod.h"

MultiType OperatorsMod::getValue() const
{
    return std::fmod(num1->getDouble(), num2->getDouble());
}

OperatorsMod::OperatorsMod(std::shared_ptr<NestedBlock> n1, std::shared_ptr<NestedBlock> n2) : num1(n1), num2(n2) {}
