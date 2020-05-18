#ifndef broRotaryEncoderH
#define broRotaryEncoderH

#include <Arduino.h>
#include "settings.h"

class BroRotaryEncoder
{
private:
	bool _wasHoldStarted = false;
	callback _onRightTurnCallbackFunc = nullptr;
	callback _onLeftTurnCallbackFunc = nullptr;
	callback _onRightHoldTurnCallbackFunc = nullptr;
	callback _onLeftHoldTurnCallbackFunc = nullptr;
	callback _onClickCallbackFunc = nullptr;
	callback _onDoubleClickCallbackFunc = nullptr;
	callback _onPressStartCallbackFunc = nullptr;
	callback _onPressStopCallbackFunc = nullptr;

	byte _pinClk, _pinDt, _pinSw;
	bool _wasButtonPressed = false;
	Flags _flags;
	BroRotaryEncoderState _previosTwisterState = BroRotaryEncoderState::Normal;
	BroRotaryEncoderState _currentTwisterState = BroRotaryEncoderState::Normal;
	unsigned long _lastTimestampInMilliseconds = 0;

	bool WasRightTurn();
	bool WasLeftTurn();
	bool WasRightHoldTurn();
	bool WasLeftHoldTurn();
	bool WasHolded();
	bool WasSingleClicked();
	bool WasDoubleClicked();
	unsigned char ReadTwisterState();
	void ObserveButtonEvents(unsigned long &currentMillis);
	void ObserveTwisterEvents(unsigned long &currentMillis);

public:
	BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw);
	void Tick(void);
	void AttachOnClick(callback newFunction);
	void AttachOnDoubleClick(callback newFunction);
	void AttachOnPressStart(callback newFunction);
	void AttachOnPressStop(callback newFunction);
	void AttachOnRightTurn(callback newFunction);
	void AttachOnLeftTurn(callback newFunction);
	void AttachOnRightHoldTurn(callback newFunction);
	void AttachOnLeftHoldTurn(callback newFunction);
};
#endif //broRotaryEncoderH