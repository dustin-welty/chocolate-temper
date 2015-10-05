class TemperMachine
{
public:
	TemperMachine(byte byMeltingTemp = 100, byte byTemperTemp = 86, byte byHoldingTemp= 88);
	~TemperMachine();

	void SetCurrentChocolateTemp(byte byTemp);
	void SetCurrentAirTemp(byte byTemp);
	void 
	
private:
	byte m_byMeltingTemp;
	byte m_byTemperTemp;
	byte m_byHoldingTemp;
	bool m_bHeaterRunning;
	bool m_bHeaterFanRunning;
	bool m_bExhaustFanRunning;
	bool m_bBowlTurning;
};