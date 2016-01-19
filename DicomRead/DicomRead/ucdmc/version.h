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

/* Version related information
 *
 * This file contains the version number/Class that will be embedded not
 * only in the executable, but in the default PDU Service transfer Class.
 *
 */
#	define	IMPLEMENTATION_CLASS_STRING		"1.2.99.9.99.9.9999.9" // *GZ* "UCDMC/gcc2.5.8/DECMIPS/MHO"
#ifdef	WIN32
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/WIN32"
#else
#ifdef	ULTRIXMIPS
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/UMIPS"
#else
#ifdef	SOLARIS
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/SL5"
#else
#ifdef	MAC
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/MAC"
#else
#ifdef	SUNOSSPARC
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/SUNOS"
#else
#	define	IMPLEMENTATION_VERSION_STRING	"9.9S/OTHER"
#endif
#endif
#endif
#endif
#endif

