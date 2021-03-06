@echo off
if "%1"=="" %0 ..\game
goto a_%2
:a_
if not exist m:frontmap\con md m:frontmap
if exist m:frontmap\*.* del /q m:frontmap\*.bmp
pushd
%1\frontmap\
for %i in (*.bmp) (wfcq %i map3_3.bmp>NUL^echos .^if not errorlevel 1 cd.>m:frontmap\%i)
..\frbigmap\
for %i in (*.bmp) (wfcq %i ..\frontmap\map3_3.bmp>NUL^echos .^if not errorlevel 1 cd.>m:frontmap\%i)
popd
del /q m:frontmap\map3_3.bmp
:a_skipcmp
echo [files]>frontmap.fil
echo 141 	dir.dir		DIR_FRONTMAP>>frontmap.fil
echo 	map3_3.bmp FIL_M_WET>>frontmap.fil
echo //High res front end map layout generated by %0>h\frontmap.h
echo //You need to assign this static declaration into something...>>h\frontmap.h
echo {>>h\frontmap.h
echos {>>h\frontmap.h
set filnumcount=2
set y=0
set x=-2
echo.
:loop
set currfile=map%x%_%y%.bmp
if not exist %1\frontmap\%currfile% if not exist %1\frbigmap\%currfile% echos m
if not exist %1\frontmap\%currfile% if not exist %1\frbigmap\%currfile% echos FIL_M_WET>>h\frontmap.h
if not exist %1\frontmap\%currfile% if not exist %1\frbigmap\%currfile% goto donewater
if exist m:frontmap\%currfile% echos w
if exist m:frontmap\%currfile% echos FIL_M_WET>>h\frontmap.h
if exist m:frontmap\%currfile% del /q %1\frontmap\%currfile%
if exist m:frbigmap\%currfile% del /q %1\frbigmap\%currfile%
if exist m:frontmap\%currfile% goto donewater
echos l
echos FIL_M_%filnumcount%>>h\frontmap.h
echo 	%currfile%	FIL_M_%filnumcount%>>frontmap.fil
if %filnumcount GT 255 if exist %1\frontmap\%currfile move /q %1\frontmap\%currfile %1\frbigmap
if %filnumcount LT 256 if exist %1\frbigmap\%currfile move /q %1\frbigmap\%currfile %1\frontmap
set filnumcount=%@eval[%filnumcount +1]
if not %filnumcount==255 goto donewater
echo.>>frontmap.fil
echo 142	dir.dir		DIR_FRONTMAP2>>frontmap.fil
set filnumcount=%@eval[%filnumcount +2]
:donewater
echos `	`>>h\frontmap.h
set x=%@eval[%x+1]
if not %x==15 echos ,>>h\frontmap.h
if not %x==15 goto loop
echo.
set x=-2
set y=%@eval[%y+1]
echos }>>h\frontmap.h
if not %y==32 echo	, >>h\frontmap.h
if not %y==32 echos {>>h\frontmap.h
if not %y==32 goto loop
echo.>>h\frontmap.h
echo }>>h\frontmap.h

if  %filnumcount LT  255 echo 142	dir.dir		DIR_FRONTMAP2>>frontmap.fil
rem don't forget the thumbnail

echo 	thumbtop.bmp FIL_THUMBTOP>>frontmap.fil
echo 	thumbbot.bmp FIL_THUMBBOT>>frontmap.fil

rem generate file numbers for mid range map here 
rem I don't expect to get water optimisation

echo 	smap0_0.bmp	FIL_MIDMAP>>frontmap.fil
for %i in (1 2 3) echo 	smap%i_0.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_1.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_2.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_3.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_4.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_5.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_6.bmp>>frontmap.fil
for %i in (0 1 2 3) echo 	smap%i_7.bmp>>frontmap.fil

set filnumcount=
set currfile=
fmake2
