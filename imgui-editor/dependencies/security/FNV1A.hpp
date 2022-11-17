#pragma once
#include <cstdint>
#include <cstring>

class FnvHash
{
	static const unsigned int FNV_PRIME = 16777619u;
	static const unsigned int OFFSET_BASIS = 2166136261u;

	template <unsigned int N>
	static consteval unsigned int fnvHashConst( const char( &str )[ N ], unsigned int I = N )
	{
		return I == 1 ? ( OFFSET_BASIS ^ str[ 0 ] ) * FNV_PRIME : ( fnvHashConst( str, I - 1 ) ^ str[ I - 1 ] ) * FNV_PRIME;
	}

	static unsigned int fnvHash( const char* str )
	{
		const size_t length = strlen( str ) + 1;
		unsigned int hash = OFFSET_BASIS;
		for ( size_t i = 0; i < length; ++i )
		{
			hash ^= *str++;
			hash *= FNV_PRIME;
		}
		return hash;
	}

	struct Wrapper
	{
		Wrapper( const char* str ) : str( str ) { }
		const char* str;
	};

	unsigned int hash_value;
public:
	FnvHash( Wrapper wrapper ) : hash_value( fnvHash( wrapper.str ) ) { }

	template <unsigned int N>
	consteval FnvHash( const char( &str )[ N ] ) : hash_value( fnvHashConst( str ) ) { }

	constexpr operator unsigned int( ) const { return this->hash_value; }
};
#define FNV1A(str) FnvHash(str)