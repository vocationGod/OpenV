#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovLayout.h"
#include <optional>
namespace ov {

class ProcessorPrivate;
class OPENV_API Processor : public Element
{
    OPENV_DECLARE_PRIVATE(Processor)
    OPENV_DISABLE_COPY(Processor)
public:
    static std::shared_ptr<ov::Processor> gen();
};
}