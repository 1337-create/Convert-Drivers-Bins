#include "bin_stage.h"

int main( int argc, char* argv[] )
{
	printf( "[+] bin_stage\n" );

	if ( argc < 3 )
	{
		printf( "[!] not enough arguments passed to binary\n" );
		return -1;
	}

	std::string infile  = get_absolute_path( argv[1] );
	std::string outfile = get_absolute_path( argv[2] );

	printf( "[+] in:  %s\n",  infile.c_str( ) );
	printf( "[+] out: %s\n", outfile.c_str( ) );

	std::ifstream input( infile, std::ios::binary );

	if ( !input )
	{
		printf( "[!] failed to open file\n" );
		return -1;
	}

	input.seekg( 0, std::ios::end );
	__int64 size = input.tellg( );

	printf( "[+] file size: %llu kb\n", size / 1024 );

	unsigned char* buffer = new unsigned char[size];

    input.seekg( 0, std::ios::beg );
    input.read( reinterpret_cast<char*>( buffer ), size );
	input.close( );

	// encrypt

	encrypt_forward_simple( buffer, size );

	// dump

	std::ofstream output( outfile, std::ios::binary );
	output.write( reinterpret_cast<const char*>( buffer ), size );
	output.close( );

	system( "pause" );
	return 0;
}

std::string get_absolute_path( LPCSTR lpszPath )
{
	char szBuffer[MAX_PATH + 1] = {0};
	GetFullPathName( lpszPath, MAX_PATH, szBuffer, NULL );

	return szBuffer;
}

void encrypt_forward_simple( unsigned char* buffer, __int64 size )
{
	const unsigned char communication_key[] = { 0xD0, 0xF2, 0x01, 0x12, 0xEF, 0x22 };

	for ( int i = 0; i < size; i++ )
		buffer[i] = buffer[i] ^ communication_key[i % ( sizeof( communication_key ) / sizeof( char ) )];
}