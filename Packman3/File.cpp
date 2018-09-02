#include <fstream>
#include <iostream>
#include <Windows.h>
#include "File.h"

using namespace std;

File::File( const char* filename ) :
mSize( 0 ),
mData( 0 )
{
	ifstream f( filename, ifstream::binary );
	if(f)
	{
		f.seekg( 0, ifstream::end );
		mSize = static_cast<int>( f.tellg() );
		f.seekg( 0, ifstream::beg );
		mData = new char[ mSize ];
		f.read( mData, mSize );
		f.close();
	}
	else
	{
		OutputDebugString( "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n" );
	}
}

File::~File()
{
	delete[] mData;
	mData = 0;
}

// �t�@�C���̃T�C�Y���擾
int File::size() const
{
	return mSize;
}

// �t�@�C����̃f�[�^���ۂ��Ǝ擾
char* File::data() const
{
	return mData;
}