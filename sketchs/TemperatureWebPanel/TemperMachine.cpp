
bool TemperMachine::bCommand(String &sCommand, String *psReturnVal);
{
	bool bProcessedCmd = true;
	if (sCommand == "heater")
    {
        if (bHeaterOn)
        {
           *psReturnVal = "On";
        }
        else
        {
           *psReturnVal = "Off";
        }
    }
    else if (sCommand == "bowl")
    {
        if (bBowlOn)
        {
            *psReturnVal = "On";
        }
        else
        {
            *psReturnVal = "Off";
        }
    }
    else if (sCommand == "air_temp")
    {
        *psReturnVal = 
    }
    else if (sCommand == "choc_temp")
    {
        *psReturnVal = int(Thermistor(analogRead(0)));
    }
    else if (sCommand == "melt_temp")
    {
        *psReturnVal = iMeltTemp;
    }
    else if (sCommand == "temper_temp")
    {
        *psReturnVal = iTemperTemp;
    }
    else if (sCommand =="chocolate_melted")
    {
        if (bMelting)
        {
            *psReturnVal = "Yes";
        }
        else
        {
            *psReturnVal = "No";
        }
    }
    else if (sCommand =="chocolate_melted_set")
    {
        bMelting = !bMelting;
        if (bMelting)
        {
            *psReturnVal = "Yes";
        }
        else
        {
            *psReturnVal = "No";
        }
    }
    else if (sCommand == "heater_set")
    {
        bHeaterOn = !bHeaterOn;

        if (bHeaterOn)
        {
           *psReturnVal = "On";
        }
        else
        {
            *psReturnVal = "Off";
        }
    }
    else if (sCommand == "bowl_set")
    {
        bBowlOn = !bBowlOn;
        if (bBowlOn)
        {
            *psReturnVal = "On";
        }
        else
        {
            *psReturnVal = "Off";
        }
    }
    else
    {
    	bProcessedCmd = false;
    }

    return bProcessedCmd;
}
