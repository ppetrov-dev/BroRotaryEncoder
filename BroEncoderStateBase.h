#ifndef BroEncoderStateBaseH
#define BroEncoderStateBaseH

class BroRotaryEncoder;
class BroEncoderStateBase
{
protected:
    BroRotaryEncoder *_context;
    void SetStartTime(const unsigned long& milliseconds);
    void SetStopTime(const unsigned long &milliseconds);
    bool IsDebounceExpiredWithStartTime(const unsigned long &milliseconds);
    bool IsDebounceExpiredWithStopTime(const unsigned long &milliseconds);
    bool IsClickTicksExpired(const unsigned long &milliseconds);
    bool IsPressTicksExpired(const unsigned long &milliseconds);
    bool ContainsDoubleClickHandler();
    void RaiseLongPressStartIfNotNull();
    void RaiseLongPressStopIfNotNull();
    void RaiseClickIfNotNull();
    void RaiseDoubleClickIfNotNull();
    void TransitionTo(BroEncoderStateBase* state);
public:
    virtual void Tick(const bool &isButtonPressed, const unsigned long &milliseconds);
    virtual void RaiseEventIfNeeded();
    virtual void Drop(const bool &isButtonPressed);
    void SetContext(BroRotaryEncoder *context);
};
#endif //BroEncoderStateBaseH