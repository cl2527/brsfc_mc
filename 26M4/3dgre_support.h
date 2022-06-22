/*
 * GE Healthcare
 * Copyright (C) 2013 The General Electric Company
 *
 * 3dgre_support.h
 *
 * Language : ANSI C
 * Author   : Charles Michelich
 * Date     : Nov 1, 2013
 */

#ifndef _3dgre_support_h
#define _3dgre_support_h

/* Header files to satisfy types used in this file */
#include "stddef_ep.h"

/*-------------------- Defines and type definitions -------------------- */
/* SVBranch HCSDM00092046  Initial promote to support SBM */
typedef struct zy_exp {
    n16 view;
    n16 slice;
    n16 echo;
    n16 heat;
    n16 flags;
} ZY_EXPORT;

/* ----------------------Host and Target functions --------------------- */ 

/* ------------------------ Host only functions ------------------------ */
#ifdef HOST_TGT

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

STATUS
writeZyExport(const ZY_EXPORT *zy_export,
              const int len,
              const int debug_flag);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HOST_TGT */

/* ------------------------ Target only functions ---------------------- */
#ifdef MGD_TGT

STATUS
readZyExport(ZY_EXPORT *zy_export,
             const int len,
             const int debug_flag);

#endif /* MGD_TGT */

#endif /* _3dgre_support_h */
