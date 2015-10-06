
class TemperMachine
{
public:
	TemperMachine(byte byMeltingTemp = 100, byte byTemperTemp = 86, byte byHoldingTemp= 88);
	~TemperMachine(void);

	//get/set settings
	byte byGetMeltingTemp(void) { return m_byMeltingTemp; }
	byte byGetTemperTemp(void) { return m_byTemperTemp; }
	byte byGetHoldingTemp(void) { return m_byHoldingTemp; }
	void SetMeltingTemp(byte byTemp) { m_byMeltingTemp = byTemp; }
	void SetTemperTemp(byte byTemp) { m_byTemperTemp = byTemp; }
	void SetHoldingTemp(byte byTemp) { m_byHoldingTemp = byTemp; }

	//get/set state
	void SetCurrentChocolateTemp(byte byTemp) { m_byCurrentAirTemp = byTemp; }
	void SetCurrentAirTemp(byte byTemp) { m_byCurrentChocolateTemp = byTemp; }
	void SetHeaterRunning(bool bRunning) { m_bHeaterRunning = bRunning; }
	void SetHeaterFanRunning(bool bRunning) { m_bHeaterFanRunning = bRunning; }
	void SetExhaustFanRunning(bool bRunning) { m_bExhaustFanRunning = bRunning; }
	void SetBowlTurning(bool bTurning) { m_bBowlTurning = bTurning; }
	void bIsMelting(bool bIsMelting) { m_bIsMelting = bIsMelting; }

	byte byGetCurrentChocolateTemp(void) { return m_byCurrentAirTemp; }
	byte byGetCurrentAirTemp(void) { return m_byCurrentChocolateTemp; }
	bool bGetHeaterRunning(void) { return m_bHeaterRunning; }
	bool bGetHeaterFanRunning(void) { return m_bHeaterFanRunning; }
	bool bGetExhaustFanRunning(void) { return m_bExhaustFanRunning; }
	bool bGetBowlTurning(void) { return m_bBowlTurning; }
	bool bIsMelting(void) { return m_bIsMelting; }

	void Init(bool bHeaterRunning, bool bHeaterFanRunning, bool bExhaustFanRunning, bool bBowlTurning);

	//logic level/operation methods
	//recieves the command a returns the result to be displayed
	bool bCommand(String &sCommand, String *psReturnVal);
	void GetValuesToSet(bool *pbHeaterOn, bool *pbHeaterFanOn, bool *pbExhaustFanOn, bool *bBowlOn); 

private:
	// internal settings
	byte m_byMeltingTemp;
	byte m_byTemperTemp;
	byte m_byHoldingTemp;

	// internal state
	bool m_bHeaterRunning;
	bool m_bHeaterFanRunning;
	bool m_bExhaustFanRunning;
	bool m_bBowlTurning;
	bool m_bIsMelting;

	byte m_byCurrentAirTemp;
	byte m_byCurrentChocolateTemp;
};
