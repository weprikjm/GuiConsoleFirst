#include "p2Log.h"
#include "j1App.h"
#include "j1Scene.h"
#include "Gui.h"

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
	char str[4096];
	strcpy_s(str, 4095 ,tmp_string2);
	str[4094] = '\0';

	//logInit += tmp_string2;
}