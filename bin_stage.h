#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>

#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <inttypes.h>

int main( int argc, char* argv[] );
std::string get_absolute_path( LPCSTR lpszPath );
void encrypt_forward_simple( unsigned char* buffer, __int64 size );