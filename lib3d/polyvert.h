//------------------------------------------------------------------------------
//Filename       polyvert.h
//System
//Author         Paul.
//Date           Tue 4 Jan 2000
//Description
//------------------------------------------------------------------------------
#ifndef	POLYVERT_Included
#define	POLYVERT_Included

#include "lib3d.h"
class Lib3D;
class SVertex;
class R3DVERTEX;
class _R3DVERTEX3;
struct Material;

const D3DVALUE W_SCALE = 30.f;//00.f;
const D3DVALUE BACK_Z = 1.0f;

#define	DEFAULT_POLYVERT 0

const UByte PRE_PROJECTED			= 0;
const UByte SPHERE_PROJECT			= 1;
const UByte SPHERE_PROJECT_1		= 2;
const UByte SPHERE_PROJECT_2		= 3;
const UByte SPHERE_PROJECT_BG		= 4;
const UByte SPHERE_PROJECT_DO_W		= 5;
const UByte STANDARD_PROJECT		= 6;
const UByte STANDARD_PROJECT_1		= 7;
const UByte STANDARD_PROJECT_2		= 8;
const UByte STANDARD_PROJECT_BG		= 9;
const UByte STANDARD_PROJECT_DO_W	= 10;
const UByte PROJECT_2D				= 11;
const UByte W_16BIT_OFFSET			= 12; // must be the last one...

const D3DVALUE zFiddle = 4.0/D3DVALUE(ULong(1<<15));

//const D3DVALUE zFiddle = 0.0f;

typedef struct TNLSVertex
{
    R3DVERTEX r3dvert;
} TNLSVertex;


class SPolygon
{
public:
    static D3DVALUE zFactor;											//JON 27Sep00
    SPolygon *pNext;				//4
    SVertex* pVertexList;		//4
    Material	material;				//48
    UWord		vertexcount;			//2
    union 								//2
    {
        UWord		orcode;
        SWord		transMat;	// for tnl
    };
    union
    {
        UWord		andcode;			//2
        struct
        {
            SByte		projMat;	// for tnl
            UByte		lightMode;
        };

    };
    ULong		zbuffer;				//4
    UByte		projectType;			//1
    D3DVALUE	zDepth2d;

    void CalcTransZ( const D3DVALUE zFarPlaneInv, const D3DVALUE tZBias );

    void SetTrans2DZ( ULong zBuffer2d );

    _R3DVERTEX3* CopyToVertexBuffer( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;


    _R3DVERTEX3* AlredyProjectedCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* SphereProjectCopyBG( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* SphereProjectCopyW( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyW( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyBG( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* Project2DCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

// ------------------------- 3dfx fixes

    _R3DVERTEX3* SphereProjectCopyW_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopy_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopyBG_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* StandardProjectCopy_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyW_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyBG_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

#ifndef _NO_VERTEX_SHARING_HDR
//       ********************************** INDEXED VERSIONS ******************************************
    _R3DVERTEX3* CopyToIndexdedVB( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* AlredyProjectedCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* SphereProjectCopyBGI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* SphereProjectCopyWI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyWI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyBGI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* Project2DCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;
// ------------------------- 3dfx fixes

    _R3DVERTEX3* SphereProjectCopyW_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopy_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* SphereProjectCopyBG_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

    _R3DVERTEX3* StandardProjectCopy_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyW_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const;

    _R3DVERTEX3* StandardProjectCopyBG_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const;

#endif //_NO_VERTEX_SHARING_HDR
};

typedef struct SLine
{
    struct SLine *pNext;
    SVertex		vertices[2];
//	R3DVERTEX3	vertices[2];
    Material	material;
//DeadCode JON 15Nov00 	UWord		orcode;
//DeadCode JON 15Nov00 	UWord		andcode;
}
SLine;

typedef struct SPoint
{
    struct SPoint *pNext;
    SVertex		vertex;
//DeadCode JON 8Aug00 	Material	material;
}
SPoint;

#endif
