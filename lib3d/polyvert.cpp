#include "lib3d.h"
#include "polyvert.h"

inline ULong FPNormToLong(const D3DVALUE p)
{
    if (p>=1.0f)		return 0xFFFFFFFF;
    else if (p<=0.f)	return 0x00000000;
    return F2UL_Round(p*D3DVALUE(ULong(0xFFFFFFFF)));
}


        void SPolygon::CalcTransZ( const D3DVALUE zFarPlaneInv, const D3DVALUE tZBias )
    {
        D3DVALUE ztot=0.f;
        SVertex* pp = pVertexList;
        for (int q=vertexcount; q>0; q--)
        {
//DeadCode JON 30Aug00 			ztot+=pp->sz;
            ztot+=pp->hw;
            pp=pp->pNext;
        }
//DeadCode JON 3Oct00 		ztot/=(D3DVALUE(vertexcount)*zFarPlane);
        ztot/=D3DVALUE(vertexcount);
        ztot+=tZBias;
        ztot*=zFarPlaneInv;
//TempCode JON 30Aug00 #ifndef NDEBUG
//TempCode JON 30Aug00 		if ( ztot < 0.0 || ztot > 1.0 )
//TempCode JON 30Aug00 			INT3;
//TempCode JON 30Aug00 #endif
        zbuffer=FPNormToLong(ztot);// - tZBias;
    }

        void SPolygon::SetTrans2DZ( ULong zBuffer2d )
    {
        zbuffer=zBuffer2d;
    }

    _R3DVERTEX3* SPolygon::CopyToVertexBuffer( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        switch ( projectType )
        {
        case PRE_PROJECTED:
            bufferPos = AlredyProjectedCopy( bufferPos, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT:
            bufferPos = SphereProjectCopy( bufferPos, cx, cy, sx, sy, 0.0 );
            break;
        case SPHERE_PROJECT_1:
            bufferPos = SphereProjectCopy( bufferPos, cx, cy, sx, sy, zFiddle );
            break;
        case SPHERE_PROJECT_2:
            bufferPos = SphereProjectCopy( bufferPos, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case SPHERE_PROJECT_BG:
            bufferPos = SphereProjectCopyBG( bufferPos, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT_DO_W:
            bufferPos = SphereProjectCopyW( bufferPos, cx, cy, sx, sy, zFactor );
            break;
        case STANDARD_PROJECT:
            bufferPos = StandardProjectCopy( bufferPos, cx, cy, sx, sy, 0.0 );
            break;
        case STANDARD_PROJECT_1:
            bufferPos = StandardProjectCopy( bufferPos, cx, cy, sx, sy, zFiddle );
            break;
        case STANDARD_PROJECT_2:
            bufferPos = StandardProjectCopy( bufferPos, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case STANDARD_PROJECT_BG:
            bufferPos = StandardProjectCopyBG( bufferPos, cx, cy, sx, sy );
            break;
        case STANDARD_PROJECT_DO_W:
            bufferPos = StandardProjectCopyW( bufferPos, cx, cy, sx, sy, zFactor );
            break;
        case PROJECT_2D:
            bufferPos = Project2DCopy(  bufferPos, cx, cy, sx, sy );
            break;
            // the 3dFX Fixex.
        case PRE_PROJECTED + W_16BIT_OFFSET:
            bufferPos = AlredyProjectedCopy( bufferPos, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopy_16( bufferPos, cx, cy, sx, sy, 0.0 );
            break;
        case SPHERE_PROJECT_1 + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopy/*_16*/( bufferPos, cx, cy, sx, sy, zFiddle );
            break;
        case SPHERE_PROJECT_2 + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopy/*_16*/( bufferPos, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case SPHERE_PROJECT_BG + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyBG/*_16*/( bufferPos, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT_DO_W + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyW_16( bufferPos, cx, cy, sx, sy, zFactor );
            break;
        case STANDARD_PROJECT + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16( bufferPos, cx, cy, sx, sy, 0.0 );
            break;
        case STANDARD_PROJECT_1 + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16( bufferPos, cx, cy, sx, sy, zFiddle );
            break;
        case STANDARD_PROJECT_2 + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16( bufferPos, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case STANDARD_PROJECT_BG+ W_16BIT_OFFSET:
            bufferPos = StandardProjectCopyBG_16( bufferPos, cx, cy, sx, sy );
            break;
        case STANDARD_PROJECT_DO_W + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopyW_16( bufferPos, cx, cy, sx, sy, zFactor );
            break;
        case PROJECT_2D + W_16BIT_OFFSET:
            bufferPos = Project2DCopy(  bufferPos, cx, cy, sx, sy );
            break;

            NODEFAULT;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::AlredyProjectedCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
//			*bufferPos++=curVert->getR3DVert(); // fill the vertex buffer with the points...
            memcpy( bufferPos++, curVert, sizeof( R3DVERTEX2 ) );
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyBG( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=            		curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyW( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }


    _R3DVERTEX3* SPolygon::SphereProjectCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyW( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyBG( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::Project2DCopy( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            bufferPos->x=			curVert->x*sx+cx;
            bufferPos->y=			curVert->y*sy+cy;
            bufferPos->z=			zDepth2d;
            bufferPos->rhw=			1.0f-zDepth2d;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }
// ------------------------- 3dfx fixes

    _R3DVERTEX3* SPolygon::SphereProjectCopyW_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopy_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyBG_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopy_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyW_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyBG_16( _R3DVERTEX3* bufferPos, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        SVertex* curVert = pVertexList;
        for (int i=vertexcount; i>0; i--)
        {
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
            bufferPos++;
            curVert=curVert->pNext;
        }
        return bufferPos;
    }

#ifndef _NO_VERTEX_SHARING_HDR
//       ********************************** INDEXED VERSIONS ******************************************
    _R3DVERTEX3* SPolygon::CopyToIndexdedVB( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
#define DO_INDEXED_COPY( arg )											\
{																		\
	SVertex* curVert = pVertexList;										\
	for (int i=vertexcount;i>0;i--)										\
	{																	\
		{ arg }															\
		*curPrimIndex++=												\
/*			curVert->vertIndex=*/WORD( bufferPos-bufferStart );			\
/*		curVert->uploadPass=0xFFFF;*/									\
		bufferPos++;													\
		curVert=curVert->pNext;											\
	}																	\
	return bufferPos;													\
}

#define DO_INDEXED_COPY_SHARING( arg )									\
{																		\
	SVertex* curVert = pVertexList;										\
	for (int i=vertexcount;i>0;i--)										\
	{																	\
		if ( curVert->identical == NULL ||								\
			 curVert->identical->uploadPass != bufferPass )				\
		{ /* upload this vertex...	*/									\
			{ arg }														\
			curVert->uploadPass = bufferPass;							\
			*curPrimIndex++=											\
				curVert->vertIndex =									\
					WORD( bufferPos-bufferStart );						\
			bufferPos++;												\
		} else															\
		{ /* this vertex is already uploaded...	  */					\
			*curPrimIndex++=											\
				curVert->vertIndex=										\
					curVert->identical->vertIndex;						\
			curVert->uploadPass = bufferPass;							\
		}																\
		curVert=curVert->pNext;											\
	}																	\
	return bufferPos;													\
}

        switch ( projectType )
        {
        case PRE_PROJECTED:
            bufferPos = AlredyProjectedCopyI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT:
            bufferPos = SphereProjectCopyI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, 0.0 );
            break;
        case SPHERE_PROJECT_1:
            bufferPos = SphereProjectCopyI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, zFiddle );
            break;
        case SPHERE_PROJECT_2:
            bufferPos = SphereProjectCopyI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case SPHERE_PROJECT_BG:
            bufferPos = SphereProjectCopyBGI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT_DO_W:
            bufferPos = SphereProjectCopyWI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, zFactor );
            break;
        case STANDARD_PROJECT:
            bufferPos = StandardProjectCopyI( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, 0.0 );
            break;
        case STANDARD_PROJECT_1:
            bufferPos = StandardProjectCopyI( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, zFiddle );
            break;
        case STANDARD_PROJECT_2:
            bufferPos = StandardProjectCopyI( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case STANDARD_PROJECT_BG:
            bufferPos = StandardProjectCopyBGI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case STANDARD_PROJECT_DO_W:
            bufferPos = StandardProjectCopyWI( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, zFactor );
            break;
        case PROJECT_2D:
            bufferPos = Project2DCopyI(  bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
            // the 3dFX Fixex.
        case PRE_PROJECTED + W_16BIT_OFFSET:
            bufferPos = AlredyProjectedCopyI( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopy_16I( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, 0.0 );
            break;
        case SPHERE_PROJECT_1 + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyI/*_16*/( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, zFiddle );
            break;
        case SPHERE_PROJECT_2 + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyI/*_16*/( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case SPHERE_PROJECT_BG + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyBGI/*_16*/( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case SPHERE_PROJECT_DO_W + W_16BIT_OFFSET:
            bufferPos = SphereProjectCopyW_16I( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy, zFactor );
            break;
        case STANDARD_PROJECT + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16I( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, 0.0 );
            break;
        case STANDARD_PROJECT_1 + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16I( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, zFiddle );
            break;
        case STANDARD_PROJECT_2 + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopy_16I( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, (zFiddle*2.0f) );
            break;
        case STANDARD_PROJECT_BG+ W_16BIT_OFFSET:
            bufferPos = StandardProjectCopyBG_16I( bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;
        case STANDARD_PROJECT_DO_W + W_16BIT_OFFSET:
            bufferPos = StandardProjectCopyW_16I( bufferPos, curPrimIndex, bufferStart, bufferPass, cx, cy, sx, sy, zFactor );
            break;
        case PROJECT_2D + W_16BIT_OFFSET:
            bufferPos = Project2DCopyI(  bufferPos, curPrimIndex, bufferStart, cx, cy, sx, sy );
            break;

            NODEFAULT;
        }
        return bufferPos;
    }

    _R3DVERTEX3* SPolygon::AlredyProjectedCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
//			*bufferPos=curVert->getR3DVert(); // fill the vertex buffer with the points...
            memcpy( bufferPos, curVert, sizeof( R3DVERTEX2 ) );
        )
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyBGI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyWI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }


    _R3DVERTEX3* SPolygon::SphereProjectCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY_SHARING(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyWI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY_SHARING (
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
//DeadCode JON 30Oct00 		SVertex* curVert = pVertexList;
//DeadCode JON 30Oct00 		for (int i=vertexcount;i>0;i--)
//DeadCode JON 30Oct00 		{
//DeadCode JON 30Oct00 			if ( curVert->identical == NULL ||
//DeadCode JON 30Oct00 				 curVert->identical->uploadPass != bufferPass )
//DeadCode JON 30Oct00 			{ // upload this vertex...
//DeadCode JON 30Oct00 				D3DVALUE rhw = 1.f/curVert->hw;
//DeadCode JON 30Oct00 				bufferPos->x=			curVert->x*rhw*sx+cx;
//DeadCode JON 30Oct00 				bufferPos->y=			curVert->y*rhw*sy+cy;
//DeadCode JON 30Oct00 				bufferPos->z=			curVert->z*zFactor;
//DeadCode JON 30Oct00 				bufferPos->rhw=			rhw;
//DeadCode JON 30Oct00 				// copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
//DeadCode JON 30Oct00 				memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
//DeadCode JON 30Oct00 				// more indexing stuff
//DeadCode JON 30Oct00 				curVert->uploadPass = bufferPass;
//DeadCode JON 30Oct00 				*curPrimIndex++=
//DeadCode JON 30Oct00 					curVert->vertIndex =
//DeadCode JON 30Oct00 						WORD( bufferPos-bufferStart );
//DeadCode JON 30Oct00 				bufferPos++;
//DeadCode JON 30Oct00 			} else
//DeadCode JON 30Oct00 			{ // this vertex is already uploaded...
//DeadCode JON 30Oct00 				*curPrimIndex++=
//DeadCode JON 30Oct00 					curVert->vertIndex=
//DeadCode JON 30Oct00 						curVert->identical->vertIndex;
//DeadCode JON 30Oct00 				curVert->uploadPass = bufferPass;
//DeadCode JON 30Oct00 			}
//DeadCode JON 30Oct00 			curVert=curVert->pNext;
//DeadCode JON 30Oct00 		}
//DeadCode JON 30Oct00 		return bufferPos;
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyBGI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::Project2DCopyI( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
            bufferPos->x=			curVert->x*sx+cx;
            bufferPos->y=			curVert->y*sy+cy;
            bufferPos->z=			zDepth2d;
            bufferPos->rhw=			1.0f-zDepth2d;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }
// ------------------------- 3dfx fixes

    _R3DVERTEX3* SPolygon::SphereProjectCopyW_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopy_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::SphereProjectCopyBG_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopy_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY_SHARING(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			(curVert->z*rhw)+zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyW_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const UWord bufferPass, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy, const D3DVALUE zFactor  ) const
    {
        DO_INDEXED_COPY_SHARING(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			curVert->z*zFactor;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }

    _R3DVERTEX3* SPolygon::StandardProjectCopyBG_16I( _R3DVERTEX3* bufferPos, WORD* &curPrimIndex, const _R3DVERTEX3* bufferStart, const D3DVALUE cx, const D3DVALUE cy, const D3DVALUE sx, const D3DVALUE sy ) const
    {
        DO_INDEXED_COPY(
            D3DVALUE rhw = 1.f/curVert->hw;
            bufferPos->x=			curVert->x*rhw*sx+cx;
            bufferPos->y=			curVert->y*rhw*sy+cy;
            bufferPos->z=			BACK_Z;
            bufferPos->rhw=			rhw*W_SCALE;
            // copy the rest of the vertex info ( 1 val for color, 1 for specular, 2 for each imapcoord pair );
            memcpy( &bufferPos->color, &curVert->color, (2+(2*2))*sizeof( D3DVALUE ) );
        )
    }
#endif //_NO_VERTEX_SHARING_HDR
