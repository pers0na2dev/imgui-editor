#pragma once

#include <memory>

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>

class consoleMananger
{
public:
	void init( );
	void print( const char* fmt, ... );
private:
	HANDLE _out = NULL, _old_out = NULL;
	HANDLE _err = NULL, _old_err = NULL;
	HANDLE _in = NULL, _old_in = NULL;
};

inline auto conManager = std::make_shared<consoleMananger>();