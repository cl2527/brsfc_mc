/*
 * GE Medical Systems
 * Copyright (C) 1998 The General Electric Company
 * 
 * $Source: %M% $
 * $Revision: %I% $  $Date: %G% %U% $
 * 
 * Interface file for Gate.eh.
 * 
 * Language : EPIC / ANSI C
 * Author   : Gabriel Fernandez
 * Date     : 19-Jan-1999
 */
/* do not edit anything above this line */

/*
 Version      Date      Author      Description
------------------------------------------------------------------------------
 1.0        19-Jan-1999 GFN         Initial version.
 */


#ifndef Gate_h
#define Gate_h

/*
 * @host
 */
STATUS GateCvinit( void );
STATUS GateCveval( int nSeg, float scanTimePerSeg );

/*
 * @pg
 */
STATUS GatePulsegen( int seqtime );

/*
 * @rsp
 */
STATUS GateRspInit( int options );
static long GetInfoFromSpu( void );
STATUS GateWaitForValidTrig( void );
#endif /* Gate_h */
