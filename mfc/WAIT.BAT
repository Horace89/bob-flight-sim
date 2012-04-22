:wait 
delay 
if exist \BOB\src\bferr.txt goto end
if not exist \BOB\src\bfieldsm.fil goto wait
:end
