#include "include/Random123/philox.h"

/**
\brief	Generates a random number between 0 and 1.

\author	dcofer
\date	12/19/2012

\param	gid 		The global id for this thread. 
\param	iTimeSlice	The curent time slice being processed. 
\param	iSeed		The seed value to use when generating the random number. 

\return	random number.
**/
float Random(int gid, unsigned int iTimeSlice, unsigned int iSeed)
{
	philox4x32_key_t k = {{gid, iSeed, 0xfacebead, 0x12345678}};
	philox4x32_ctr_t c = {{iTimeSlice, 0xf00dcafe, 0xdeadbeef, 0xbeeff00d}};

	union {
		philox4x32_ctr_t c;
		int4 i;
	} u;

	u.c = philox4x32(c, k);
	unsigned int iRnd = (unsigned int) u.i.x;

	float fltRnd = iRnd*(1.0/4294967296.0);
	return fltRnd;
}


/**
\brief	Generates a random integer number between two values.

\author	dcofer
\date	12/19/2012

\param	gid 		The global id for this thread. 
\param	iTimeSlice	The curent time slice being processed. 
\param	iSeed		The seed value to use when generating the random number. 
\param	low 	The low value for the random number. 
\param	high	The high value for the random number. 

\return	random integer number.
**/
int RandomInt(int gid, unsigned int iTimeSlice, unsigned int iSeed, int low, int high )
{
	high++;
	return (int) (( abs(high-low) * Random(gid, iTimeSlice, iSeed) ) + low);
}


/**
\brief	Generates a random float number between two values.

\author	dcofer
\date	5/3/2011

\param	gid 		The global id for this thread. 
\param	iTimeSlice	The curent time slice being processed. 
\param	iSeed		The seed value to use when generating the random number. 
\param	low 	The low value for the random number. 
\param	high	The high value for the random number. 

\return	random float number.
**/
float RandomFloat(int gid, unsigned int iTimeSlice, unsigned int iSeed, float low, float high )
{return (float) (( fabs(high-low) * Random(gid, iTimeSlice, iSeed) ) + low);}
