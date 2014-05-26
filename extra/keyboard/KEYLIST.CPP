//
// This module writes the key and joystick mapping to a binary file...
//
	
#include <cstdio>
typedef	unsigned short	UWord;
enum	FileNum;

const	int TOTALKEYBITFLAGS=768;

#define	SPECIAL_KEYMAPS	1
#include	"keymaps.h"
;

int main(int argc,char** argv)
{
	if (argv[1])
	{
		FILE* f = fopen(argv[1], "wb");
		if (f)
		{
			KeyMapping	*Debug3dMapTable = ThisKeyMapping;
			while (Debug3dMapTable->bitflag != 0)
				fwrite(Debug3dMapTable++, sizeof(KeyMapping), 1, f);
			fclose(f);
			return 0;
		}
	}
	else
	{
		printf("Usage: keyboard <outputfile_name>\n");
	}
	return 1;
}
