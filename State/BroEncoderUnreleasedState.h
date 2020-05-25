#ifndef BroEncoderUnreleasedStateH
#define BroEncoderUnreleasedStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderUnreleasedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderUnreleasedStateH