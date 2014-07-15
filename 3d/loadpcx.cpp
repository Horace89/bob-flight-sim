/*
* pcx.c -- pcx texture loader
* last modification: aug. 14, 2007
*
* Copyright (c) 2005-2007 David HENRY
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
* ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* gcc -Wall -ansi -lGL -lGLU -lglut pcx.c -o pcx
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loadpcx.h"

#include "myerror.h"

namespace PCX
{
	/* OpenGL texture info */
	/*
	struct gl_texture_t
	{
	GLsizei width;
	GLsizei height;

	GLenum format;
	GLint internalFormat;
	GLuint id;

	GLubyte *texels;
	};
	*/
	typedef unsigned char GLubyte;
	typedef unsigned __int16 uint16_t;
	typedef uint16_t GLushort;
#pragma pack(1)
	/* PCX header */
	struct pcx_header_t
	{
		GLubyte manufacturer;
		GLubyte version;
		GLubyte encoding;
		GLubyte bitsPerPixel;

		GLushort xmin, ymin;
		GLushort xmax, ymax;
		GLushort horzRes, vertRes;

		GLubyte palette[48];
		GLubyte reserved;
		GLubyte numColorPlanes;

		GLushort bytesPerScanLine;
		GLushort paletteType;
		GLushort horzSize, vertSize;

		GLubyte padding[54];
	};
#pragma pack(4)

	/*
	static void
	ReadPCX1bit(FILE *fp, const struct pcx_header_t *hdr,
	struct gl_texture_t *texinfo)
	{
	int y, i, bytes;
	int colorIndex;
	int rle_count = 0, rle_value = 0;
	GLubyte *ptr = texinfo->texels;

	for (y = 0; y < texinfo->height; ++y)
	{
	ptr = &texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
	bytes = hdr->bytesPerScanLine;

	// Decode line number y
	while (bytes--)
	{
	if (rle_count == 0)
	{
	if ((rle_value = fgetc(fp)) < 0xc0)
	{
	rle_count = 1;
	}
	else
	{
	rle_count = rle_value - 0xc0;
	rle_value = fgetc(fp);
	}
	}

	rle_count--;

	for (i = 7; i >= 0; --i, ptr += 3)
	{
	colorIndex = ((rle_value & (1 << i)) > 0);

	ptr[0] = hdr->palette[colorIndex * 3 + 0];
	ptr[1] = hdr->palette[colorIndex * 3 + 1];
	ptr[2] = hdr->palette[colorIndex * 3 + 2];
	}
	}
	}
	}

	static void
	ReadPCX4bits(FILE *fp, const struct pcx_header_t *hdr,
	struct gl_texture_t *texinfo)
	{
	GLubyte *colorIndex, *line;
	GLubyte *pLine, *ptr;
	int rle_count = 0, rle_value = 0;
	int x, y, c;
	int bytes;

	colorIndex = (GLubyte *)malloc(sizeof(GLubyte) * texinfo->width);
	line = (GLubyte *)malloc(sizeof(GLubyte) * hdr->bytesPerScanLine);

	for (y = 0; y < texinfo->height; ++y)
	{
	ptr = &texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];

	memset(colorIndex, 0, texinfo->width * sizeof(GLubyte));

	for (c = 0; c < 4; ++c)
	{
	pLine = line;
	bytes = hdr->bytesPerScanLine;

	// Decode line number y
	while (bytes--)
	{
	if (rle_count == 0)
	{
	if ((rle_value = fgetc(fp)) < 0xc0)
	{
	rle_count = 1;
	}
	else
	{
	rle_count = rle_value - 0xc0;
	rle_value = fgetc(fp);
	}
	}

	rle_count--;
	*(pLine++) = rle_value;
	}

	// Compute line's color indexes
	for (x = 0; x < texinfo->width; ++x)
	{
	if (line[x / 8] & (128 >> (x % 8)))
	colorIndex[x] += (1 << c);
	}
	}

	// Decode scan line.  color index => rgb
	for (x = 0; x < texinfo->width; ++x, ptr += 3)
	{
	ptr[0] = hdr->palette[colorIndex[x] * 3 + 0];
	ptr[1] = hdr->palette[colorIndex[x] * 3 + 1];
	ptr[2] = hdr->palette[colorIndex[x] * 3 + 2];
	}
	}

	// Release memory
	free(colorIndex);
	free(line);
	}
	*/
	static void
		ReadPCX8bits(const GLubyte *buffer, size_t sz, ImageMap_Desc * img)
	{
		int rle_count = 0, rle_value = 0;
		GLubyte magic;
		GLubyte *ptr;
		//fpos_t curpos;
		const GLubyte * curpos = buffer + sizeof(pcx_header_t);
		int y, bytes;
		struct pcx_header_t* header = (struct pcx_header_t*) buffer;

		/* The palette is contained in the last 769 bytes of the file */
		const size_t SZ_PAL = 768;
		magic = *(buffer + sz - SZ_PAL - 1);

		/* First byte must be equal to 0x0c (12) */
		bobassert(magic == 0x0c, "error: colormap's first byte must be 0x0c! " << magic);

		/* Read palette */
		img->palette = new GLubyte[SZ_PAL];
		memcpy(img->palette, buffer + sz - SZ_PAL, SZ_PAL);

		/* Read pixel data */
		img->body = (GLubyte *)
			malloc(sizeof(GLubyte) * img->w * img->h);

		for (y = img->h-1; y >= 0; --y)
		{
			ptr = img->body + ((img->h - (y + 1)) * img->w);
			bytes = header->bytesPerScanLine;

			/* Decode line number y */
			while (bytes--)
			{
				if (rle_count == 0)
				{
					if ((rle_value = *curpos++) < 0xc0)
					{
						rle_count = 1;
					}
					else
					{
						rle_count = rle_value - 0xc0;
						rle_value = *curpos++;
					}
				}

				rle_count--;

				*ptr++ = rle_value;
			}
		}
	}
	/*
	static void
	ReadPCX24bits(FILE *fp, const struct pcx_header_t *hdr,
	struct gl_texture_t *texinfo)
	{
	GLubyte *ptr = texinfo->texels;
	int rle_count = 0, rle_value = 0;
	int y, c;
	int bytes;

	for (y = 0; y < texinfo->height; ++y)
	{
	// For each color plane
	for (c = 0; c < 3; ++c)
	{
	ptr = &texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
	bytes = hdr->bytesPerScanLine;

	// Decode line number y
	while (bytes--)
	{
	if (rle_count == 0)
	{
	if ((rle_value = fgetc(fp)) < 0xc0)
	{
	rle_count = 1;
	}
	else
	{
	rle_count = rle_value - 0xc0;
	rle_value = fgetc(fp);
	}
	}

	rle_count--;
	ptr[c] = (GLubyte)rle_value;
	ptr += 3;
	}
	}
	}
	}
	*/
	/*
	static struct gl_texture_t *
	ReadPCXFile(const char *filename)
	{
	//	struct gl_texture_t *texinfo;
	struct pcx_header_t header;
	FILE *fp = NULL;
	int bitcount;

	// Open image file
	fp = fopen(filename, "rb");
	if (!fp)
	{
	fprintf(stderr, "error: couldn't open \"%s\"!\n", filename);
	return NULL;
	}

	// Read header file
	fread(&header, sizeof(struct pcx_header_t), 1, fp);
	if (header.manufacturer != 0x0a)
	{
	fprintf(stderr, "error: bad version number! (%i)\n",
	header.manufacturer);
	return NULL;
	}

	// Initialize texture parameters
	texinfo = (struct gl_texture_t *)
	malloc(sizeof(struct gl_texture_t));
	texinfo->width = header.xmax - header.xmin + 1;
	texinfo->height = header.ymax - header.ymin + 1;
	texinfo->format = GL_RGB;
	texinfo->internalFormat = 1;
	texinfo->texels = (GLubyte *)
	malloc(sizeof(GLubyte) * texinfo->width
	* texinfo->height * texinfo->internalFormat);

	bitcount = header.bitsPerPixel * header.numColorPlanes;

	// Read image data
	switch (bitcount)
	{

	case 1:
	// 1 bit color index
	ReadPCX1bit(fp, &header, texinfo);
	break;

	case 4:
	// 4 bits color index
	ReadPCX4bits(fp, &header, texinfo);
	break;

	case 8:
	// 8 bits color index
	ReadPCX8bits(fp, &header, texinfo);
	break;

	case 24:
	// 24 bits
	ReadPCX24bits(fp, &header, texinfo);
	break;

	default:
	// Unsupported
	fprintf(stderr, "error: unknown %i bitcount pcx files\n", bitcount);
	free(texinfo->texels);
	free(texinfo);
	texinfo = NULL;
	break;
	}

	fclose(fp);
	return texinfo;
	}
	*/

	void
		ReadPCXFile(const char *buffer, size_t sz, ImageMap_Desc * img)
	{
		//	struct gl_texture_t *texinfo;
		struct pcx_header_t& header = *(struct pcx_header_t *)buffer;
		//FILE *fp = NULL;
		int bitcount;

		if (header.manufacturer != 0x0a)
		{
			fprintf(stderr, "error: bad version number! (%i)\n",
				header.manufacturer);
			return;
		}

		/* Initialize texture parameters */
		img->w = header.xmax - header.xmin + 1;
		img->h = header.ymax - header.ymin + 1;
		//TRACING("w="<<img->w <<" h="<<img->h);
		bitcount = header.bitsPerPixel * header.numColorPlanes;

		/* Read image data */
		switch (bitcount)
		{
			/*
			case 1:
			// 1 bit color index
			ReadPCX1bit(fp, &header, texinfo);
			break;

			case 4:
			// 4 bits color index
			ReadPCX4bits(fp, &header, texinfo);
			break;
			*/
		case 8:
			/* 8 bits color index */
			ReadPCX8bits((const GLubyte *)buffer, sz, img);
			break;
			/*
			case 24:
			// 24 bits
			ReadPCX24bits(fp, &header, texinfo);
			break;
			*/
		default:
			/* Unsupported */
			fprintf(stderr, "error: unknown %i bitcount pcx files\n", bitcount);
			break;
		}

		//fclose(fp);
		//return texinfo;
	}


}