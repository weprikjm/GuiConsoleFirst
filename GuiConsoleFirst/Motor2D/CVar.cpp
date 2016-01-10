#include "CVar.h"

CVar::CVar(const p2SString& nameIdentifier)
{
	sValue.create(nameIdentifier.GetString());
}

const char* CVar::GetValueToString()
{
	return sValue.GetString();
}



iCVar::iCVar(p2SString& sValue) : CVar(sValue)
{
	iValue = atoi(sValue.GetString());
}

void iCVar::SetValueToInt(p2SString& value)
{
	iValue = atoi(value.GetString());
}
int iCVar::GetValueToInt()
{
	return iValue;
}

iCVar::iCVar(int iValue)
{
	this->iValue = iValue;
}





fCVar::fCVar(p2SString& sValue) : CVar(sValue)
{
	fValue = atof(sValue.GetString());
}


void fCVar::SetValueToFloat(p2SString& value)
{
	fValue = atof(value.GetString());
}
float fCVar::GetValueToFloat()
{
	return fValue;
}

fCVar::fCVar(float fValue)
{
	this->fValue = fValue;
}