#include <string>
#include "NestedBlock/RoundBlock/RoundBlock.h"

class DaysSince2000 : public RoundBlock
{
public:
    MultiType getValue() const override;
};
