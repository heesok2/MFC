#pragma once

#define F_BLOCK_VER_UNKNOWN		0x0000
#define F_BLOCK_VER_100			0x0001

#define F_BLOCK_VERSION			F_BLOCK_VER_100 // latest version

enum FILE_BLOCK_TYPE
{
	F_BLOCK_TYPE_UNKNOWN	= 0,
	F_BLOCK_TYPE_INFO		= 1,
	F_BLOCK_TYPE_DPOOL		= 2,

	F_BLOCK_TYPE_EOF		= 9999,
};