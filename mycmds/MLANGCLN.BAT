cd
rem if exist resource.h	del	resource.h
if exist resource.h move resource.h ..\mfc\
rem for %i in (res\*.*)	do del %i
rem for %i in (*.cur)	do del %i
rem @echo. >cleaned.flg

