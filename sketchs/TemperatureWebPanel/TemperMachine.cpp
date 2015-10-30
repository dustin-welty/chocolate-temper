
#include "TemperMachine.h"
#include <stdio.h>
#include <string.h>

TemperMachine::TemperMachine(BYTE byMeltingTemp /*= 100*/, BYTE byTemperTemp /*= 86*/, BYTE byHoldingTemp /*= 88*/)
{
	// internal settings
	m_byMeltingTemp = byMeltingTemp;
	m_byTemperTemp = byTemperTemp;
	m_byHoldingTemp = byHoldingTemp;

	// internal state
	m_bHeaterRunning = false;
	m_bHeaterFanRunning = false;
	m_bExhaustFanRunning = false;
	m_bBowlTurning = false;
	m_bIsMelting = false;

	m_bOn = false;
	m_bHold = false;

	m_byCurrentAirTemp = 60;
	m_byCurrentChocolateTemp = 60;
}

void TemperMachine::Init(bool bHeaterRunning, bool bHeaterFanRunning, bool bExhaustFanRunning, bool bBowlTurning)
{
  m_bHeaterRunning = bHeaterRunning;
  m_bHeaterFanRunning = bHeaterFanRunning;
  m_bExhaustFanRunning = bExhaustFanRunning;
  m_bBowlTurning = bBowlTurning;
  m_bIsMelting = false;
  m_bOn = false;
  m_bHold = false;
}

bool TemperMachine::bCommand(const char *psCommand, char *psReturnVal)
{
	bool bProcessedCmd = true;
	if (strcmp(psCommand, "machine") == 0)
	{
		if (m_bOn)
		{
			strcpy(psReturnVal, "On");
		}
		else
		{
			strcpy(psReturnVal, "Off");
		}
	}
	else if (strcmp(psCommand, "hold") == 0)
	{
		if (m_bHold)
		{
			strcpy(psReturnVal, "On");
		}
		else
		{
			strcpy(psReturnVal, "Off");
		}
	}
	else if (strcmp(psCommand, "heater") == 0)
    {
        if (m_bHeaterRunning)
        {
           strcpy(psReturnVal, "On");
        }
        else
        {
           strcpy(psReturnVal, "Off");
        }
    }
    else if (strcmp(psCommand, "bowl") == 0)
    {
        if (m_bBowlTurning)
        {
            strcpy(psReturnVal, "On");
        }
        else
        {
            strcpy(psReturnVal, "Off");
        }
    }
    else if (strcmp(psCommand, "air_temp") == 0)
    {
        sprintf(psReturnVal, "%d", m_byCurrentAirTemp);
    }
    else if (strcmp(psCommand, "choc_temp") == 0)
    {
        sprintf(psReturnVal, "%d", m_byCurrentChocolateTemp);
    }
    else if (strcmp(psCommand, "melt_temp") == 0)
    {
        sprintf(psReturnVal, "%d", m_byMeltingTemp);
    }
    else if (strcmp(psCommand, "temper_temp") == 0)
    {
        sprintf(psReturnVal, "%d", m_byTemperTemp);
    }
    else if (strcmp(psCommand, "hold_temp") == 0)
    {
        sprintf(psReturnVal, "%d", m_byHoldingTemp);
    }
    else if (strcmp(psCommand, "chocolate_melted") == 0)
    {
        if (m_bIsMelting)
        {
            strcpy(psReturnVal, "Yes");
        }
        else
        {
            strcpy(psReturnVal, "No");
        }
    }
    else if (strcmp(psCommand, "chocolate_melted_set") == 0)
    {
        m_bIsMelting = !m_bIsMelting;
        if (m_bIsMelting)
        {
            strcpy(psReturnVal, "Yes");
        }
        else
        {
            strcpy(psReturnVal, "No");
        }
    }
    else if (strcmp(psCommand, "machine_set") == 0)
    {
        m_bOn = !m_bOn;

        if (m_bOn)
        {
           strcpy(psReturnVal, "On");
        }
        else
        {
            strcpy(psReturnVal, "Off");
        }
    }
    else if (strcmp(psCommand, "hold_set") == 0)
    {
        m_bHold = !m_bHold;
        if (m_bHold)
        {
        	m_bIsMelting = false;
            strcpy(psReturnVal, "On");
        }
        else
        {
            strcpy(psReturnVal, "Off");
        }
    }
    else
    {
    	bProcessedCmd = false;
    }

    return bProcessedCmd;
}

void TemperMachine::GetValuesToSet(bool *pbHeaterOn, bool *pbHeaterFanOn, bool *pbExhaustFanOn, bool *bBowlOn)
{
	m_bHeaterRunning = false;
	m_bHeaterFanRunning = false;
	m_bExhaustFanRunning = false;
	m_bBowlTurning = false;

	if (m_bOn)
	{
		m_bBowlTurning = true;
		m_bExhaustFanRunning = true;

		if (m_bHold)
		{
			if (m_byCurrentAirTemp < m_byHoldingTemp)
			{
				m_bHeaterRunning = true;
				m_bHeaterFanRunning = true;
				m_bExhaustFanRunning = false;
			}
		}
		else
		{
			if (m_bIsMelting && m_byCurrentAirTemp < m_byMeltingTemp)
			{
				m_bHeaterRunning = true;
				m_bHeaterFanRunning = true;
				m_bExhaustFanRunning = false;
			}
			else if (!m_byMeltingTemp && m_byCurrentAirTemp < m_byTemperTemp)
			{
				m_bHeaterRunning = true;
				m_bHeaterFanRunning = true;
				m_bExhaustFanRunning = false;
			}
		}
	}

	*pbHeaterOn = m_bHeaterRunning;
	*pbHeaterFanOn = m_bHeaterFanRunning;
	*pbExhaustFanOn = m_bExhaustFanRunning;
	*bBowlOn = m_bBowlTurning;
}
