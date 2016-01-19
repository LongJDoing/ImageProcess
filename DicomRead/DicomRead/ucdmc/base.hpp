/****************************************************************************
          Copyright (C) 1995, University of California, Davis

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND THE UNIVERSITY
          OF CALIFORNIA DOES NOT MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          owned by the University of California, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include this copyright notice.
****************************************************************************/

/***************************************************************************
 *
 * University of California, Davis
 * UCDMC DICOM Network Transport Libraries
 * Version 0.1 Beta
 *
 * Technical Contact: mhoskin@ucdavis.edu
 *
 ***************************************************************************/

// Base Class Include Header
#if	__MWERKS__
// Macintosh Compiling is a little different.  We don't pass in a system/endian
// on the "command line", hence, we detect the MetroWorks compiler.
#	define	MAC
#	define	NATIVE_ENDIAN	2
#endif
#ifdef	MAC
#	include	<stdio.h>
#	include	<string.h>
#	include	"macsock.h"
#else
extern	"C"
	{
#	include	<stdio.h>
#	include	<string.h>
	}
#endif
#ifdef	WIN32
#	include	<windows.h>
#	include	<winsock.h>
#	include	<share.h>
#else
#ifdef	MAC

#else
#	include	"unixsock.h"
#endif
#endif
#	include	"cctypes.h"
#	include	"safemem.h"
#	include	"util.h"
#	include	"array.thh"
#	include	"array.tcc"
#	include	"pqueue.thh"
#	include	"pqueue.tcc"
#	include	"farray.thh"
#	include	"buffer.thh"

// Sometimes it's easier to do something like this than guess
// for all the various systems.. 
#ifndef	SEEK_SET
#	define	SEEK_SET	0
#endif

