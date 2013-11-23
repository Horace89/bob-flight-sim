# Microsoft Developer Studio Generated NMAKE File, Based on Rbutton.dsp
!IF "$(CFG)" == ""
CFG=RButton - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RButton - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RButton - Win32 Release" && "$(CFG)" != "RButton - Win32 Debug" && "$(CFG)" != "RButton - Win32 Unicode Debug" && "$(CFG)" != "RButton - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rbutton.mak" CFG="RButton - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RButton - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RButton - Win32 Release"

OUTDIR=\bob\Release\exe
INTDIR=\bob\Release\button
# Begin Custom Macros
OutDir=\bob\Release\exe
# End Custom Macros

ALL : "\bob\Release\exe\Rbutton.lic" "$(OUTDIR)\Rbutton.ocx" "\bob\Release\exe\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\all.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "..\..\Release\exe\RButton.tlb"
	-@erase "\bob\Release\exe\Rbutton.lic"
	-@erase "\bob\Release\exe\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "\bob\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /base:"0x10100000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Rbutton.pdb" /machine:I386 /def:".\RButton.def" /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\all.obj" \
	"$(INTDIR)\RButton.res"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\bob\Release\exe
TargetPath=\bob\Release\exe\Rbutton.ocx
InputPath=\bob\Release\exe\Rbutton.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

OUTDIR=\bob\Debug\exe
INTDIR=\bob\Debug\rbutton
# Begin Custom Macros
OutDir=\bob\Debug\exe
# End Custom Macros

ALL : "\bob\Debug\exe\Rbutton.lic" "$(OUTDIR)\Rbutton.ocx" "$(OUTDIR)\Rbutton.bsc" "\bob\Debug\exe\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\all.obj"
	-@erase "$(INTDIR)\all.sbr"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Rbutton.bsc"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "..\..\Debug\exe\RButton.tlb"
	-@erase "\bob\Debug\exe\Rbutton.lic"
	-@erase "\bob\Debug\exe\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /ZI /Od /I "\bob\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\all.sbr"

"$(OUTDIR)\Rbutton.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /base:"0x10100000" /subsystem:windows /dll /pdb:none /debug /machine:I386 /def:".\RButton.def" /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\all.obj" \
	"$(INTDIR)\RButton.res"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\bob\Debug\exe
TargetPath=\bob\Debug\exe\Rbutton.ocx
InputPath=\bob\Debug\exe\Rbutton.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\DebugU\Rbutton.lic" "$(OUTDIR)\Rbutton.ocx" "$(OUTDIR)\RButton.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\all.obj"
	-@erase "$(INTDIR)\getfile.obj"
	-@erase "$(INTDIR)\getresrc.obj"
	-@erase "$(INTDIR)\Getshadw.obj"
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\RButton.tlb"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.ilk"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "$(OUTDIR)\Rbutton.pdb"
	-@erase ".\DebugU\Rbutton.lic"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /base:"0x10100000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Rbutton.pdb" /debug /machine:I386 /def:".\RButton.def" /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" /pdbtype:sept 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\all.obj" \
	"$(INTDIR)\getfile.obj" \
	"$(INTDIR)\getresrc.obj" \
	"$(INTDIR)\Getshadw.obj" \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj" \
	"$(INTDIR)\RButton.res"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Rbutton.ocx
InputPath=.\DebugU\Rbutton.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : ".\ReleaseU\Rbutton.lic" "$(OUTDIR)\Rbutton.ocx" ".\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\all.obj"
	-@erase "$(INTDIR)\getfile.obj"
	-@erase "$(INTDIR)\getresrc.obj"
	-@erase "$(INTDIR)\Getshadw.obj"
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\RButton.tlb"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase ".\ReleaseU\Rbutton.lic"
	-@erase ".\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /base:"0x10100000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Rbutton.pdb" /machine:I386 /def:".\RButton.def" /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\all.obj" \
	"$(INTDIR)\getfile.obj" \
	"$(INTDIR)\getresrc.obj" \
	"$(INTDIR)\Getshadw.obj" \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj" \
	"$(INTDIR)\RButton.res"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Rbutton.ocx
InputPath=.\ReleaseU\Rbutton.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Rbutton.dep")
!INCLUDE "Rbutton.dep"
!ELSE 
!MESSAGE Warning: cannot find "Rbutton.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RButton - Win32 Release" || "$(CFG)" == "RButton - Win32 Debug" || "$(CFG)" == "RButton - Win32 Unicode Debug" || "$(CFG)" == "RButton - Win32 Unicode Release"
SOURCE=.\all.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "\bob\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\all.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /GX /ZI /Od /I "\bob\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\all.obj"	"$(INTDIR)\all.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\all.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\all.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\getfile.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\getfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\getfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Mfc\getresrc.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\getresrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\getresrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Mfc\Getshadw.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Getshadw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Getshadw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RButton.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RButton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RButton.odl

!IF  "$(CFG)" == "RButton - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o "NUL" /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o "NUL" /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o "NUL" /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o "NUL" /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RButton.rc

!IF  "$(CFG)" == "RButton - Win32 Release"


"$(INTDIR)\RButton.res" : $(SOURCE) "$(INTDIR)" "..\..\Release\exe\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "\bob\Release\exe" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"


"$(INTDIR)\RButton.res" : $(SOURCE) "$(INTDIR)" "..\..\Debug\exe\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "\bob\Debug\exe" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"


"$(INTDIR)\RButton.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "DebugU" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"


"$(INTDIR)\RButton.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "ReleaseU" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\rbuttonc.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rbuttonc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rbuttonc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\rbuttonp.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rbuttonp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Rbutton.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rbuttonp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RButton.lic

!IF  "$(CFG)" == "RButton - Win32 Release"

OutDir=\bob\Release\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"..\..\Release\exe\Rbutton.lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

OutDir=\bob\Debug\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"..\..\Debug\exe\Rbutton.lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(INTDIR)\Rbutton.lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"
<< 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(INTDIR)\Rbutton.lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"
<< 
	

!ENDIF 


!ENDIF 

