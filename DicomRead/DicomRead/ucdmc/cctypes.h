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
/***************************************************************************
 *
 * Karl Franzens University, Graz
 * UCDMC99 DICOM Network Transport Libraries 
 * Version 0.1 Beta
 *
 * Technical Contact: gunter.zeilinger@kfunigraz.ac.at
 * Modifications signed with [gz]
 ***************************************************************************/

/*
 * Copyright (c) 1995 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Davis. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 */

/* CC Types */

#ifdef	SOLARIS
#	define	SYSTEM_V
#endif

#ifndef	WIN32
typedef unsigned	int	BOOL;
#endif
typedef unsigned	int		UINT;
typedef unsigned	short	UINT16;
#ifndef _BASETSD_H_ // MSVC 6.0 define: typedef unsigned int UINT32 [gz]
typedef unsigned	long	UINT32;
#endif
typedef unsigned	char	UINT8;
#ifndef	WIN32
typedef unsigned	char	BYTE;
#endif
typedef	signed		char	INT8;
typedef	signed		short	INT16;
#ifndef _BASETSD_H_ // MSVC 6.0 define: typedef int INT32 [gz]
typedef	signed		long	INT32;
#endif
#ifndef	WIN32
typedef	signed		int		INT;
#endif

#ifndef	TRUE
#define	TRUE	((UINT) 1)
#endif
#ifndef	FALSE
#define	FALSE	((UINT) 0)
#endif


#ifdef	LITTLE_ENDIAN
#undef	LITTLE_ENDIAN
#endif
#ifdef	BIG_ENDIAN
#undef	BIG_ENDIAN
#endif

#	define	LITTLE_ENDIAN	1
#	define	BIG_ENDIAN		2
#ifndef	NATIVE_ENDIAN
#	define	NATIVE_ENDIAN	LITTLE_ENDIAN
#endif
        
