class TemperMachine
{
public:
	TemperMachine(byte byMeltingTemp = 100, byte byTemperTemp = 86, byte byHoldingTemp= 88);
	~TemperMachine();

	//get/set settings
	byte byGetMeltingTemp() { return m_byMeltingTemp; }
	byte byGetTemperTemp() { return m_byTemperTemp; }
	byte byGetHoldingTemp() { return m_byHoldingTemp; }
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

	byte byGetCurrentChocolateTemp() { return m_byCurrentAirTemp; }
	byte byGetCurrentAirTemp() { return m_byCurrentChocolateTemp; }
	bool bGetHeaterRunning() { return m_bHeaterRunning; }
	bool bGetHeaterFanRunning() { return m_bHeaterFanRunning; }
	bool bGetExhaustFanRunning() { return m_bExhaustFanRunning; }
	bool bGetBowlTurning() { return m_bBowlTurning; }
	bool bIsMelting() { return m_bIsMelting; }


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
