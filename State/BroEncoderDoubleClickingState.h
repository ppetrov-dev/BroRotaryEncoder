#ifndef BroEncoderDoubleClickingStateH
#define BroEncoderDoubleClickingStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderDoubleClickingState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

#endif //BroEncoderDoubleClickingStateH