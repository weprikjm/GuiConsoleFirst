#include "p2SString.h"
#include <map>

class CVar
{
public: 
	CVar(const p2SString& nameIdentifier);

	int SetValueToInt(p2SString& command);
	float SetValueToFloat(p2SString& command);
	int GetValueToInt();
	const char* GetValueToString();

	p2SString& operator=(const p2SString& command);



private:
	p2SString sValue;
	int iValue;


};