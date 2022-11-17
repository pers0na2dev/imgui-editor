#include "console.hpp"

void consoleMananger::init( )
{
    _old_out = GetStdHandle( STD_OUTPUT_HANDLE );
    _old_err = GetStdHandle( STD_ERROR_HANDLE );
    _old_in = GetStdHandle( STD_INPUT_HANDLE );

    ::AllocConsole( ) && ::AttachConsole( GetCurrentProcessId( ) );

    _out = GetStdHandle( STD_OUTPUT_HANDLE );
    _err = GetStdHandle( STD_ERROR_HANDLE );
    _in = GetStdHandle( STD_INPUT_HANDLE );

    SetConsoleMode( _out,
        ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT );

    SetConsoleMode( _in,
        ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
        ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE );

    SetConsoleTitleA( "imgui.tech" );
}
void consoleMananger::print( const char* fmt, ... )
{
    if ( !_out )
        return;

    char buf[ 1024 ];
    va_list va;

    va_start( va, fmt );
    _vsnprintf_s( buf, 1024, fmt, va );
    va_end( va );

    WriteConsoleA( _out, buf, static_cast< DWORD >( strlen( buf ) ), nullptr, nullptr );
}