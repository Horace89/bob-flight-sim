//------------------------------------------------------------------------------
//Filename       math.h
//System
//Author         Jim Taylor
//Date           Thu 21 Sep 1995
//Description    Starter for 10... base 10 that is!
//------------------------------------------------------------------------------
#ifndef	MATH_Included
#define	MATH_Included

//stuff stolen from the system includes - why we have to use system file names - who knows
extern "C" {
extern double	pow( double __x, double __y );
extern double	exp( double __x );
}


#define	DEFAULT_MATH 0

#include "myangles.h"

#include	"mathasm.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

enum	RndVal	{	RndValMIN=0,
					RND10PC=6553,
					RND25PC=16384,
					RND33PC=21843,	//CSB 28/06/99
					RND50PC=32768,
					RND67PC=43686,	//CSB 28/06/99
					RND75PC=49152,
					RND90PC=58982,
					RND99PC=64880,//RDH 06Oct96
					RndValMAX=65535};

class	MathLib													//PD 29Nov95
{
static	UWord	bval,cval;
		UWord	rndcount;											//ARM 03Sep96
static	SWord	matan[],
				sincos_table[],
				tan_table[];
static	UWord	rndlookup[55],
				Days_in_Month[];
//DEADCODE DAW 08/05/00 static	UWord	SqrtLookup[];
void	sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang);
	void	FillFastSqrt();
public:
	enum	{MAX_RND=64};

//DeadCode AMM 19Oct100 	float	FastSqrt(float fl);
//DeadCode AMM 19Oct100 	UWord SavedRndCount;										//ARM 04Sep96

	MathLib ()
	{
		rndcount = 0;											//ARM 25Oct96
/* x0r		srand(time(NULL));
		size_t s = sizeof(rndlookup) / sizeof(UWord);
		for (size_t i = 0; i < s;i++)
		{
			rndlookup[i] = rand() ^ (rand() << 15);
		}
*/
		//DeadCode AMM 19Oct100 		MaxRndCount = 0;										//ARM 25Oct96
//DEADCODE DAW 08/05/00 		FillFastSqrt();
	}

	UWord GetRndCount () { return rndcount; }					//ARM 03Sep96
	void ResetRndCount () { rndcount = 0; }						//ARM 03Sep96
//DeadCode AMM 19Oct100 	UWord MaxRndCount;											//ARM 03Sep96
//DeadCode AMM 19Oct100 	UWord thisRndCount;											//ARM 03Sep96

//DeadCode AMM 19Oct100 	void TestRndCount ()										//ARM 03Sep96
//DeadCode AMM 19Oct100 	{															//ARM 03Sep96
//DeadCode AMM 19Oct100 		if (thisRndCount > MaxRndCount)							//ARM 03Sep96
//DeadCode AMM 19Oct100 			MaxRndCount = thisRndCount;							//ARM 03Sep96
//DeadCode AMM 19Oct100 	}															//ARM 03Sep96

	UWord GetRndLookUp (UWord n);						//ARM 04Sep96
	void SetRndLookUp (UWord n, UWord val);			//ARM 04Sep96

	UWord Getbval() { return bval; }							//ARM 04Sep96
	UWord Getcval() { return cval; }							//ARM 04Sep96

	void Setbval(UWord val) { bval = val; }					//ARM 04Sep96
	void Setcval(UWord val) { cval = val; }					//ARM 04Sep96

	enum	SignType {POSITIVE=0,NEGATIVE=-1,SIGN_ALIGN=0x7fff};
//DeadCode RDH 30Nov95 	void	sin_cos(ANGLES, SWord&, SWord& );
	ANGLES	arcsin(SWord);
//DeadCode JON 30Aug00 	ANGLES   arccos(SWord);

//	ANGLES	high_arc_sin(SWord );								//PD 23May96
//	ANGLES	high_arc_cos(SWord );								//PD 23May96

	ANGLES	ATan256(int index0to256)	{return Angles(matan[index0to256]);}
	SWord	tan(ANGLES);
//DeadCode JON 30Aug00 	SLong	hightan(ANGLES ang);

	ULong	distance3d(SLong,SLong,SLong);
	UWord	Distance_Unsigned(UWord,UWord);
ULong	a2iend(string&	srctxt);
ULong	a2iend(string&	srctxt,ULong& datalength);
void	high_sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang);
void	high_sin_cos(ANGLES ang, Float& sin_ang, Float& cos_ang);	  //CSB 09/11/99
int		K8sin128(int v)	{return sincos_table[(v>>3)&0x3ff]>>8;}
//int		K8cos128(int v)	{return sincos_table[(v>>3)&0x3ff]>>8;}  //x0r why it is the same as previous?
int		K8cos(int v)	{return sincos_table[(v>>3)&0x3ff];}
ANGLES	arctan(SLong dx, SLong dy);
ANGLES	HighArcTan(SLong, SLong);								//PD 04Jul96
//UWord   Distance_Unsigned(UWord dx, UWord dy);
void    InterceptHdg(ULong Wx1, ULong Wz1, ULong Wx2, ULong Wz2, ULong &dist, UWord &hdg);
ULong   Distance2d(SLong dx, SLong dy);
static ULong	DistAbsSum(SLong x,SLong y,SLong z=0,SLong w=0);
static Float	DistanceSquared(Float x,Float y)						{return (x*x+y*y);}
static Float	DistanceSquared(Float x,Float y,Float z)				{return (x*x+y*y+z*z);}
static Float	DistanceSquared(Float x,Float y,Float z,Float w)		{return (x*x+y*y+z*z+w*w);}
#ifndef __BCPLUSPLUS__
static inline	double	SquareRoot(double d)	{return sqrt(d);}
#endif
void	HighIntercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept);		//RDH 01Dec95
void	HighIntercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,ANGLES &HdgIntercept,ANGLES &PitchIntercept)
		{HighIntercept(deltax,deltay,deltaz,Range,
					(SWord&)HdgIntercept,(SWord&)PitchIntercept);}

void	Intercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept);		//RDH 01Dec95
void	Intercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,ANGLES &HdgIntercept,ANGLES &PitchIntercept)
		{Intercept(deltax,deltay,deltaz,Range,
					(SWord&)HdgIntercept,(SWord&)PitchIntercept);}

static	void 	Pos (SWord inputvar, UWord &posvar,SWord &signvar)		//JIM 02May96
{
	signvar=mathlib_w_getsign(inputvar);
	posvar=mathlib_w_applysign(inputvar,signvar);
}
static	void 	Pos (SLong inputvar, ULong &posvar,SLong &signvar)		//JIM 02May96
{
	signvar=mathlib_l_getsign(inputvar);
	posvar=mathlib_l_applysign(inputvar,signvar);
}
static	SWord 	GetSign (SWord inputvar)
{	return(mathlib_w_getsign(inputvar));}
static	SLong 	GetSign (SLong inputvar)
{	return(mathlib_l_getsign(inputvar));}
static	SWord 	GetSign (ANGLES inputvar)
{	return(mathlib_w_getsign(inputvar));}

static	UWord 	UseSign (SWord inputvar, SWord signvar)
{	return(mathlib_w_applysign(inputvar,signvar));}
static	SLong 	UseSign (SLong inputvar, SLong signvar)
{	return(mathlib_l_applysign(inputvar,signvar));}				//JIM 02May96

static	UWord	AbsSign(SWord	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}
static	SLong	AbsSign(SLong	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}
static	UWord	AbsSign(ANGLES	inputvar)
{	return(UseSign(inputvar,GetSign(inputvar)));}

SWord MonthFromDays (SWord daysinyear, SWord &daysinfullmonth,SWord leapyear );
void DateFromSecs (SLong secs, SWord &day, SWord &month, SWord &year);
SWord YearFromDays (SWord day, SWord &daysinfullyears, SWord &leapyear);
SWord YearFromSecs (SLong secs);
void TimeFromSecs (SLong secs, SWord &hr, SWord &mins);
void SunPosFromSecs(SLong secs, ANGLES& pos);					//PD 22Apr96


SWord DofCampFromSecs (SLong secs,SLong beginning);

RndVal	rnd();
RndVal	Query();

//DeadCode JIM 12Jul96 SWord	rnd(SWord	M)	{return (SWord) ( ((SLong)M*rnd()) >>16);}
SLong	rnd(SLong	M)	{return MULSHSIN(rnd(),M,16);}
Angles	rnd(ANGLES M)	{return (Angles)MULSHSIN(rnd(),M,16);}

SWord Cos_ArcSin(SWord);
};

inline	Angles	operator + (ANGLES a,RndVal b)	{return (Angles)((SWord)a+(SWord)b);}
//inline	Angles	operator += (ANGLES a,SLong b)  {return (Angles)(a=((SWord)a+(SWord)b));}

extern	MathLib	Math_Lib;										//PD 29Nov95
#ifndef	__BCPLUSPLUS__
/*
inline Float FPACos(Float x)	//returns arccos(x) in radians
{
	Float ans;

	_asm
	{
		fld1;
		fld x;
		fmul st,st(0);
		fld st;
		fsubp st(2),st;
		fdivp st(1),st;
		fsqrt;
		fld1;
		fpatan;
		fstp ans;
	}

	return ans;
}
*/
inline Float FPATan(Float opp, Float adj)
{
/*	Float	ans;
	_asm
	{
		fld		opp
			fld		adj
			fpatan
			fstp	ans
	}
	return ans;*/
//		return atan2(adj, opp);
		return atan2(opp, adj);
}

#endif

#endif

