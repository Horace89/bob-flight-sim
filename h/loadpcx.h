#ifndef __LOADPCX__
#define __LOADPCX__

#include "Dosdefs.h"
#include "imagemap.h"
namespace PCX
{
	void	ReadPCXFile(const char *buffer, size_t sz, ImageMap_Desc * img);
}
#endif
