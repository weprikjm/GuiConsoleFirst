#include "CVar.h"

CVar::CVar(const p2SString& nameIdentifier)
{
	sValue.create(nameIdentifier.GetString());
}

int CVar::SetValueToInt(p2SString& string)
{
	return iValue = atoi(string.GetString());
}
int CVar::GetValueToInt()
{
	return iValue;
}

const char* CVar::GetValueToString()
{
	return sValue.GetString();
}

/*
p2SString& CVar::operator=(const p2SString& command)
{


}
*/