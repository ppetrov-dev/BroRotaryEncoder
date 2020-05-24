#ifndef broRotaryEncoderH
#define broRotaryEncoderH

#include "BroSimpleRotaryEncoder.h"
#include "settings.h"

class BroRotaryEncoder : public BroSimpleRotaryEncoder
{
private:
	unsigned long _clickTicks = 500;  // number of ticks that have to pass by
									  // before a click is detected.
	unsigned long _pressTicks = 1000; // number of ticks that have to pass by
									  // before a long button press is detected
	unsigned long _debounceTicks = 50; // number of ticks for debounce times.

	byte _pinSw;
	int _buttonPressedValue;

	BroEncoderButtonState _buttonState = BroEncoderButtonState::Normal;
	unsigned long _startTime; 
	unsigned long _stopTime; 

	void (*_onRightHoldTurnCallbackFunc)() = nullptr;
	void (*_onLeftHoldTurnCallbackFunc)() = nullptr;
	void (*_onClickCallbackFunc)() = nullptr;
	void (*_onDoubleClickCallbackFunc)() = nullptr;
	void (*_onLongPressStartCallbackFunc)() = nullptr;
	void (*_onLongPressStopCallbackFunc)() = nullptr;
	void SetButtonState(const bool& isButtonPressed);
	void RaiseButtonsEvents(void);
	void RaiseTwisterEvents(const bool &isButtonPressed);
	void RaiseLeftHoldTurnIfNotNull(void);
	void RaiseRightHoldTurnIfNotNull(void);

public : BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw, bool isActiveLow, bool isPullupActive);
	BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw);
	void Tick(void);
	void AttachOnClick(void (*newFunction)());
	void AttachOnDoubleClick(void (*newFunction)());
	void AttachOnLongPressStart(void (*newFunction)());
	void AttachOnLongPressStop(void (*newFunction)());
	void AttachOnRightHoldTurn(void (*newFunction)());
	void AttachOnLeftHoldTurn(void (*newFunction)());

	void SetDebounceTicks(unsigned long milliseconds);
	void SetClickTicks(unsigned long milliseconds);
	void SetPressTicks(unsigned long milliseconds);

	int GetLastPressedTicks();
	void Reset(void);
};
#endif //broRotaryEncoderH