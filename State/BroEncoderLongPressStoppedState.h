#ifndef BroEncoderLongPressStoppedStateH
#define BroEncoderLongPressStoppedStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderLongPressStoppedState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

#endif //BroEncoderLongPressStoppedStateH