#ifndef BroEncoderDoubleClickedStateH
#define BroEncoderDoubleClickedStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderDoubleClickedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

#endif //BroEncoderDoubleClickedStateH