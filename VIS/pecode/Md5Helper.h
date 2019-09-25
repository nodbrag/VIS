#include <string>
#include <fstream>
#pragma once
typedef unsigned char byte;
typedef unsigned int uint32;

using std::string;
using std::ifstream;

class Md5Helper
{
public:
	Md5Helper();
	~Md5Helper();
	Md5Helper(const void* input, size_t length);
	Md5Helper(const string& str);
	Md5Helper(ifstream& in);
	void update(const void* input, size_t length);
	void update(const string& str);
	void update(ifstream& in);
	const byte* digest();
	string toString();
	void reset();

private:
	void update(const byte* input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const uint32* input, byte* output, size_t length);
	void decode(const byte* input, uint32* output, size_t length);
	string bytesToHexString(const byte* input, size_t length);

	/* class uncopyable */
	Md5Helper(const Md5Helper&);
	Md5Helper& operator=(const Md5Helper&);

private:
	uint32 _state[4];   /* state (ABCD) */
	uint32 _count[2];   /* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];   /* input buffer */
	byte _digest[16];   /* message digest */
	bool _finished;     /* calculate finished ? */

	static const byte PADDING[64];  /* padding for calculate */
	static const char HEX[16];
	enum { BUFFER_SIZE = 1024 };
};

