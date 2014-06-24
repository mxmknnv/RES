extern "C" 
{
#include "BigInt.h"
};


class LongNum 
{
public:
	LongNum();
	LongNum(const LongNum &);
	LongNum(int a);
	~LongNum();
	LongNum &operator =(const LongNum &);
	const LongNum operator +(LongNum &);
	const LongNum operator -(LongNum &);
	const LongNum operator *(LongNum &);
	const LongNum operator /(LongNum &);
	const LongNum operator %(LongNum &);
	const LongNum DegWithMod(LongNum &, LongNum &);
	bool operator ==(const LongNum &A);
	bool operator >(const LongNum &A);
	bool operator <(const LongNum &A);
	bool operator >=(const LongNum &A);
	bool operator <=(const LongNum &A);
	bool operator !=(const LongNum &A);
	bool operator ==(int a);
	bool operator >(int a);
	bool operator <(int a);
	bool operator >=(int a);
	bool operator <=(int a);
	bool operator !=(int a);	
	void Write(char *);
	void Read(char *);
private:
	BigInt Number;
};
