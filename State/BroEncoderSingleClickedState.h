#ifndef BroEncoderSingleClickedStateH
#define BroEncoderSingleClickedStateH

#include <State/BroEncoderStateBase.h>

class BroEncoderSingleClickedState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

#endif //BroEncoderSingleClickedStateH