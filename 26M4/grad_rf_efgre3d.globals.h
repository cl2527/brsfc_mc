/* used in fgre3d.e to calculate the min_seqcoil - for this
purpose it is assumed that all the gradient pulses involved
in spatial sat start from 0 and follow contiguously in the
gradient structures */
#define NUMXSAT 3
#define NUMYSAT 14
#define NUMZSAT 10

/* used in fgre3d.e to calculate the min_seqrfamp - for this
purpose it is assumed that all the rf pulses involved
in spatial sat start from 0 and follow contiguously in the
rf structure */
#define NUMRFSAT 12
#define RFSX1_SLOT 0
#define RFSX2_SLOT 1
#define RFSY1_SLOT 2
#define RFSY2_SLOT 3
#define RFSZ1_SLOT 4
#define RFSZ2_SLOT 5
#define RFSE1_SLOT 6
#define RFSE2_SLOT 7
#define RFSE3_SLOT 8
#define RFSE4_SLOT 9
#define RFSE5_SLOT 10
#define RFSE6_SLOT 11
#define RFCSSAT_SLOT 12
#define RF1_SLOT 13
#define RF0_SLOT 14
#define RF90_SLOT 15
#define RF180_SLOT 16
#define RFTIPUP_SLOT 17
#define HARD180_SLOT 18
#define RFGIR01_SLOT 19
#define RFGIR02_SLOT 20
#define RFFRIR_SLOT 21
#define RFFLP90_SLOT  22
#define RFFLP180_SLOT 23
#define RFFLP90R_SLOT 24
#define RF1TM_SLOT 25
#define RF_FREE2 26

#include "rf_navmonitor.globals.h"
#include "rf_Prescan.globals.h"

#define GXRFSX1_SLOT 0
#define GXRFSX2_SLOT 1
#define GKSX_SLOT 2
#define GXKCS_SLOT 3
#define GX1_SLOT 4
#define GXW_SLOT 5
#define GXWEX_SLOT 6
#define GX2_SLOT 7
#define GXW2_SLOT 8 
#define GXFC_SLOT 9 
#define GXFLPVENC_SLOT 10
#define GXFLPK_SLOT 11
/* CRT ************************************* Pascal 08/07/13 */
#define GXSPIRAL_SLOT 12  /* BMK 2007.06.26 */
#define GXSPOIL_SLOT 13   /* BMK 2007.06.26 */
#define GXSPOIL2_SLOT 14   /* BMK 2007.06.26 */
/*************************************************************/
#define GX_FREE 15 

#define GYRFSY1_SLOT 0
#define GYRFSY2_SLOT 1
#define GYKSE1_SLOT 2
#define GYKSE2_SLOT 3
#define GYKSE3_SLOT 4
#define GYKSE4_SLOT 5
#define GYKSE5_SLOT 6
#define GYKSE6_SLOT 7
#define GYKSX1_SLOT 8
#define GYKSX2_SLOT 9
#define GYKSY1_SLOT 10
#define GYKSY2_SLOT 11
#define GYKSZ1_SLOT 12
#define GYKSZ2_SLOT 13
#define GY1_SLOT 14
#define GY1R_SLOT 15
#define GYKCS_SLOT 16
#define GYFLPVENC_SLOT 17
#define GYFLPK_SLOT 18
#define GYFE1_SLOT 19
#define GYFE2_SLOT 20
/* CRT ************************************* Pascal 08/07/13 */
#define GYSPIRAL_SLOT 21  /* BMK 2007.06.26 */
#define GYSPOIL_SLOT 22   /* BMK 2007.06.26 */
#define GYSPOIL2_SLOT 23   /* BMK 2007.06.26 */
/*************************************************************/
#define GY_FREE 24 

#define GZRFSZ1_SLOT 0
#define GZRFSZ2_SLOT 1
#define GZRFSE1_SLOT 2
#define GZRFSE2_SLOT 3
#define GZRFSE3_SLOT 4
#define GZRFSE4_SLOT 5
#define GZRFSE5_SLOT 6
#define GZRFSE6_SLOT 7 
#define GKSZ_SLOT 8
#define GZKCS_SLOT 9
#define GZRF1_SLOT 10
#define GZCOMB_SLOT 11
#define GZP_SLOT 12
#define GZRF0_SLOT 13
#define GZRF0K_SLOT 14
#define GZKTIPUP_SLOT 15
#define GZ1_SLOT 16
#define GZK_SLOT 17
#define GZRFGIR01_SLOT 18
#define GZKGIR01_SLOT 19
#define GZRFGIR02_SLOT 20
#define GZKGIR02_SLOT 21
#define GZRFFRIR_SLOT 22 
#define GZKRFFRIR_SLOT 23 
#define GZFLPVENC_SLOT 24
#define GZFLPK_SLOT 25
#define GZ_FREE 26

#define MAX_RFPULSE RF_FREE
#define MAX_GRADX GX_FREE
#define MAX_GRADY GY_FREE
#define MAX_GRADZ GZ_FREE

