#ifndef GyverEncoder_h
#define GyverEncoder_h

#include <Arduino.h>

#define DEBOUNCE_TURN 1
#define DEBOUNCE_BUTTON 80
#define HOLD_TIMEOUT 700

#pragma pack(push,1)
typedef struct
{	
	bool SW_state: 1;
	bool hold_flag: 1;
	bool butt_flag: 1;
	bool turn_flag: 1;
	bool isTurn_f: 1;
	bool isPress_f: 1;
	bool isRelease_f: 1;
	bool isHolded_f: 1;
	bool isFastR_f: 1;
	bool isFastL_f: 1;
	bool enc_tick_mode: 1;
	bool enc_type: 1;

} GyverEncoderFlags;
#pragma pack(pop)

class Encoder
{
  public:
    Encoder(uint8_t clk, uint8_t dt, uint8_t sw);				// CLK, DT, SW
	Encoder(uint8_t clk, uint8_t dt, uint8_t sw, boolean);		
		
	void tick();						
	void setType(boolean type);			
	void setTickMode(boolean tickMode); 
	void setDirection(boolean direction);	
	void setFastTimeout(int timeout);		
	
	boolean isTurn();					
	boolean isRight();					
	boolean isLeft();					
	boolean isRightH();				
	boolean isLeftH();				
	boolean isFastR();					
	boolean isFastL();					
	
	boolean isPress();					
	boolean isRelease();					
	boolean isClick();						
    boolean isHolded();					
	boolean isHold();					
	int8_t fast_timeout = 50;				
	
  private:
	void init();
	GyverEncoderFlags flags;
	byte curState, prevState;
	byte encState;	
	uint32_t debounce_timer = 0, fast_timer;
    byte _CLK = 0, _DT = 0, _SW = 0;
	
};

#define TYPE1 0			
#define TYPE2 1			
#define NORM 0		
#define REVERSE 1	
#define MANUAL 0	
#define AUTO 1		
 
#endif