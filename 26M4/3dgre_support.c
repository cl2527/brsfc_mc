/*
 * GE Healthcare
 * Copyright (C) 2013 The General Electric Company
 *
 * 3dgre_support.c
 *
 * ANSI C support functions for 3D Gradient Echo family of PSDs.
 * Note that multiple PSDs use these functions.
 *
 * These function should not use any global variables.  If a function uses
 * any global variables, including CVs, ipgexport variables, and
 * host/tgt global variables, do NOT put the function in this file.
 *
 * The goal of this source file to provide a place for clean, well scoped,
 * functions to be defined.  By not including the #include's with the EPIC
 * globals, the compiler will enforce not accidentally using a global
 * variable.
 *
 * Language : ANSI C
 * Author   : Charles Michelich
 * Date     : Nov 1, 2013
 *
 */

/*
 * Comments:
 * Date (dd mmm CCYY) Author (or Initials) Date
 * Comment
 *
 * 01 Nov 2013
 * Separated read and write of ZY export from 3dphcon.e and efgre3d_support.c
 * into common file for 3D Gradient Echo family.
 * Refactored to remove use of malloc and add checksum verification.
 *
 */

/* ----------------------Host and Target functions --------------------- */

/* Local header files */
#include <string.h>
#include "geCrcLib.h"
#include "3dgre_support.h"

/* --- For writeZyExport() and readZyExport() --- */
/* Filename for transfering zy_export table from host to target */
#ifdef SIM
static const char zy_export_filename[] = "./zy_export.dat";
#else
static const char zy_export_filename[] = "/usr/g/psddata/zy_export.dat";
#endif

/* --- Local function prototypes --- */
static GeCrcResult zyExportCrc( n32 *pCrc,
                                const ZY_EXPORT * zy_export,
                                const size_t len );

static void dumpZyExport( const ZY_EXPORT *zy_export,
                          const int len,
                          const char * filename );

/* --- End local function prototypes --- */

/**
 * Computes CRC for an array of ZY_EXPORT structures
 *
 * @param[out] GeCrcResult - GE_CRC_OK if crc computed successfully
 * @param[out] pCrc - computed CRC
 * @param[in] zy_export - array of zy_export structures
 * @param[in] len - number of elements in zy_export
 */
static GeCrcResult zyExportCrc( n32 *pCrc,
                                const ZY_EXPORT * zy_export,
                                const size_t len )
{
    /*
     * This CRC compuation requires that ZY_EXPORT consists solely of fully
     * packed n16 variables.  Computing the crc independently on each
     * structure element using the geCrcAdd*() methods is more robust to
     * changes in ZY_EXPORT, but was ~2.5 slower that the below geCrcCalc16
     * method for the current ZY_EXPORT structure.
     */
    return geCrcCalc16(pCrc, (const n16 *)zy_export, sizeof(ZY_EXPORT) * len);
}

/**
 * write ZY_EXPORT to disk as text file for debugging purposes
 *
 *  @param[in] zy_export - ZY_EXPORT table to tranfer to AGP
 *  @param[in] len - Number of element in zy_export table to transfer
 *  @param[in] filename - filename to write to
 */
static void dumpZyExport( const ZY_EXPORT *zy_export,
                          const int len,
                          const char * filename )
{
    FILE * fid = NULL;
    char filepath[BUFSIZ] = "";

#ifdef SIM
    strcpy(filepath, "./");
#else
    strcpy(filepath, "/usr/g/service/log/");
#endif
    strcat(filepath, filename);

    fid = fopen(filepath, "w");
    if( fid != NULL )
    {
        int i = 0;
        for( i = 0; i < len; ++i )
        {
            /* SVBranch HCSDM00092046  Initial promote to support SBM */
            fprintf(fid, "zy_export[%d] = {%d,%d,%d,%d,%d}\n", i, zy_export[i].view, zy_export[i].slice, zy_export[i].echo, zy_export[i].heat,
                    zy_export[i].flags);
        }

        fclose(fid);
    }
}

/* ------------------------ Host only functions ------------------------ */
#ifdef HOST_TGT

/* Host side only local includes */
#include <stdlib.h>

#ifndef SIM
#include "cnv_endian_API.h"

/**
 * Swaps bytes (little/big endian) in array of ZY_EXPORT structures
 *
 * NOTE: Assumes that ZY_EXPORT is only n16 elements.
 *
 * Used local implementation of byteswap instead of cnv_endian_n16()
 * because the local implementation was approximately 4x faster
 *
 * @param[in/out] ZY_EXPORT * p  Pointer to the ZY_EXPORT array to byteswap
 * @param[in] len  Number of elements in ZY_EXPORT array
 */
static void
byteswapZyExport(ZY_EXPORT * zy_exp, const int len)
{
    int i = 0;
    char * p = (char *)zy_exp;
    const int size = len*sizeof(ZY_EXPORT);

    for( i = 0; i < size; i += sizeof(n16) )
    {
        char tmpc = p[i];
        p[i] = p[i+1];
        p[i+1] = tmpc;
    }
}

#endif /* !SIM */

/**
 * stores content of ZY_EXPORT array for transfer to target PSD
 *
 * This function writes the populated contents of the zy_export array
 * to disk for transfer to the AGP instead of using a static array in
 * @ipgexport.  The file size ia determined by the actual yres and
 * slice number.  Since routine clinical scan will not use the maximum
 * resolution, the file size will typically be much smaller and the
 * download time will be faster.
 *
 *  @param[in] zy_export - ZY_EXPORT table to tranfer to AGP
 *  @param[in] len - Number of element in zy_export table to transfer
 *  @param[in] debug_flag - if(debug_flag), enable debugging code
 *  @return status of function (SUCCESS or FAILURE)
 */
    STATUS
writeZyExport(const ZY_EXPORT *zy_export, const int len, const int debug_flag)
{
    const char * funcName = "writeZyExport";
    ZY_EXPORT *zy_export_swap = NULL;
    FILE * fid = NULL;
    n32 crc = 0;
    GeCrcResult crcResult = GE_CRC_ERR_MEM;

    if( debug_flag )
    {
        printf("%s: Writing %d elements to %s\n", funcName, len, zy_export_filename);
        dumpZyExport(zy_export, len, "zy_export_host.txt");
    }

    /* Calculate checksum of data to be downloaded for integrity checking */
    crcResult = zyExportCrc(&crc, zy_export, len);
    if( GE_CRC_OK != crcResult )
    {
        printf("%s: unable to compute zy_export checksum (%d)\n", funcName, crcResult);
        return FAILURE;
    }

    /* Make a copy for byteswapping */
    zy_export_swap = (ZY_EXPORT *)malloc(sizeof(ZY_EXPORT) * len);
    if( NULL == zy_export_swap )
    {
        printf("%s: malloc memory for zy_export_swap failed!\n", funcName);
        return FAILURE;
    }
    memcpy(zy_export_swap, zy_export, sizeof(ZY_EXPORT) * len);

#ifndef SIM
    /* Byteswap in hardware */
    cnv_endian_n32(&crc);
    byteswapZyExport(zy_export_swap, len);
#endif /* !SIM */

    /* Save to disk */
    fid = fopen(zy_export_filename, "wb");
    if( NULL == fid )
    {
        printf("%s: open file %s for writing failed!\n",
               funcName, zy_export_filename);
        free(zy_export_swap);
        return FAILURE;
    }

    if( fwrite(&crc, sizeof(crc), 1, fid) != 1 )
    {
        printf("%s: write zy_export crc to file %s failed!\n",
            funcName, zy_export_filename);
        free(zy_export_swap);
        fclose(fid);
        return FAILURE;
    }

    if( (int)(fwrite(zy_export_swap, sizeof(ZY_EXPORT), len, fid)) != len )
    {
        printf("%s: write zy_export_pkd to file %s failed!\n",
            funcName, zy_export_filename);
        free(zy_export_swap);
        fclose(fid);
        return FAILURE;
    }

    free(zy_export_swap);
    fclose(fid);

    return SUCCESS;
}

#endif /* HOST_TGT */

/* ------------------------ Target only functions ------------------------ */
#ifdef MGD_TGT

/* Target side only local includes */
#include "epicfuns.h"
#include "epicmsg.h"

/**
 * restores ZY_EXPORT structure written by Host PSD using writeZyExport()
 * into Target PSD
 *
 * @param[out] zy_export - ZY_EXPORT table to read from disk.
 *                         Memory must already be allocated for at least
 *                         len elements of this structure.
 * @param[in] len - Number of element in zy_export table to read
 * @param[in] debug_flag - if(debug_flag), enable debugging code
 * @return status of function (SUCCESS or FAILURE)
 */
STATUS
readZyExport(ZY_EXPORT *zy_export, const int len, const int debug_flag)
{
    STATUS status = SUCCESS;
    const char * funcName = "readZyExport";
    FILE *fid = NULL;
    n32 crcFile = 1;
    n32 crcLocal = 0;
    GeCrcResult crcResult = GE_CRC_ERR_MEM;
    int read_in_length = 0;

    if( debug_flag )
    {
        printf("%s: Reading %d elements from %s\n", funcName, len, zy_export_filename);
    }

    fid = fopen(zy_export_filename,"rb");
    if( NULL == fid )
    {
        status = FAILURE;
        printf("%s: open file %s for reading failed!\n", funcName, zy_export_filename);
    }

    /* Read CRC */
    if( SUCCESS == status )
    {
        if( 1 != fread(&crcFile, sizeof(crcFile), 1, fid) )
        {
            status = FAILURE;
            fclose(fid);
            printf("%s: Unable to read zy_export crc from %s\n", funcName, zy_export_filename);
        }
    }

    /* Read ZY_EXPORT */
    if( SUCCESS == status )
    {
        read_in_length = fread(zy_export, sizeof(ZY_EXPORT), len, fid);
        fclose(fid);
        if( read_in_length != len )
        {
            status = FAILURE;
            printf("%s: Only able to read %d of %d ZY_EXPORT elements from %s\n",
                   funcName, read_in_length, len, zy_export_filename);
        }
    }

    /* Verify CRC */
    if( SUCCESS == status )
    {
        crcResult = zyExportCrc(&crcLocal, zy_export, len);
        if( GE_CRC_OK != crcResult )
        {
            status = FAILURE;
            printf("%s: unable to compute zy_export checksum (%d)\n", funcName, crcResult);
        }
        else if( crcLocal != crcFile )
        {
            status = FAILURE;
            printf("%s: zy_export CRC does not match expected value %lu != %lu\n",
                   funcName, crcLocal, crcFile);
        }
    }

    if( debug_flag )
    {
        dumpZyExport(zy_export, len, "zy_export_tgt.txt");
    }

    if( FAILURE == status )
    {
        MsgHndlr(funcName, MSG_FORMAT, FILE_PBM,
                 EMT_PSD_SUPPORT_FAILURE, funcName);
    }

    return status;
}

#endif /* MGD_TGT */
