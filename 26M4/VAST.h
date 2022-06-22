/*
 * GE Medical Systems
 * Copyright (C) 2003 The General Electric Company
 * 
 * $Source: %M% $
 * $Revision: %I% $  $Date: %G% %U% $
 * 
 * Interface file for VAST.e.
 * 
 * Language : EPIC / ANSI C
 * Author   : Anila Lingamneni
 * Date     : 21-Jan-2003
 */
/* do not edit anything above this line */

/*
 Version      Date      Author      Description
------------------------------------------------------------------------------
 1.0       21-Jan-2003  ALP         Initial version.
 */

#ifndef VAST_h
#define VAST_h

/*
 * @host section
 */


/*
 * @rsp
 */

STATUS vast_gre_scancore( void );
STATUS vast_fiesta_scancore( void );
STATUS vast_ifir_scancore( void );

#endif /* VAST_h */
