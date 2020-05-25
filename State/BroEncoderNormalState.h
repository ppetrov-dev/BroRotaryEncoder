#ifndef BroEncoderNormalStateH
#define BroEncoderNormalStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderNormalState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderNormalStateH