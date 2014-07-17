//------------------------------------------------------------------------------
//Filename       error.h
//System
//Author         Martin Alderton
//Date           Fri 6 Oct 1995
//Description
//------------------------------------------------------------------------------
#ifndef	error_Included
#define	error_Included

//#ifndef CEDITOR												//ARM 11Apr97
//	#include	"display.h"										//DAW 15Apr96
//#endif															//ARM 11Apr97
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
								//DAW 15Apr96
class	 Error
{	//can't allow this to be half commented out!
		FILE	*logfile;										//JIM 01Aug96

	public:
		//char* exitmsg;
		static	char exit_string[2048];												//RJS 8Nov00
		Error(void);
		~Error(void );

//DeadCode JIM 02Jul96 		void Error::EmitSysErr(char *, ...);
		Error& ExitMode();
Error& Say(const char *, ...);
Error& SayAndQuit(const char *, ...);
		void Quit();
//#ifdef __MSVC__
//#define Quit
//#define SayAndQuit
//#endif
#ifdef __WATCOMC__
//#pragma	aux Quit			aborts;
//#pragma	aux SayAndQuit		aborts;
#endif
		#if	DEBUGGING
//DeadCode ARM 05Aug96 			void screenswap(Display *);
			void OpenLog(void );
			void WriteToLog(char *,...);
			void CloseLog(void );
			void KeyTrap(void );								//pd 01Nov95
			static	void	dummyproc(char*)	{;}
			static	void	dummyproc(char*,int)	{;}
			static	void	dummyproc(char*,int,int)	{;}
			static	void	dummyproc(char*,int,int,const char*)	{;}
			static	void	dummyproc(char*,int,int,int)	{;}
			static	void	dummyproc(char*,int,int,int,int)	{;}
			static	void	dummyproc(char*,int,int,int,const char*,int)	{;}
			static	void	dummyproc(char*,char*)	{;}
			static	void	dummyproc(char*,char*,char*)	{;}
			static	void	dummyproc(char*,char*,int,int)	{;}
			static	void	dummyproc(char*,char*,int)	{;}
			static	void	dummyproc(char*,int,char*)	{;}
		#endif

	private:

	protected:

};
extern	class Error	_Error;


//#ifdef	__WATCOMC__

/*#ifdef NDEBUG
 #define EmitSysErr ExitMode().SayAndQuit(__FILE__ "%i ",__LINE__),Error::dummyproc
#else*/
 #define EmitSysErr ExitMode().Say(__FILE__ ":%d\n",__LINE__).SayAndQuit
//#endif
	#define EmitWarning Say
 #define ReallyEmitSysErr  Say

// #define ReallyEmitSysErr ExitMode().Say(__HERE__ ": \n").SayAndQuit

/*#ifdef	assert
#pragma warnmsg("assert redefined")
#undef assert
#undef nassert
#endif*/

//DEADCODE DAW 26/04/99 #ifndef	assert

	#ifdef NDEBUG
		#define myassert(expr) {}
		#define bobassert(expr,str) {}
	#else
		#define	GOTASSERT ROWAN
		#define bobTrace _Error.Say
//		#define bobassert(expr,str) {if (expr) {} else {_Error.Say(#expr str);}}
//		#define myassert(expr) {if (expr) {} else {_Error.Say(#expr);}}
		#define bobassert(expr,str) {assert(expr);}
		#define myassert(expr) {assert(expr);}
	#endif

#endif
