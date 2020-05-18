#ifndef broRotaryEncoderSettingsH
#define broRotaryEncoderSettingsH

extern "C"
{
    typedef void (*callback)(void);
}

#define ButtonDebounceInMilliseconds 50
#define ButtonHoldTimeoutInMilliseconds 1000
#define ButtonDoubleClickTimeoutInMilliseconds 300

#pragma pack(push, 1)
typedef struct
{
    bool hold_flag : 1;
    bool butt_flag : 1;
    bool turn_flag : 1;
    bool isTurn_f : 1;
    bool isPress_f : 1;
    bool isRelease_f : 1;
    bool isHolded_f : 1;
    bool isSingle_f : 1;
    bool isDouble_f : 1;
    bool countFlag : 1;
    bool doubleFlag : 1;
    bool doubleAllow : 1;
    bool rst_flag : 1;
} Flags;
#pragma pack(pop)

enum BroRotaryEncoderState
{
    Normal = 0,
    LeftTurn = 1,
    RightTurn = 2,
    LeftHoldTurn = 3,
    RightHoldTurn = 4,
};

#endif //broRotaryEncoderSettingsH