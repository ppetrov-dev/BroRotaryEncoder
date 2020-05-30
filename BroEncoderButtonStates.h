#ifndef BroEncoderButtonStatesH
#define BroEncoderButtonStatesH

#include "BroEncoderStateBase.h"

class BroEncoderUnreleasedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};
class BroEncoderNormalState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

class BroEncoderSingleClickCandidateState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

class BroEncoderSingleClickState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

class BroEncoderSingleClickedState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};
class BroEncoderDoubleClickCandidateState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

class BroEncoderDoubleClickingState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

class BroEncoderDoubleClickedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
};

class BroEncoderLongPressCandidateState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

class BroEncoderLongPressStartedState : public BroEncoderStateBase
{
public:
    void Tick(const bool &isButtonPressed, const unsigned long &milliseconds) override;
    void Drop(const bool &isButtonPressed) override;
};
class BroEncoderLongPressStoppedState : public BroEncoderStateBase
{
public:
    void RaiseEventIfNeeded() override;
};

#endif //BroEncoderButtonStatesH