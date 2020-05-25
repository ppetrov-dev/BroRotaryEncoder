#ifndef BroEncoderSingleClickStateH
#define BroEncoderSingleClickStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderSingleClickState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderSingleClickStateH