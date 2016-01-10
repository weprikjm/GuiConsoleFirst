#ifndef __CVAR_H__
#define __CVAR_H__

#include "p2SString.h"
#include <map>

class CVar
{
public: 
	CVar(const p2SString& nameIdentifier);
	//This Constructor should never be used
	CVar(){}
	
	const char* GetValueToString();

public:
	p2SString sValue;
};

class iCVar : public CVar
{
public:
	//This Constructor should never be used
	iCVar(){}
	
	iCVar(p2SString& sValue);
	iCVar(int iValue);

	void SetValueToInt(p2SString& value);
	int GetValueToInt();

private:
	int iValue;
};

class fCVar : public CVar
{
public:
	//This Constructor should never be used
	fCVar(){}

	fCVar(p2SString& sValue);
	fCVar(float fValue);


	void SetValueToFloat(p2SString& value);
	float GetValueToFloat();
private:
	float fValue;
};

#endif
