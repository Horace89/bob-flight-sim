// dxjoy2.cpp : Defines the entry point for the application.
//

//#include "stdafx.h"
#include "resource.h"
#include	<dinput.h>
#include	<stdio.h>
#include <conio.h>

#define MAX_LOADSTRING 100
char* FILENAME="DXJOY.LOG";
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
int	keydown=0;
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DXJOY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DXJOY2);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DXJOY2);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_DXJOY2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
unsigned long __stdcall	SearchDevices(   LPVOID lpParameter   ); 
FILE* stream=stdout;
HWND		ConsoleWindowDI;
HINSTANCE	ConsoleInstance;
HANDLE		ConsoleInput;
HANDLE		ConsoleOutput;
HWND		ConsoleWindowItself;
char* ConTitle="Jim's Joystick Test Program. Do not click on here!";
char* ConTitle2="Jim's Joystick Test Program. Press escape key (probably) to move on";


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "Click here to enable input!!!!", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   ConsoleWindowDI=hWnd;
   ConsoleInstance=hInstance;

	FreeConsole();
	AllocConsole();
	SetConsoleTitle(ConTitle);
	ConsoleInput=GetStdHandle(STD_INPUT_HANDLE);
	ConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);

	if (ConsoleOutput)
	{
		COORD c=GetLargestConsoleWindowSize(ConsoleOutput);
		SMALL_RECT r={1,1,c.X,c.Y};
		c.Y=1000;
		if (c.X>120)
			c.X=120;
		SetConsoleScreenBufferSize(ConsoleOutput,c);
	}
//DEADCODE MS 01/02/00 	GUITHREADINFO t;
//DEADCODE MS 01/02/00 	GetGUIThreadInfo(NULL,&t);
   MoveWindow(hWnd,0,0,600,0,FALSE);
   ShowWindow(hWnd, nCmdShow);
	Sleep(50);
	ConsoleWindowItself=FindWindow(NULL, ConTitle);
	RECT r;
	GetWindowRect(ConsoleWindowItself,&r);
	MoveWindow(ConsoleWindowItself,r.left ,r.top+30,r.right-r.left,r.bottom-r.top-30,FALSE);

//	SetForegroundWindow(ConsoleWindowID);

   UpdateWindow(hWnd);
   DWORD rv	;
	CreateThread(NULL,0,SearchDevices,NULL,NULL,&rv);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:

			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			
			
			break;
		case WM_CLOSE:
		   DestroyWindow(hWnd);
		   break;


		case WM_DESTROY:
			FreeConsole();
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			keydown=wParam;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


//These equates match a look-up for the actual values and printed strings
enum {	DL_FOREGROUND_EXCLUSIVE,	DL_BACKGROUND_EXCLUSIVE,
		DL_FOREGROUND_NONEXCLUSIVE,	DL_BACKGROUND_NONEXCLUSIVE,
		DLL_FOREGROUND_EXCLUSIVE,	DLL_BACKGROUND_EXCLUSIVE,
		DLL_FOREGROUND_NONEXCLUSIVE,DLL_BACKGROUND_NONEXCLUSIVE,
		DLL_PASTEND,

//Change these equates to change the order that the modes are tested for
		DL_START=		DL_FOREGROUND_EXCLUSIVE,
		DL_STOPBEFORE=	DLL_BACKGROUND_EXCLUSIVE
				};
//These equates are just convenience. They are not directly referenced
enum	{FULLHAT=36000,FULLJOY=65536,HAT2PC=720,JOY2PC=1300,JOY5PC=3300,JOY1PC=655,JOY01PC=65,

//These equates are used to limit how often a noisy changing input gets displayed
	JOY_RECOGNISED_MINDELTA=JOY5PC,		//Minimum delta displayed if offset can be named
	JOY_UNRECOGNISED_MINDELTA=JOY1PC,	//Minimum delta displayed if no name can be found for same offset
};

//These equates control the buffer length property and the DeviceObjectData array size
enum	{PROP_BUFFLEN=150,DOD_BUFFLEN=60};


char decimalbuffer[10]={0};
char*	Decimal(int i)
{
	int index=8;
	int v=i;
	if (i<0) v=-v;
	do{
		decimalbuffer[index--]=(v%10)+'0';
		v=v/10;
	}while (index && v);
	if (i<0)
		decimalbuffer[index]='-';
	else
		decimalbuffer[index]='+';
	return decimalbuffer+index;
}
char	linebuffer[10000]={0}; 

//THIS IS ALL TO DO WITH GENERATING FLUSHED STREAMED OUTPUT	WHICH MAXIMISES THE DISPLAY BEFORE A CRASH
//EACH PARAMETER TO FPUTSFLUSH WILL BE FLUSHED BEFORE THE NEXT PARAMETER IS PROCESSED IN ANY WAY.
//BLANK PARAMETERS WILL BE CONVERTED INTO NUL BY THE CRUDDYCRUD OPERATOR.
#pragma warning( disable : 4003 )
struct	Crud	{} CRUDDY_CRUD;
inline bool	operator +	(const char* s,Crud)	{return s!=NULL;}
inline bool	operator +	(int,Crud)	{return true;}
inline bool	operator +	(Crud)			{return false;}

inline const char* operator -	(const char* s,Crud)	{return s;}
inline const char* operator -	(int s,Crud)	{return Decimal(s);}
inline const char* operator -	(Crud)			{return NULL;}
//DEADCODE MS 01/02/00 BOOL WriteFile(
//DEADCODE MS 01/02/00   HANDLE hFile,                    // handle to file
//DEADCODE MS 01/02/00   LPCVOID lpBuffer,                // data buffer
//DEADCODE MS 01/02/00   DWORD nNumberOfBytesToWrite,     // number of bytes to write
//DEADCODE MS 01/02/00   LPDWORD lpNumberOfBytesWritten,  // number of bytes written
//DEADCODE MS 01/02/00   LPOVERLAPPED lpOverlapped        // overlapped buffer
//DEADCODE MS 01/02/00 );
DWORD written;
void	Fputs(const char* s,FILE* f)
{
	fputs(s,f);
}

#define	fputsflush1(stream,str)	if ( str + CRUDDY_CRUD)	{	\
		{WriteFile(ConsoleOutput,(str-CRUDDY_CRUD),strlen(str-CRUDDY_CRUD),&written,NULL);FlushFileBuffers(ConsoleOutput);}	\
		{Fputs(str-CRUDDY_CRUD,stream);fflush(stream);}	\
		{OutputDebugString(str-CRUDDY_CRUD);}			\
	}


#define	fputsflush(stream,string1,string2,string3,string4,string5,string6,string7,string8)\
{																		   \
	fputsflush1	(stream,string1)	\
	fputsflush1	(stream,string2)	\
	fputsflush1	(stream,string3)	\
	fputsflush1	(stream,string4)	\
	fputsflush1	(stream,string5)	\
	fputsflush1	(stream,string6)	\
	fputsflush1	(stream,string7)	\
	fputsflush1	(stream,string8)	\
}

LPDIRECTINPUT	DIdev;
int useddevices=0;
int	localusedaxes=0;
int	mouseusedaxes=0;
int	joyusedaxes=0;
int usedaxes=0;
struct	Devices
{
	char	devname[40];
	GUID	dev_uids;
	IDirectInputDevice	*dev1;
	IDirectInputDevice2	*dev2;
}	dev_uids[16];	
struct	Axes
{
	GUID guid;
	char	axisname[40];
	int		devnum;
	int		offset;
	DWORD	dwType;
	int		lastval;
}	dev_axes[2000];
int		max_devs=0;
int		max_axes=0;
int	key_bots,hat_tops,axis_tops,definition_tops;
int	Start_But,Start_Axis;
DIOBJECTDATAFORMAT	dataobjects[500];
int	max_dataobjects;


static	BOOL CALLBACK DIEnumDeviceButtonsProc(LPCDIDEVICEOBJECTINSTANCE ddoi,LPVOID pvRef)
{


	fputsflush(stream,"\"",ddoi->tszName,"\"\t");
	strcpy(dev_axes[max_axes].axisname,ddoi->tszName);
	dev_axes[max_axes].devnum=max_devs;
	dev_axes[max_axes].dwType=ddoi->dwType;
	max_axes++;
	return DIENUM_CONTINUE;

}
static	BOOL CALLBACK DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE ddoi,LPVOID pvRef)
{

	if (ddoi->dwType&(DIDFT_AXIS|DIDFT_POV))
	{
		fputsflush(stream,"Input: ",Decimal(localusedaxes),"\t\"",ddoi->tszName,"\"\t");
		if (ddoi->guidType==GUID_POV)
		{
			fputsflush(stream,"POV\n");
		}
		else 
		{
			fputsflush(stream,"Axis");
			if (ddoi->guidType==GUID_XAxis)
			{
				fputsflush(stream,"(Xp)\n");
			}
			else if (ddoi->guidType==GUID_RyAxis || ddoi->guidType==GUID_RzAxis)
			{
				fputsflush(stream,"(rX)\n");
			}
			else
			{
				fputsflush(stream,"(Y/Z)\n");
			}
		}
		localusedaxes++;
		strcpy(dev_axes[max_axes].axisname,ddoi->tszName);
		dev_axes[max_axes].devnum=max_devs;
		dev_axes[max_axes].dwType=ddoi->dwType;
		max_axes++;
	}
	else if (!(ddoi->dwType&DIDFT_BUTTON))
	{
		fputsflush(stream,"Other:",ddoi->tszName,"\tThis is ignored by Mig Alley\n");
	}

	return DIENUM_CONTINUE;
}

static BOOL CALLBACK DIEnumDevicesProc(const DIDEVICEINSTANCE *ddi,LPVOID pvRef)
{
	fputsflush(stream,"DEVICE",Decimal(useddevices));
	fputsflush(stream,"\tTYPE CODE:",Decimal(ddi->dwDevType),Decimal(ddi->dwDevType&255),Decimal((ddi->dwDevType>>8)&255),Decimal(ddi->dwDevType>>16),"\n");
	if ((ddi->dwDevType&255)!=DIDEVTYPE_KEYBOARD)
	{
		LPDIRECTINPUT	DIdev=(LPDIRECTINPUT)pvRef;
		fputsflush(stream,"Name:\"",ddi->tszInstanceName,"\"\t");
		fputsflush(stream,"ProdName:\"",ddi->tszProductName,"\"\n");
		fputsflush(stream,"GUID:\t",Decimal(ddi->guidInstance.Data1),Decimal(ddi->guidInstance.Data2),Decimal(ddi->guidInstance.Data3),Decimal(ddi->guidInstance.Data4[0]),Decimal(ddi->guidInstance.Data4[1]));
		fputsflush(stream,
			ddi->guidInstance.Data4[2],
			ddi->guidInstance.Data4[3],
			ddi->guidInstance.Data4[4],
			ddi->guidInstance.Data4[5],
			ddi->guidInstance.Data4[6],
			ddi->guidInstance.Data4[7]
			);

		fputsflush(stream,"\nMouse:",(((ddi->dwDevType&255)==DIDEVTYPE_MOUSE)?" Yes":" No"));
		LPDIRECTINPUTDEVICE dev;
		DIDEVCAPS			caps={sizeof(DIDEVCAPS)};
		fputsflush(stream,"\tDev ");
		DIdev->CreateDevice(ddi->guidInstance,&dev,NULL);
		fputsflush(stream,"Caps: ");
		dev->GetCapabilities(&caps);
		fputsflush(stream,"\tFF:",(((caps.dwFlags&DIDC_FORCEFEEDBACK)!=0)?" Yes":" No"));
		fputsflush(stream,"\tButtons:",Decimal(caps.dwButtons));
		fputsflush(stream,"\tHats:",Decimal(caps.dwPOVs));
		fputsflush(stream,"\tAxes:",Decimal(caps.dwAxes),"\n");
		localusedaxes=0;
		dev->EnumObjects(DIEnumDeviceObjectsProc,NULL,DIDFT_AXIS+DIDFT_POV);
		fputsflush(stream,"Buttons:",Decimal(caps.dwButtons),"\t");
		dev->EnumObjects(DIEnumDeviceButtonsProc,NULL,DIDFT_BUTTON);
		usedaxes+=localusedaxes;
		if ((ddi->dwDevType&255)==DIDEVTYPE_MOUSE)
			if (!mouseusedaxes)
				mouseusedaxes=localusedaxes;
			else
				;
		else
			if (!joyusedaxes)
				joyusedaxes=localusedaxes;
			else
				;
		fputsflush(stream,"\nAxes used:",Decimal(localusedaxes),Decimal(usedaxes),Decimal(mouseusedaxes),Decimal(joyusedaxes),"\n");
		fputsflush(stream,"Releasing...");
		dev->Release();
		fputsflush(stream,"Released.\tNext?\n");
		useddevices++;
	}
	else
	{
		fputsflush(stream,"Keyboard (skipped)");
		fputsflush(stream,"Name:\"",ddi->tszInstanceName,"\"\t");
		fputsflush(stream,"ProdName:\"",ddi->tszProductName,"\"\n");
		LPDIRECTINPUTDEVICE dev;
		DIDEVCAPS			caps={sizeof(DIDEVCAPS)};
		LPDIRECTINPUT	DIdev=(LPDIRECTINPUT)pvRef;
		DIdev->CreateDevice(ddi->guidInstance,&dev,NULL);
		fputsflush(stream,"Caps: ");
		dev->GetCapabilities(&caps);
		fputsflush(stream,"\tButtons:",Decimal(caps.dwButtons));
		dev->EnumObjects(DIEnumDeviceButtonsProc,NULL,DIDFT_BUTTON);
		fputsflush(stream,"...Releasing...");
		dev->Release();
		fputsflush(stream,"Released.\tNext?\n");
	}
	dev_uids[max_devs].dev_uids=ddi->guidInstance;
	strcpy(dev_uids[max_devs].devname,ddi->tszInstanceName);
	max_devs++;
	return DIENUM_CONTINUE;
}

int debug=-1;

static	BOOL CALLBACK DIEnumObjectsToDF(LPCDIDEVICEOBJECTINSTANCE ddoi,LPVOID pvRef)
{
	if (ddoi->guidType==GUID_Button || ddoi->guidType==GUID_Key)
	{	//_DIOBJECTDATAFORMAT
		if (ddoi->dwType!= dev_axes[Start_But].dwType)
		{
			fputsflush(stream,"ERROR!!! Button dwType mismatch: Expected \"",dev_axes[Start_But].axisname,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"                              Encountered \"",ddoi->tszName,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"Mig Alley does not check this. These 2 inputs may be confused. Please report this.\n");
		}
		dev_axes[Start_But].guid=ddoi->guidType;
  		dataobjects[max_dataobjects].pguid=0;//&dev_axes[Start_But].guid;
		dataobjects[max_dataobjects].dwOfs=key_bots;
		dataobjects[max_dataobjects].dwType=ddoi->dwType;//|DIDFT_ANYINSTANCE  ;//ddoi->dwType;
		dataobjects[max_dataobjects].dwFlags=0;
		dev_axes[Start_But].offset=key_bots;
		dev_axes[Start_But].lastval=0x10000000;
		key_bots++;
		max_dataobjects++;
		int dn=dev_axes[Start_But].devnum;
		do{	Start_But++;
		}while (Start_But<max_devs && (dev_axes[Start_But].devnum!=dn || (dev_axes[Start_But].dwType&DIDFT_BUTTON)==0));
	}
	else if (ddoi->guidType==GUID_POV)
	{
		if (ddoi->dwType!= dev_axes[Start_Axis].dwType)
		{
			fputsflush(stream,"ERROR!!! HAT dwType mismatch: Expected \"",dev_axes[Start_But].axisname,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"             Hat/Axis      Encountered \"",ddoi->tszName,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"Mig Alley does not check this. These 2 inputs may be confused. Please report this.\n");
		}

		hat_tops-=8;
		dev_axes[Start_Axis].guid=ddoi->guidType;
 		dataobjects[max_dataobjects].pguid=&dev_axes[Start_Axis].guid;
		dataobjects[max_dataobjects].dwOfs=hat_tops;
		dataobjects[max_dataobjects].dwType=ddoi->dwType;//|DIDFT_ANYINSTANCE  ;//ddoi->dwType;
		dataobjects[max_dataobjects].dwFlags=0;
		dev_axes[Start_Axis].offset=hat_tops;
		
		max_dataobjects++;
		int dn=dev_axes[Start_Axis].devnum;
		do{	Start_Axis++;
		}while (Start_Axis<max_devs && (dev_axes[Start_Axis].devnum!=dn || (dev_axes[Start_Axis].dwType&DIDFT_BUTTON)));
	}
	else
	{	//Assuming an axis... bad move...but the enumerate was limited.
		if (ddoi->dwType!= dev_axes[Start_Axis].dwType)
		{
			fputsflush(stream,"ERROR!!! AXIS dwType mismatch: Expected \"",dev_axes[Start_But].axisname,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"              Hat/Axis      Encountered \"",ddoi->tszName,"\" Types ",Decimal(ddoi->dwType),"\n");
			fputsflush(stream,"Mig Alley does not check this. These 2 inputs may be confused. Please report this.\n");
		}

		axis_tops-=4;
		dev_axes[Start_Axis].guid=ddoi->guidType;
 		dataobjects[max_dataobjects].pguid=&dev_axes[Start_Axis].guid;
		dataobjects[max_dataobjects].dwOfs=axis_tops;
		dataobjects[max_dataobjects].dwType=ddoi->dwType;//0x80000000|DIDFT_ANYINSTANCE|3  ;//ddoi->dwType;
		dataobjects[max_dataobjects].dwFlags=0;
		dev_axes[Start_Axis].offset=axis_tops;
		
		max_dataobjects++;
		int dn=dev_axes[Start_Axis].devnum;
		do{	Start_Axis++;
		}while (Start_Axis<max_devs && (dev_axes[Start_Axis].devnum!=dn || (dev_axes[Start_Axis].dwType&DIDFT_BUTTON)));
	}
	return DIENUM_CONTINUE;
}
int	cooplevels[]=
{DISCL_FOREGROUND+DISCL_EXCLUSIVE,DISCL_BACKGROUND+DISCL_EXCLUSIVE,DISCL_FOREGROUND+DISCL_NONEXCLUSIVE,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE,
 DISCL_FOREGROUND+DISCL_EXCLUSIVE,DISCL_BACKGROUND+DISCL_EXCLUSIVE,DISCL_FOREGROUND+DISCL_NONEXCLUSIVE,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE
};
char*	cooplevelstext[]=
{"DISCL_FOREGROUND+DISCL_EXCLUSIVE","DISCL_BACKGROUND+DISCL_EXCLUSIVE","DISCL_FOREGROUND+DISCL_NONEXCLUSIVE","DISCL_BACKGROUND+DISCL_NONEXCLUSIVE",
 "DISCL_FOREGROUND+DISCL_EXCLUSIVE","DISCL_BACKGROUND+DISCL_EXCLUSIVE","DISCL_FOREGROUND+DISCL_NONEXCLUSIVE","DISCL_BACKGROUND+DISCL_NONEXCLUSIVE"
};
int WaitKeyDown()
{
	keydown=0;
	int	toldyou=0;
	while (keydown==0)
	{
		FlushConsoleInputBuffer(ConsoleInput);
		if (GetForegroundWindow()!=ConsoleWindowDI)
		{
			SetForegroundWindow(ConsoleWindowItself);
			SetForegroundWindow(ConsoleWindowDI);
			if (GetForegroundWindow()!=ConsoleWindowDI)
				if (!toldyou++)
					fputsflush(stream,"\nPlease select the Top left title bar, then press a key. I can select the title bar in 15 seconds!")
				else
					fputsflush(stream,".");
		}
		Sleep(100);
	}
	if (toldyou)
		fputsflush(stream,"\n");
	return keydown;
}

void	TryKeySetup()
{	

	DIPROPDWORD	buffprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},PROP_BUFFLEN};
	fputsflush(stream,"Maximums:  Keys:",Decimal(key_bots),"  Hats:",Decimal(hat_tops),"  Axes:",Decimal(axis_tops),"...\n");
	int	rv;
	{for (int d=0;d<max_devs;d++)
		dev_uids[d].dev1=dev_uids[d].dev2=NULL;	
	}

	for (int d=0;d<max_devs;d++)
	{
		fputsflush(stream,dev_uids[d].devname,": ");
		for (int x=max_axes-1;x>=0;x--)
			if (dev_axes[x].devnum==d)
				if (dev_axes[x].dwType&DIDFT_BUTTON)
					Start_But=x;
				else
					Start_Axis=x;
		max_dataobjects=0;
		if ((rv=DIdev->CreateDevice(dev_uids[d].dev_uids,&dev_uids[d].dev1,NULL))==DI_OK)
		{
			int hres = dev_uids[d].dev1->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&dev_uids[d].dev2); 
			if (!SUCCEEDED(hres))
			{
				fputsflush(stream,"Created V1");
				rv=dev_uids[d].dev1->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);
				if (!SUCCEEDED(rv))
					switch (rv)
					{
					case DI_PROPNOEFFECT:  fputsflush(stream,"DIPROP_BUFFERSIZE DI_PROPNOEFFECT");break;
					case DIERR_INVALIDPARAM:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_INVALIDPARAM");break;
					case DIERR_NOTINITIALIZED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_NOTINITIALIZED");break;
					case DIERR_OBJECTNOTFOUND:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_OBJECTNOTFOUND");break;
					case DIERR_UNSUPPORTED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_UNSUPPORTED");break;
					default:
						fputsflush(stream,"DIPROP_BUFFERSIZE Error:",rv);
					}
				dev_uids[d].dev1->EnumObjects(DIEnumObjectsToDF,NULL,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,definition_tops,max_dataobjects,dataobjects};
				dev_uids[d].dev1->SetDataFormat(&dataform);
				int	trylevel=DL_START;
				dev_uids[d].dev1->SetCooperativeLevel(ConsoleWindowDI,cooplevels[trylevel]);
			 	rv=dev_uids[d].dev1->Acquire();
				if (!SUCCEEDED(rv))
				{
					int i;
					for (i=trylevel;i<DL_STOPBEFORE;i++)
					{
						dev_uids[d].dev1->SetCooperativeLevel(ConsoleWindowDI,cooplevels[i]);
						rv=dev_uids[d].dev1->Acquire();
						if (!SUCCEEDED(rv))
							fputsflush(stream,"\n Acquire FAILED with cooperative level",cooplevelstext[i])
						else
							break;
					}
					if (SUCCEEDED(rv))
						fputsflush(stream,"\n Acquire SUCCEEDED with cooperative level",cooplevelstext[i],".",
						"This may not be an actual problem when Mig Alley is running full-screen\n");	

				}
				if (!SUCCEEDED(rv))
				{
					fputsflush(stream," Acquire FAILED with ",Decimal(max_dataobjects)," objects. Code: ",Decimal(rv),". Where?\n");
					switch (rv)
					{
					case DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM\n");break;
					case DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED\n");break;
					case DIERR_OTHERAPPHASPRIO:	fputsflush(stream," DIERR_OTHERAPPHASPRIO\n");break;
					}
					for (int mdo=max_dataobjects-1;mdo;mdo--)
					{
						
						dataform.dwNumObjs=mdo;
						dev_uids[d].dev1->SetDataFormat(&dataform);
						rv=dev_uids[d].dev1->Acquire();
						if(SUCCEEDED(rv))	break;
					}
					if (SUCCEEDED(rv))
					{
						fputsflush(stream,"Acquire SUCCEEDED with ONLY ",Decimal(mdo)," Objects. Removed (reverse order):\n"
											"INDEX	OFFSET	TYPE	NAME\n");
						for (;mdo<max_dataobjects;mdo++)
							for (int search=dataobjects[mdo].dwOfs,i=0;i<max_axes;i++)
								if (dev_axes[i].offset==search)
									fputsflush(stream,Decimal(mdo),"\t",Decimal(search),"\t",Decimal(dataobjects[mdo].dwType),"\t\"",dev_axes[i].axisname,"\"\n");	
					}
				}
				else
					fputsflush(stream," Acquired\n");

			}
			else
			{
				dev_uids[d].dev1->Release();
				dev_uids[d].dev1=NULL;
				fputsflush(stream,"Created V2");
				max_dataobjects=0;
				dev_uids[d].dev2->EnumObjects(DIEnumObjectsToDF,NULL,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				rv=dev_uids[d].dev2->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);
				if (!SUCCEEDED(rv))
					switch (rv)
					{
					case DI_PROPNOEFFECT:  fputsflush(stream,"DIPROP_BUFFERSIZE DI_PROPNOEFFECT");break;
					case DIERR_INVALIDPARAM:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_INVALIDPARAM");break;
					case DIERR_NOTINITIALIZED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_NOTINITIALIZED");break;
					case DIERR_OBJECTNOTFOUND:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_OBJECTNOTFOUND");break;
					case DIERR_UNSUPPORTED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_UNSUPPORTED");break;
					default:
						fputsflush(stream,"DIPROP_BUFFERSIZE Error:",rv);
					}
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,definition_tops,max_dataobjects,dataobjects};
//DEADCODE DAW 25/01/00 				if (d==3)
//DEADCODE DAW 25/01/00 					dev_uids[d].dev2->SetDataFormat(&c_dfDIJoystick2 );
//DEADCODE DAW 25/01/00 				else
				dev_uids[d].dev2->SetDataFormat(&dataform);

				int	trylevel=DL_START;
				dev_uids[d].dev2->SetCooperativeLevel(ConsoleWindowDI,cooplevels[trylevel]);
				rv=dev_uids[d].dev2->Acquire();
				if (!SUCCEEDED(rv))
				{
					int i;
					for (i=trylevel;i<DL_STOPBEFORE;i++)
					{
						dev_uids[d].dev2->SetCooperativeLevel(ConsoleWindowDI,cooplevels[i]);
						rv=dev_uids[d].dev2->Acquire();
						if (!SUCCEEDED(rv))
							fputsflush(stream,"\n Acquire FAILED with cooperative level",cooplevelstext[i])
						else
							break;
					}
					if (SUCCEEDED(rv))
						fputsflush(stream,"\n Acquire SUCCEEDED with cooperative level",cooplevelstext[i],".\n",
						"This may not be an actual problem when Mig Alley is running full-screen\n");	

				}
				if (!SUCCEEDED(rv))
				{
					fputsflush(stream," Acquire FAILED with ",Decimal(max_dataobjects)," objects. Code: ",Decimal(rv),". Where?\n");
					switch (rv)
					{
					case DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM\n");break;
					case DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED\n");break;
					case DIERR_OTHERAPPHASPRIO:	fputsflush(stream," DIERR_OTHERAPPHASPRIO\n");break;
					default:	fputsflush(stream,rv); break;
					}
					for (int mdo=max_dataobjects-1;mdo;mdo--)
					{
						
						dataform.dwNumObjs=mdo;
						dev_uids[d].dev2->SetDataFormat(&dataform);
						rv=dev_uids[d].dev2->Acquire();
						if(SUCCEEDED(rv))	break;
					}
					if (SUCCEEDED(rv))
					{
						fputsflush(stream,"Acquire SUCCEEDED with ONLY ",Decimal(mdo)," Objects. Removed (reverse order):\n"
											"INDEX	OFFSET	TYPE	NAME\n");
						for (;mdo<max_dataobjects;mdo++)
							for (int search=dataobjects[mdo].dwOfs,i=0;i<max_axes;i++)
								if (dev_axes[i].offset==search)
									fputsflush(stream,Decimal(mdo),"\t",Decimal(search),"\t",Decimal(dataobjects[mdo].dwType),"\t\"",dev_axes[i].axisname,"\"\n");	
					}
				}
				else
					fputsflush(stream," Acquired\n");

			
			}
		}
		if(!SUCCEEDED(rv))		break;
	}

	if(!SUCCEEDED(rv))
		fputsflush(stream,"Aborted setup...\n")
	else
	{
		fputsflush(stream,"Please test each key button and axis.\nPress ",dev_uids[0].devname,":",dev_axes[0].axisname," to finish testing\n"
			"OFFSET TYPE\tNAME\t\t\tVALUE\n");
		int	remindcount=20;
		int	smoothingforsilly[1024];
		for (bool cont=true;cont;)
			for (int d=0;d<max_devs;d++)
			{
				Sleep(1);
				DIDEVICEOBJECTDATA	results[DOD_BUFFLEN];  // DI_OK or DI_BUFFEROVERFLOW.
				unsigned long resultcount=DOD_BUFFLEN;
				int rv1=DI_OK,rv2;
				if (dev_uids[d].dev1)			   
					rv2=dev_uids[d].dev1->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),results,&resultcount,0);
				else if (dev_uids[d].dev2)
				{
					rv1=dev_uids[d].dev2->Poll();	//DIERR_INPUTLOST  DIERR_NOTACQUIRED  DIERR_NOTINITIALIZED  

					rv2=dev_uids[d].dev2->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),results,&resultcount,0);
				}
	//DIERR_INPUTLOST DIERR_INVALIDPARAM  DIERR_NOTACQUIRED  DIERR_NOTBUFFERED  DIERR_NOTINITIALIZED  
				if (rv1!=DI_OK || rv2!=DI_OK)
				{
					fputsflush(stream,"Error reading device \"",dev_uids[d].devname,"\"\tPoll: ",rv1);
					switch (rv1)
					{
					case   DIERR_INPUTLOST:		fputsflush(stream," DIERR_INPUTLOST");break;
					case   DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM");break;
					case   DIERR_NOTACQUIRED:	fputsflush(stream," DIERR_NOTACQUIRED");break;
					case	DI_OK:				fputsflush(stream," OK");break;
					default:	fputsflush(stream,rv); break;
					}
					fputsflush(stream,"\tGetDeviceData: ",rv2);
					switch(rv2)
					{
					case   DIERR_INPUTLOST:		fputsflush(stream," DIERR_INPUTLOST");break;
					case   DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM");break;
					case   DIERR_NOTACQUIRED:	fputsflush(stream," DIERR_NOTACQUIRED");break;
					case   DIERR_NOTBUFFERED:	fputsflush(stream," DIERR_NOTBUFFERED");break;
					case   DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED");break;
					case   DI_BUFFEROVERFLOW:	fputsflush(stream," DI_BUFFEROVERFLOW");break;
					case	DI_OK:				fputsflush(stream," OK");break;
					default:	fputsflush(stream,rv); break;
					}
					fputsflush(stream,"\n");
					resultcount=0;
					if (rv2==DIERR_INPUTLOST || rv1==DIERR_INPUTLOST)
					{
						SetForegroundWindow(ConsoleWindowDI);
						Sleep(1000);
						if (dev_uids[d].dev2)
							dev_uids[d].dev2->Acquire();
						else
							dev_uids[d].dev1->Acquire();
					}
				}

				for (unsigned long i=0;i<resultcount;i++)
				{	bool found=false;
					int offset=results[i].dwOfs;
					if (offset==debug)
						debug=offset;
					for (int j=0;j<max_axes;j++)
						if (dev_axes[j].offset==offset)
						{
							found=true;
							int delta=dev_axes[j].lastval-(results[i].dwData&0xfffff);
							if (delta>JOY_RECOGNISED_MINDELTA || delta<-JOY_RECOGNISED_MINDELTA)
							{
								fputsflush(stream,offset," ",dev_axes[j].dwType,"\t= ");
								fputsflush(stream,dev_uids[dev_axes[j].devnum].devname,":",dev_axes[j].axisname,"\t",results[i].dwData,"\n");

								if (dev_axes[j].lastval!=0x10000000)
									dev_axes[j].lastval=results[i].dwData&0xfffff;
								if (j==0)
									cont=false;
								if (!--remindcount)
								{
									remindcount=20;
									fputsflush(stream,"Press ",dev_uids[0].devname,":",dev_axes[0].axisname," to finish testing\n");
								}
							}
						}
					if (!found)
					{
					   int delta=smoothingforsilly[offset]-(results[i].dwData&0xfffff);
						if (delta>JOY_UNRECOGNISED_MINDELTA || delta<-JOY_UNRECOGNISED_MINDELTA)
						{
							fputsflush(stream,Decimal(offset)," ",Decimal(dev_axes[j].dwType),"\t=  ",Decimal(results[i].dwData),"\tNO PROGRAMMED DEVICE MATCHES\n");
							smoothingforsilly[offset]=results[i].dwData&0xfffff;
						}

					}
				}
				
			}

	}
	for (int y=0;y<max_devs;y++)
	{
		if (dev_uids[y].dev1)
		{
			dev_uids[y].dev1->Unacquire();
			dev_uids[y].dev1->Release();
			dev_uids[y].dev1=NULL;
		}
		if (dev_uids[y].dev2)
		{
			dev_uids[y].dev2->Unacquire();
			dev_uids[y].dev2->Release();
			dev_uids[y].dev2=NULL;
		}
	}

}
//DEADCODE MS 01/02/00 If you want to know the: Use: 
//DEADCODE MS 01/02/00 Handle to a process HANDLE GetCurrentProcess (void); 
//DEADCODE MS 01/02/00 Identifier of a process DWORD GetCurrentProcessId (void); 
//DEADCODE MS 01/02/00 Handle of another process HANDLE OpenProcess (0, FALSE, 
//DEADCODE MS 01/02/00 DWORD dwProcessId); 
//DEADCODE MS 01/02/00 Process identifier for the process that created a particular window DWORD GetWindowThreadProcessId 
//DEADCODE MS 01/02/00 (HWND hWnd, LPWORD lpdwProcessId); 
//////////////////////////////////////////////////////////////////////
//
// Function:    TryStaticSetup
// Date:		02/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	TryStaticSetup()
{	

	DIPROPDWORD	buffprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},PROP_BUFFLEN};
	fputsflush(stream,"Maximums:  Keys:",Decimal(key_bots),"  Hats:",Decimal(hat_tops),"  Axes:",Decimal(axis_tops),"...\n");
	int	rv;
	{for (int d=0;d<max_devs;d++)
		dev_uids[d].dev1=dev_uids[d].dev2=NULL;	
	}

	for (int d=0;d<max_devs;d++)
	{
		fputsflush(stream,dev_uids[d].devname,": ");
		for (int x=max_axes-1;x>=0;x--)
			if (dev_axes[x].devnum==d)
				if (dev_axes[x].dwType&DIDFT_BUTTON)
					Start_But=x;
				else
					Start_Axis=x;
		max_dataobjects=0;
		if ((rv=DIdev->CreateDevice(dev_uids[d].dev_uids,&dev_uids[d].dev1,NULL))==DI_OK)
		{
			int hres = dev_uids[d].dev1->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&dev_uids[d].dev2); 
			if (!SUCCEEDED(hres))
			{
				fputsflush(stream,"Created V1");
//DEADCODE DAW 02/02/00 				rv=dev_uids[d].dev1->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);
				if (!SUCCEEDED(rv))
					switch (rv)
					{
					case DI_PROPNOEFFECT:  fputsflush(stream,"DIPROP_BUFFERSIZE DI_PROPNOEFFECT");break;
					case DIERR_INVALIDPARAM:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_INVALIDPARAM");break;
					case DIERR_NOTINITIALIZED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_NOTINITIALIZED");break;
					case DIERR_OBJECTNOTFOUND:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_OBJECTNOTFOUND");break;
					case DIERR_UNSUPPORTED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_UNSUPPORTED");break;
					default:
						fputsflush(stream,"DIPROP_BUFFERSIZE Error:",rv);
					}
				dev_uids[d].dev1->EnumObjects(DIEnumObjectsToDF,NULL,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,definition_tops,max_dataobjects,dataobjects};
				dev_uids[d].dev1->SetDataFormat(&dataform);
				int	trylevel=DL_START;
				dev_uids[d].dev1->SetCooperativeLevel(ConsoleWindowDI,cooplevels[trylevel]);
			 	rv=dev_uids[d].dev1->Acquire();
				if (!SUCCEEDED(rv))
				{
					int i;
					for (i=trylevel;i<DL_STOPBEFORE;i++)
					{
						dev_uids[d].dev1->SetCooperativeLevel(ConsoleWindowDI,cooplevels[i]);
						rv=dev_uids[d].dev1->Acquire();
						if (!SUCCEEDED(rv))
							fputsflush(stream,"\n Acquire FAILED with cooperative level",cooplevelstext[i])
						else
							break;
					}
					if (SUCCEEDED(rv))
						fputsflush(stream,"\n Acquire SUCCEEDED with cooperative level",cooplevelstext[i],".",
						"This may not be an actual problem when Mig Alley is running full-screen\n");	

				}
				if (!SUCCEEDED(rv))
				{
					fputsflush(stream," Acquire FAILED with ",Decimal(max_dataobjects)," objects. Code: ",Decimal(rv),". Where?\n");
					switch (rv)
					{
					case DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM\n");break;
					case DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED\n");break;
					case DIERR_OTHERAPPHASPRIO:	fputsflush(stream," DIERR_OTHERAPPHASPRIO\n");break;
					}
					for (int mdo=max_dataobjects-1;mdo;mdo--)
					{
						
						dataform.dwNumObjs=mdo;
						dev_uids[d].dev1->SetDataFormat(&dataform);
						rv=dev_uids[d].dev1->Acquire();
						if(SUCCEEDED(rv))	break;
					}
					if (SUCCEEDED(rv))
					{
						fputsflush(stream,"Acquire SUCCEEDED with ONLY ",Decimal(mdo)," Objects. Removed (reverse order):\n"
											"INDEX	OFFSET	TYPE	NAME\n");
						for (;mdo<max_dataobjects;mdo++)
							for (int search=dataobjects[mdo].dwOfs,i=0;i<max_axes;i++)
								if (dev_axes[i].offset==search)
									fputsflush(stream,Decimal(mdo),"\t",Decimal(search),"\t",Decimal(dataobjects[mdo].dwType),"\t\"",dev_axes[i].axisname,"\"\n");	
					}
				}
				else
					fputsflush(stream," Acquired\n");

			}
			else
			{
				dev_uids[d].dev1->Release();
				dev_uids[d].dev1=NULL;
				fputsflush(stream,"Created V2");
				max_dataobjects=0;
				dev_uids[d].dev2->EnumObjects(DIEnumObjectsToDF,NULL,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
//DEADCODE DAW 02/02/00 				rv=dev_uids[d].dev2->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);
				if (!SUCCEEDED(rv))
					switch (rv)
					{
					case DI_PROPNOEFFECT:  fputsflush(stream,"DIPROP_BUFFERSIZE DI_PROPNOEFFECT");break;
					case DIERR_INVALIDPARAM:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_INVALIDPARAM");break;
					case DIERR_NOTINITIALIZED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_NOTINITIALIZED");break;
					case DIERR_OBJECTNOTFOUND:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_OBJECTNOTFOUND");break;
					case DIERR_UNSUPPORTED:  fputsflush(stream,"DIPROP_BUFFERSIZE DIERR_UNSUPPORTED");break;
					default:
						fputsflush(stream,"DIPROP_BUFFERSIZE Error:",rv);
					}
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,definition_tops,max_dataobjects,dataobjects};
//DEADCODE DAW 25/01/00 				if (d==3)
//DEADCODE DAW 25/01/00 					dev_uids[d].dev2->SetDataFormat(&c_dfDIJoystick2 );
//DEADCODE DAW 25/01/00 				else
				dev_uids[d].dev2->SetDataFormat(&dataform);

				int	trylevel=DL_START;
				dev_uids[d].dev2->SetCooperativeLevel(ConsoleWindowDI,cooplevels[trylevel]);
				rv=dev_uids[d].dev2->Acquire();
				if (!SUCCEEDED(rv))
				{
					int i;
					for (i=trylevel;i<DL_STOPBEFORE;i++)
					{
						dev_uids[d].dev2->SetCooperativeLevel(ConsoleWindowDI,cooplevels[i]);
						rv=dev_uids[d].dev2->Acquire();
						if (!SUCCEEDED(rv))
							fputsflush(stream,"\n Acquire FAILED with cooperative level",cooplevelstext[i])
						else
							break;
					}
					if (SUCCEEDED(rv))
						fputsflush(stream,"\n Acquire SUCCEEDED with cooperative level",cooplevelstext[i],".\n",
						"This may not be an actual problem when Mig Alley is running full-screen\n");	

				}
				if (!SUCCEEDED(rv))
				{
					fputsflush(stream," Acquire FAILED with ",Decimal(max_dataobjects)," objects. Code: ",Decimal(rv),". Where?\n");
					switch (rv)
					{
					case DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM\n");break;
					case DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED\n");break;
					case DIERR_OTHERAPPHASPRIO:	fputsflush(stream," DIERR_OTHERAPPHASPRIO\n");break;
					default:	fputsflush(stream,rv); break;
					}
					for (int mdo=max_dataobjects-1;mdo;mdo--)
					{
						
						dataform.dwNumObjs=mdo;
						dev_uids[d].dev2->SetDataFormat(&dataform);
						rv=dev_uids[d].dev2->Acquire();
						if(SUCCEEDED(rv))	break;
					}
					if (SUCCEEDED(rv))
					{
						fputsflush(stream,"Acquire SUCCEEDED with ONLY ",Decimal(mdo)," Objects. Removed (reverse order):\n"
											"INDEX	OFFSET	TYPE	NAME\n");
						for (;mdo<max_dataobjects;mdo++)
							for (int search=dataobjects[mdo].dwOfs,i=0;i<max_axes;i++)
								if (dev_axes[i].offset==search)
									fputsflush(stream,Decimal(mdo),"\t",Decimal(search),"\t",Decimal(dataobjects[mdo].dwType),"\t\"",dev_axes[i].axisname,"\"\n");	
					}
				}
				else
					fputsflush(stream," Acquired\n");

			
			}
		}
		if(!SUCCEEDED(rv))		break;
	}

	if(!SUCCEEDED(rv))
		fputsflush(stream,"Aborted setup...\n")
	else
	{
		fputsflush(stream,"Please test each key button and axis.\nPress ",dev_uids[0].devname,":",dev_axes[0].axisname," to finish testing\n"
			"OFFSET TYPE\tNAME\t\t\tVALUE\n");
		int	remindcount=20;
		int	smoothingforsilly[1024];
		unsigned char	buffer[2048];
		for (bool cont=true;cont;)
			for (int d=0;d<max_devs;d++)
			{
				Sleep(1);
				DIDEVICEOBJECTDATA	results[DOD_BUFFLEN];  // DI_OK or DI_BUFFEROVERFLOW.
				unsigned long resultcount=DOD_BUFFLEN;
				int rv1=DI_OK,rv2;
				if (dev_uids[d].dev1)			   
					rv2=dev_uids[d].dev1->GetDeviceState(definition_tops,buffer);
				else if (dev_uids[d].dev2)
				{
					rv1=dev_uids[d].dev2->Poll();	//DIERR_INPUTLOST  DIERR_NOTACQUIRED  DIERR_NOTINITIALIZED  

					rv2=dev_uids[d].dev2->GetDeviceState(definition_tops,buffer);
				}
	//DIERR_INPUTLOST DIERR_INVALIDPARAM  DIERR_NOTACQUIRED  DIERR_NOTBUFFERED  DIERR_NOTINITIALIZED  
				if (rv1!=DI_OK || rv2!=DI_OK)
				{
					fputsflush(stream,"Error reading device \"",dev_uids[d].devname,"\"\tPoll: ",rv1);
					switch (rv1)
					{
					case   DIERR_INPUTLOST:		fputsflush(stream," DIERR_INPUTLOST");break;
					case   DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM");break;
					case   DIERR_NOTACQUIRED:	fputsflush(stream," DIERR_NOTACQUIRED");break;
					case	DI_OK:				fputsflush(stream," OK");break;
					default:	fputsflush(stream,rv); break;
					}
					fputsflush(stream,"\tGetDeviceData: ",rv2);
					switch(rv2)
					{
					case   DIERR_INPUTLOST:		fputsflush(stream," DIERR_INPUTLOST");break;
					case   DIERR_INVALIDPARAM:	fputsflush(stream," DIERR_INVALIDPARAM");break;
					case   DIERR_NOTACQUIRED:	fputsflush(stream," DIERR_NOTACQUIRED");break;
					case   DIERR_NOTBUFFERED:	fputsflush(stream," DIERR_NOTBUFFERED");break;
					case   DIERR_NOTINITIALIZED:	fputsflush(stream," DIERR_NOTINITIALIZED");break;
					case   DI_BUFFEROVERFLOW:	fputsflush(stream," DI_BUFFEROVERFLOW");break;
					case	DI_OK:				fputsflush(stream," OK");break;
					default:	fputsflush(stream,rv); break;
					}
					fputsflush(stream,"\n");
					resultcount=0;
					if (rv2==DIERR_INPUTLOST || rv1==DIERR_INPUTLOST)
					{
						SetForegroundWindow(ConsoleWindowDI);
						Sleep(1000);
						if (dev_uids[d].dev2)
							dev_uids[d].dev2->Acquire();
						else
							dev_uids[d].dev1->Acquire();
					}
				}
				for (int j=0;j<max_axes;j++)
					if (dev_axes[j].devnum==d)
					if ((dev_axes[j].lastval&0xffffff00)==0x10000000)
					{
						int newval=0x10000000+buffer[dev_axes[j].offset];
						if (newval!=dev_axes[j].lastval)
						{
							fputsflush(stream,dev_axes[j].offset," ",dev_axes[j].dwType,"\t= ");
							fputsflush(stream,dev_uids[dev_axes[j].devnum].devname,":",dev_axes[j].axisname,"\t",buffer[dev_axes[j].offset],"\n");
							dev_axes[j].lastval=newval;
							if (j==0)
								cont=false;
						}

					}
					else
					{
						int newval=buffer[dev_axes[j].offset]+(buffer[dev_axes[j].offset+1]<<8);
						int	delta=dev_axes[j].lastval-newval;
						if (delta>JOY_RECOGNISED_MINDELTA || delta<-JOY_RECOGNISED_MINDELTA)
						{
							dev_axes[j].lastval=newval;
							fputsflush(stream,dev_axes[j].offset," ",dev_axes[j].dwType,"\t= ");
							fputsflush(stream,dev_uids[dev_axes[j].devnum].devname,":",dev_axes[j].axisname,"\t",newval,"\n");
//DEADCODE DAW 02/02/00 							fputsflush(stream,dev_uids[dev_axes[j].devnum].devname,":",dev_axes[j].axisname,"=",newval," ");
						}
					}
//DEADCODE DAW 02/02/00 				fputsflush(stream,"\n");	
			}

	}
	for (int y=0;y<max_devs;y++)
	{
		if (dev_uids[y].dev1)
		{
			dev_uids[y].dev1->Unacquire();
			dev_uids[y].dev1->Release();
			dev_uids[y].dev1=NULL;
		}
		if (dev_uids[y].dev2)
		{
			dev_uids[y].dev2->Unacquire();
			dev_uids[y].dev2->Release();
			dev_uids[y].dev2=NULL;
		}
	}

}


unsigned long __stdcall	SearchDevices(   LPVOID lpParameter   )
{
	char* name="DXJOY.LOG";
	stream=fopen(name,"wt");
	fputsflush(stream,"	Rowan DX joystick testing program.\n\n"
				"This program is intended to access your DirectInput joystick in a similar way to the "
				"Rowan Simulation product Mig Alley.\n"
				"By running this program I hope you will be able to reproduce the problems that you and "
				"various other users have experienced with the Mig Alley Joystick interface, and from "
				"this information I am optimistic that a fix can follow.\n\n"
				"STAGE 1] This first stage simply enquires from the hardware what features are present.\n"
				"Please take a moment to check that the reported numbers of buttons, hats, and axes "
				"matches what you expected to see.\n"
				"Note that some advanced joysticks quote extra buttons to allow axes to be mapped as buttons.\n\n"
				"Press any key (on keyboard) to continue...\n\n");	WaitKeyDown();
//DEADCODE MS 01/02/00 	DirectInputCreate(ConsoleInstance,DIRECTINPUT_VERSION,&DIdev,NULL);
	DirectInputCreate(GetModuleHandle(NULL),DIRECTINPUT_VERSION,&DIdev,NULL);
	fputsflush(stream,"\nKEYBOARD DEVICES (DIDEVTYPE_KEYBOARD): Mig Alley uses the FIRST keyboard device.\n");
	DIdev->EnumDevices(DIDEVTYPE_KEYBOARD,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	fputsflush(stream,"Press any key (on keyboard).\n");	WaitKeyDown();
	fputsflush(stream,"\nMOUSE DEVICES (DIDEVTYPE_MOUSE):\n\n");
	DIdev->EnumDevices(DIDEVTYPE_MOUSE,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	fputsflush(stream,"Press any key (on keyboard).\n");	WaitKeyDown();
	fputsflush(stream,"\nJOYSTICK DEVICES (DIDEVTYPE_JOYSTICK):\n\n");
	DIdev->EnumDevices(DIDEVTYPE_JOYSTICK,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	fputsflush(stream,"\nOTHER DEVICES (DIDEVTYPE_DEVICE): CRASHES DX 6 IF OTHER USB HARDWARE ATTACHED!\nBecause of this, Mig Alley v 1.02 & 1.1 do not poll this class of equipment.\n");
	fputsflush(stream,"Press ESCAPE KEY TO BYPASS, Or any key (on keyboard) to test.\n\n");
	if (WaitKeyDown()!=VK_ESCAPE)
		DIdev->EnumDevices(DIDEVTYPE_DEVICE,DIEnumDevicesProc,DIdev,DIEDFL_ATTACHEDONLY);
	else
		fputsflush(stream,"Skipped...\n");
	fputsflush(stream,"No more devices\nReleasing DI...");
	fputsflush(stream,"Scanning complete.\n");
	strcpy(dev_axes[max_axes].axisname,"PAST END OF LIST");
	fputsflush(stream,"\nSTAGE 2]	This second set of tests actually sets up the hardware for reading.\n"
					"Some users have reported a 'syserr' when acquiring the devices.\n"
					"Others have reported hats not working or generating an incorrect result.\n"
					"I have a number of different ways I can reorganise the code which may help some users.\n"
					"This code will try some of them after demonstrating the Mig Alley arrangement (going wrong).\n"
					"Note that this test program should be run with no other programs running,\notherwise it cannot find the active window reliably.\n"
					);
	DWORD time;
#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
	SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT,0,&time,0);
	//SPI_GETDRAGFULLWINDOWS

	key_bots=0x80,hat_tops=300,axis_tops=0x500,definition_tops=0x500;
	fputsflush(stream,"\nTRY 1: Mig Alley as released: \n"
						"The only difference is that all keys are grouped together, rather than grouped by device\n");
	fputsflush(stream,"Press any key (on keyboard) to continue...\n");	WaitKeyDown();
	TryKeySetup();

	key_bots=0x80,hat_tops=300,axis_tops=0x500,definition_tops=0x500;
	fputsflush(stream,"TRY 2: Using DI::GetDeviceState() instead of DI::GetDeviceData(). Much slower!\n"
					"If this works, and in try 1 some axes did not input properly,\n"
					"then this indicates a bug with the joystick drivers support for GetDeviceData() in DirectX 7\n"
					"Please tell me, and contact your joystick vendor for an update.\n"
					"Press any (keyboard) key: \n"); WaitKeyDown();
	TryStaticSetup();


	key_bots=0x80,hat_tops=350,axis_tops=0x500,definition_tops=0x500;
	fputsflush(stream,"TRY 3: Mig Alley as relaeased: Demonstrates 3rd joystick hat Rowan bug (odd index of integer field).\n"
						"This test will reject all hats, but the bug should only occur in-game if your mouse has a POV hat,\n"
						"or you have 3/5/7 joysticks all enabled on the config screen, and the 3rd/5th/7th joystick has hats.\n"
						"Press any (keyboard) key: \n"); WaitKeyDown();
	TryKeySetup();


	key_bots=0x80,hat_tops=0x200,axis_tops=0x400,definition_tops=0x400;
	fputsflush(stream,"TRY 4: Compacted hats design to fix 3rd hat bug:\n"
					"256 codes are reserved for main keyboard, then 40 buttons each per joystick/mouse,\n"
					"and 8 per hat, allowing 5 joysticks with 6 hats total.\n"
					"Then there is allowance for 64 in-game analogue inputs using 256 codes each for hat and joystick aliasing\n"
					"Press any (keyboard) key:\n"); WaitKeyDown();
	TryKeySetup();

	key_bots=0x80,hat_tops=0x200,axis_tops=0x300,definition_tops=0x300;
	fputsflush(stream,"TRY 5: Superpacted hats design to fix high indexes:\n"
					"Some joystick drivers may not like the very high indexes I am setting up.\n"
					"This setting is the lowest indexing arrangement I can imagine working with our code\n"
					"256 codes are reserved for main keyboard, then 40 buttons each per joystick/mouse,\n"
					"and 8 per hat, allowing 5 joysticks with 6 hats total.\n"
					"Then there is allowance for 32 in-game analogue inputs using 128 codes each for hat and joystick aliasing\n"
					"Press any (keyboard) key:\n"); WaitKeyDown();
	TryKeySetup();

	key_bots=0x00,hat_tops=0x0B0,axis_tops=0x0100,definition_tops=0x100;
	fputsflush(stream,"Try 6: Is DirectX interface working generally with very low numbers? Press any (keyboard) key:\n");	WaitKeyDown();
	TryKeySetup();



	DIdev->Release();


	fputsflush(stream,"A log has been written to the file ",name,". You can contact me as JIM@ROWAN.CIX.CO.UK\n");
	fputsflush(stream,"Scanning complete. Press any key (on keyboard).\n");WaitKeyDown();
	fclose (stream);
	SendMessage(ConsoleWindowDI,WM_CLOSE,0,0);
	GetLastError();

	return (0);
}

