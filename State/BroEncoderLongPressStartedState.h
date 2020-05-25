#ifndef BroEncoderLongPressStartedStateH
#define BroEncoderLongPressStartedStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderLongPressStartedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
    void Drop(const bool &isButtonPressed) override;
};

#endif //BroEncoderLongPressStartedStateH