#ifndef __TEMPERMACHINE_H__
#define __TEMPERMACHINE_H__

/*
Need comments

Copywrite Dustin J Welty 2015
*/

#define BYTE unsigned char

class TemperMachine
{
public:
	TemperMachine(BYTE byMeltingTemp = 100, BYTE BYTEmperTemp = 86, BYTE byHoldingTemp= 88);
	~TemperMachine(void) {};

	//get/set settings
	BYTE byGetMeltingTemp(void) { return m_byMeltingTemp; }
	BYTE byGetTemperTemp(void) { return m_byTemperTemp; }
	BYTE byGetHoldingTemp(void) { return m_byHoldingTemp; }
	void SetMeltingTemp(BYTE BYTEmp) { m_byMeltingTemp = BYTEmp; }
	void SetTemperTemp(BYTE BYTEmp) { m_byTemperTemp = BYTEmp; }
	void SetHoldingTemp(BYTE BYTEmp) { m_byHoldingTemp = BYTEmp; }

	//get/set state
	void SetCurrentChocolateTemp(BYTE BYTEmp) { m_byCurrentAirTemp = BYTEmp; }
	void SetCurrentAirTemp(BYTE BYTEmp) { m_byCurrentChocolateTemp = BYTEmp; }
	void SetHeaterRunning(bool bRunning) { m_bHeaterRunning = bRunning; }
	void SetHeaterFanRunning(bool bRunning) { m_bHeaterFanRunning = bRunning; }
	void SetExhaustFanRunning(bool bRunning) { m_bExhaustFanRunning = bRunning; }
	void SetBowlTurning(bool bTurning) { m_bBowlTurning = bTurning; }
	void SetMelting(bool bIsMelting) { m_bIsMelting = bIsMelting; }
	void SetOn(bool bIsOn) { m_bOn = bIsOn; }
	void SetHold(bool bIsHold) {m_bHold = bIsHold; }

	BYTE byGetCurrentChocolateTemp(void) { return m_byCurrentAirTemp; }
	BYTE byGetCurrentAirTemp(void) { return m_byCurrentChocolateTemp; }
	bool bGetHeaterRunning(void) { return m_bHeaterRunning; }
	bool bGetHeaterFanRunning(void) { return m_bHeaterFanRunning; }
	bool bGetExhaustFanRunning(void) { return m_bExhaustFanRunning; }
	bool bGetBowlTurning(void) { return m_bBowlTurning; }
	bool bIsMelting(void) { return m_bIsMelting; }
	bool bIsOn(void) { return m_bOn; }
	bool bIsHold(void) {return m_bHold; }

	void Init(bool bHeaterRunning, bool bHeaterFanRunning, bool bExhaustFanRunning, bool bBowlTurning);

	//logic level/operation methods
	//recieves the command a returns the result to be displayed
	bool bCommand(const char *psCommand, char *psReturnVal);
	void GetValuesToSet(bool *pbHeaterOn, bool *pbHeaterFanOn, bool *pbExhaustFanOn, bool *bBowlOn); 

private:
	// internal settings
	BYTE m_byMeltingTemp;
	BYTE m_byTemperTemp;
	BYTE m_byHoldingTemp;

	// internal state
	bool m_bHeaterRunning;
	bool m_bHeaterFanRunning;
	bool m_bExhaustFanRunning;
	bool m_bBowlTurning;
	bool m_bIsMelting;

	bool m_bOn;
	bool m_bHold;

	BYTE m_byCurrentAirTemp;
	BYTE m_byCurrentChocolateTemp;
};

#endif
