/*
 * GE Healthcare
 * Copyright (C) 2006 The General Electric Company
 *
 * efgre3d_support.c
 *
 * ANSI C support functions for efgre3d with no global variables.  If a
 * function uses any global variables, including CVs, ipgexport variables,
 * and host/tgt global variables, do NOT put the function in this file.
 *
 * The goal of this source file to provide a place for clean, well scoped,
 * functions to be defined.  By not including the #include's with the EPIC
 * globals, the compiler will enforce not accidentally using a global
 * variable.
 *
 * Language : ANSI C
 * Author   : Charles Michelich
 * Date     : May 11, 2006
 *
 */

/*************************************************************************
05/17/2007   EB      MRIhc24281   Added walkSamplingPattern() to calculate the
                                  exact scan time. Optimized pfkr calculation

07/02/2007   EB      MRIhc22327   1D Box sampling support with 2D acceleration

08/22/2007   EB      MRIhc25788   Fractional echo (minTE) support for ARC

09/10/2007   EB      MRIhc26757   Uniform acceleration support with box

10/23/2007  KA/EB    MRIhc27185   Write time-stamp labeled kacq file on HW.

10/26/2007   SW      MRIhc27859   Add kx_peak_pos in kacq file.

12/10/2007 ATV/EB/SW MRIhc25811   Added infrastructure to support adaptive TE optimization

12/31/2007 EB        MRIhc31558   ARC acceleration logic implementation

05/28/2008 EB        MRIhc37692   Update the logic to handle ARC acceleration factors.

09/30/2008 CRM       MRIhc40044   Remove unused args to walkSamplingPattern

09/15/2008 ATV       MRIhc40746   Added infrastructure to support adaptive TE/TR optimization

12/30/2008 SW/CRM    MRIhc39347   Moved xres-FOV curves from efgre3d.e
                                  Add the xres-FOV curve of 3DDE for DV2 1.5T

02/11/2009 SW        MRIhc41492   Added xres-FOV curves for normal mode

03/17/2009 JX/EB     MRIhc42617   Added safety margin to the maximum displayed acceleration  
                                  against round off errors

04/28/2009 EB        MRIhc43145:  Introduced encode_group CV to provide more flexible view orders
                     MRIhc43146   to support non-separable sampling patterns such as corner removal,
                                  ARC box/elliptical sampling. Could be extended to all segmented
                                  acquisitions. Implemented phslGroupSort() for this purpose and 
                                  modified generateZyExport()

08/18/2009 EB       MRIhc44826    Added the xres-FOV curve of 3DDE for HDw 1.5T and simplified 
                                  calculations in setOptimizedGradientScalingFactor()

01/11/2009 RBA      MRIhc42465    Added support for Parallel Imaging UI, removed setArcPulldown () and modified it 
                                  to support Asset and ARC in psdsupport/accelsupport.c
                                  The new implementation of UI for  ARC renders splitArcFactor(), setMaxArcFactor(), 
                                  setAutoArcFactor() redundant. These are kept for sake of knowledge capture but not called.
                                  These functions would later be moved to psdsupport/accelsupport.c for a wider 
                                  use by wider range of PSDs in future.

09/25/2009 Lai       GEHmr02509:  Support smart derating in SV to shorten TR when min_seqgrad is dominant.
                                  Add more accurate method and calculate Power in setOptimizedGradientScalingFactor().

12/22/2009 TAC      MRIhc46445    Added TE Lock feature for automatically ensuring
                                  3D Dual Echo/LAVA-Flex/VIBRANT-Flex TEs remain within upper limits

12/31/2009 VSN/VAK  MRIhc46886    SV to DV Apps Sync Up

02/01/2010 EB       MRIhc47466    Merge GEHmr03661:  Added fabs() for a_gx1, a_gxwex and a_gxw.

02/15/2010 EB       MRIhc47709    Lock 3D DE/Sagittal Vibrant-Flex and LAVA-Flex 3T TEs to 1.3/2.6

03/12/2010 TAC      MRIhc47629    Fixed TE Lock failure when set_cvs_changed_flag is incorrectly set to false
                    MRIhc47988

03/25/2010 EB       MRIhc48821    Updated 3T 3D DE/LAVA-Flex and VIBRANT-Flex limits to usec precision

04/30/2010 TAC/CRM  MRIhc49891    Fixed issue with incorrect display of xres when advisory error is canceled.

03/31/2011 KA       MRIhc56002    Added range check to avoid download failure due to zero division.

06/02/2011 KA       MRIhc56341    Added isRefRegionValid() for IDEALIQ phase correction.

09/30/2011 Lai   HCSDM00092046  Initial promote to support Smart Burst Mode (SBM) in 16BEAT                                  


10/03/2013 NT       HCSDM00241750  Fast LAVA feature promote

02/27/2014 TAC      HCSDM00264720  DISCO feature

26/Aug/2015 YT      HCSDM00341147  Support image cut reduction

12/11/2015 HM       HCSDM00385665  Fixed issue with the number of zy_export lines in kacq_yz.txt for Turbo LAVA

01/10/2017 VSN      HCSDM00439672  Scan time fix when pfkr_yz_flag is 1 and slice encodes greater than phase encodes

02/13/2017 VSN      HCSDM00445314  For FTMRA the sampledPoints need to be multiple of views per segment
**************************************************************************/

/* ----------------------Host and Target functions --------------------- */

/* Local header files */
#include <string.h>
#include "stddef_ep.h"
#include "efgre3d_support.h"

/* SVBranch HCSDM00092046  Initial promote to support SBM */
/* Maximal allowed number for heat */
#define HEAT_MAX 65535

/* Kacq revisions numbers */
#define KACQ_REV_MAJOR 201
#define KACQ_REV_MINOR 0

/* Method for gradient derating */
#define LEGACY_METHOD 0
#define POWER_METHOD 1

/* SVBranch GEHmr04241 Dual Echo support ART */
/* ART variables, same as in setgradspec.c */
#define SILENT_HIGH 1
#define SILENT_LOW 2

/* Structure for calculating playout order on host */
typedef struct zy_dist {
    float distance;
    float angle;
    n16 view;
    n16 slice;
    n16 flags;
} ZY_DIST;

typedef struct arraytosort {
    float a;
    float b;
    float c;
    int   d;
    float e;
} arraytosort;

/* --- Local function prototypes -- */
static STATUS
copyfile(CHAR *src, CHAR *dst);

static INT
arcGetBamFrameNumber(const INT view, const INT slice, const INT echo,
                     const INT dayres, const INT nEchoes,
                     const INT noSortFlag,
                     const INT index,
                     const INT packBamFlag,
                     const INT *phRemapTable,
                     const INT *slRemapTable);

/* --- End local function prototypes -- */

/*  copyfile
 *
 *  Description:
 *    Copy file src to dst.  This function uses a buffered file copy
 *    which has NOT been optimized for performance.  System calls to
 *    the "cp" command may yield better performance on linux.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const CHAR *src - Null terminated string containing filename and
 *        path of file to copy.
 *  (I) const CHAR *dst - Null terminated string containing filename and
 *        path of destination to copy file to.
 */
static STATUS
copyfile(CHAR *src, CHAR *dst)
{
    /* Copy file by reading to and writing from a buffer */
    FILE *srcFile = NULL;
    FILE *dstFile = NULL;
    size_t bufSz = 8192;
    size_t elemRead, elemWritten;
    char buf[bufSz];

    srcFile = fopen(src, "rb");
    if (NULL == srcFile)
    {
        printf("ERROR in copyfile(): Unable to open %s for reading", src);
        return FAILURE;
    }

    dstFile = fopen(dst, "wb");
    if (NULL == dstFile)
    {
        printf("ERROR in copyfile(): Unable to open %s for writing", dst);
        return FAILURE;
    }

    elemRead = bufSz;
    while (elemRead == bufSz)
    {
        elemRead = fread(buf, sizeof(char), bufSz, srcFile);
        elemWritten = fwrite(buf, sizeof(char), elemRead, dstFile);
        if (elemRead != elemWritten)
        {
            printf("ERROR in copyfile(): Unable to write all data to %s", dst);
            return FAILURE;
        }
    }

    if (0 != fclose(srcFile))
    {
        printf("ERROR in copyfile(): Unable to close file %s", src);
        return FAILURE;
    }
    if (0 != fclose(dstFile))
    {
        printf("ERROR in copyfile(): Unable to close file %s", dst);
        return FAILURE;
    }

    return SUCCESS;
}

/*  copyKacqToMrraw
 *
 *  Description:
 *    Copy the specified kacq file to a unique filename in
 *    /usr/g/mrraw/<kacqFilename>  The intended use of this function
 *    is to store the kacq file with the raw data when saving raw data.
 *    such that it is not lost through normal kacq file cleanup.  The
 *    calling function must ensure that the destination filename
 *    (kacqFilenameDst) is unique.  The recommended method to do this is
 *    to append a period followed by the a unique identified stored in
 *    the raw header (rhkacq_uid) such that offline recon can to associate
 *    a P-file with a particular kacq file.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - Did function complete successfully
 *  (I) const CHAR *kacqFilenameSrc - name of kacq file to copy (null terminated)
 *  (I) const CHAR *kacqPath - path to kacq file to copy (null terminated)
 *  (I) const CHAR *kacqFilenameDst - name of kacq file to in mrraw
 *                                    (null terminated)
 *  (I) const INT uid - number to concatenate to end of copied kacq
 *
 */
STATUS
copyKacqToMrraw(const CHAR *kacqFilenameSrc, const CHAR *kacqPath,
                const CHAR *kacqFilenameDst)
{
    CHAR src[BUFSIZ];
    CHAR dst[BUFSIZ];

#ifdef PSD_HW
    const CHAR *kacqRawPath = "/usr/g/mrraw/";
#else
    const CHAR *kacqRawPath = "./";
#endif

    sprintf(src, "%s%s", kacqPath, kacqFilenameSrc);
    sprintf(dst, "%s%s", kacqRawPath, kacqFilenameDst);
    if (FAILURE == copyfile(src, dst))
    {
        return FAILURE;
    }

    return SUCCESS;
}

/* arcGetBamFrameNumber
 * Description: Get the location of a frame in BAM for writing in the kacq
 * file for ARC.  This location is the number of frames (rhdaxres) from the
 * beginning of the pass.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - location of specified frame in BAM (number of
 *        frames of size rhdaxres from the beginning of the pass)
 *  (I) const INT view  - current view  (no baseline, zero-based)
 *  (I) const INT slice - current slice (zero-based)
 *  (I) const INT echo  - current echo  (zero-based)
 *  (I) const INT dayres - y-resolution for sort/nex (rhdayres)
 *  (I) const INT nEchoes - number of echoes for sort/nex (rhnecho)
 *  (I) const INT noSortFlag - True is sort/nex is disabled
 *  (I) const INT index - Index of current element of ZY_EXPORT array
 *                        (zero-based).  Used when noSortFlag is true.
 *  (I) const INT packBamFlag - Bit mask specifying to pack BAM in view/slice
 *                              or both (BAM_PACK_Y, BAM_PACK_Z)
 *  (I) const INT *phRemapTable - Vector containing mapping from view
 *                                to packed view
 *  (I) const INT *slRemapTable - Vector containing map from slice
 *                                to packed slice
 *
 *  NOTE: phRemapTable and slRemapTable are generated by arcPackBam.
 *
 */
static INT
arcGetBamFrameNumber(const INT view, const INT slice, const INT echo,
                     const INT dayres, const INT nEchoes,
                     const INT noSortFlag,
                     const INT index,
                     const INT packBamFlag,
                     const INT *phRemapTable,
                     const INT *slRemapTable)
{
    INT frame;

    if (noSortFlag)
    {
        /* Not using sort/nex */
        frame = index;
    }
    else
    {
        /* Using sort/nex */

        /* If using "BAM packing", remap view and slice */
        int bam_view = view;
        int bam_slice = slice;

        if (packBamFlag & BAM_PACK_Y)
        {
            bam_view = phRemapTable[bam_view];
        }

        if (packBamFlag & BAM_PACK_Z)
        {
            bam_slice = slRemapTable[bam_slice];
        }

        /* Calculate offset to sorted data (x,y,echo,z)
           The +1 is for the baseline view */

        frame = bam_view + 1 + dayres * (echo + nEchoes * bam_slice);
    }

    return frame;
}

/* writeKacq
 *
 *  Description:
 *    Generate kacq file.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - Did function complete successfully.
 *  (I) const INT kx_peak_pos - Echo peak position in kx direction = rhdaxres-opxres/2
 *  (I) const INT unaccelPhases - Fully sampled number of phase encodes
 *  (I) const INT unaccelSlices - Fully sampled number of slice encodes
 *  (I) const ZY_EXPORT *zy_export- zy_export table
 *  (I) const INT sampledPoints - Number of encodes sampled (including
 *        calibration encodes)
 *  (I) const INT calibrationPoints - Number of encodes in calibration region
 *                                    -1 skips writing the calibration patterns
 *  (I) const INT maskPoints - Number of encodes in mask
 *                             -1 skips writing the mask pattern
 *  (I) const INT nEchoes - Number of echos
 *  (I) const INT nTemporalPhases - Number of temporal phases
 *  (I) const INT dayres - y-resolution for sort/nex (rhdayres)
 *  (I) const INT calEcho - Echo to use for calibration.  Use -1 to indicate
 *        calibration from same echo as acquisition
 *  (I) const CAL_PARAM calRegion - calibration region information
 *  (I) const INT noSortFlag - True is sort/nex is disabled
 *  (I) const INT packBamFlag - Bit mask specifying to pack BAM in view/slice
 *        or both (BAM_PACK_Y, BAM_PACK_Z)
 *  (I) const INT *phRemapTable - Vector containing mapping from view to
 *        packed view
 *  (I) const INT *slRemapTable - Vector containing map from slice to
 *        packed slice
 *  (I) const INT copyKacqToMrrawFlag - Flag to indicate if kacq file should
 *        be copied to /usr/g/mrraw/
 *  (I) const INT kacqUid - Unique number to concatenate to end of kacq filename
 *  (I) const INT maxRy - maximum outer acceleration in phase direction
 *  (I) const INT maxRz - maximum outer acceleration in slice direction
 *  (I) const INT pfkr_yz_flag - Corner removal with sequential manner y or z view ordering
 *  (I) const INT nr_of_segments - Number of segments when segmented_flag
 *  (I) const INT views_per_segment - Views per segment or radial beam
 *  (I) const PARAM4D *param4d - parameters for 4D imaging
 *
 *  NOTE: Function assume that first sampledPoints elements of zy_export contain
 *    the sampled and calibration data followed by the mask points (size: maskPoints)
 *
 */
STATUS
writeKacq(const INT kx_peak_pos,
          const INT unaccelPhases,
          const INT unaccelSlices,
          const ZY_EXPORT *zy_export,
          const INT sampledPoints,
          const INT calibrationPoints,
          const INT maskPoints,
          const INT nEchoes,
          const INT nTemporalPhases,
          const INT dayres,
          const INT calEcho,
          const CAL_PARAM calRegion,
          const INT noSortFlag,
          const INT packBamFlag,
          const INT *phRemapTable,
          const INT *slRemapTable,
          const INT copyKacqToMrrawFlag,
          const INT kacqUid,
          const INT maxRy,
          const INT maxRz,
          const INT pfkr_yz_flag,
          const INT nr_of_segments,
          const INT views_per_segment,
          const PARAM4D *param4d)
{
    const CHAR *kacqFilenameBase = "kacq_yz.txt";
    CHAR kacqFilename[BUFSIZ];
    CHAR kacqFilenameFull[BUFSIZ];
    FILE *kacq;
    INT frame, t, si, echo;
    INT patternCount = 0;
    INT calEchoCurr = calEcho;
    INT calPattern = 0;
    INT maskPattern = 0;

#ifdef PSD_HW
    const CHAR *kacqPath = "/usr/g/psddata/";
    sprintf(kacqFilename, "%s.%d", kacqFilenameBase, kacqUid);
#else
    const CHAR *kacqPath = "./";
    sprintf(kacqFilename, "%s", kacqFilenameBase);
#endif
    sprintf(kacqFilenameFull, "%s%s", kacqPath, kacqFilename);

    kacq = fopen(kacqFilenameFull, "w");

    if (kacq == NULL)
    {
        return FAILURE;
    }
    /* si_length defines sampling length to print out zy_export for kacq file */
    int si_length  = sampledPoints;
    if (pfkr_yz_flag && (VIEWSHARING_OFF == param4d->vieworder_mode))
    {
        si_length = nr_of_segments * views_per_segment;
    }

    /* Write header for accelerated data kacq file
       GEKACQ MajorRev MinorRev
       num_sampling_pattern = # sampling pattern tables
       num_mask_patterns = # mask tables
    */
    fprintf(kacq, "GE_KTACQ\t%d\t%d\n", KACQ_REV_MAJOR, KACQ_REV_MINOR);
    fprintf(kacq, "num_sampling_patterns\t%d\n", ((-1 == calibrationPoints) ? nEchoes : 2*nEchoes));
    fprintf(kacq, "num_mask_patterns\t%d\n", ((-1 == maskPoints) ? 0 : 1));
    fprintf(kacq, "kx_peak_pos\t%d\n", kx_peak_pos);
    fprintf(kacq, "---\n");

    /* Print out reconstruction schedule */
    fprintf(kacq, "# Reconstruction schedule\n");
    fprintf(kacq, "# t, Echo, Cal Table, Cal Pass, Accel Table, Accel Pass, Mask Table\n");
    fprintf(kacq, "RECON_SCHEDULE\t%d\t%d\n", nEchoes*nTemporalPhases, 7);
    fprintf(kacq, "---\n");

    if (-1 == maskPoints)
    {
        /* If not writing a mask pattern, specify -1 in the recon schedule */
        maskPattern = -1;
    }
    else
    {
        /* Otherwise, the mask pattern will always be 0 since there is
         * only one mask supplied to the function */
        maskPattern = 0;
    }

    for (t = 0; t < nTemporalPhases; t++)
    {
        for (echo = 0; echo < nEchoes; echo++)
        {
            if (-1 == calEcho)
            {
                /* Use current echo for calibration */
                calEchoCurr = echo;
            }

            if (-1 == calibrationPoints)
            {
                calPattern = -1;
            }
            else
            {
                calPattern = calEchoCurr + nEchoes;
            }

            fprintf(kacq, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                    t, echo, calPattern, t, echo, t, maskPattern);
        }
    }

    /* Print primary acquisition sampling patterns */
    for (echo = 0; echo < nEchoes; echo++)
    {
        fprintf(kacq, "# Sampling Pattern %d (Accel)\n", patternCount);
        fprintf(kacq, "# View Offset, Pass Offset, ky, kz\n");
        fprintf(kacq, "SAMPLING_PATTERN\t%d\t%d\n", sampledPoints, 4);
        fprintf(kacq, "max_stride\t%d\t%d\n", maxRy, maxRz);
        fprintf(kacq, "pattern_dimensions\t%d\t%d\n",
                unaccelPhases, unaccelSlices);
        fprintf(kacq, "---\n");

        for (si = 0; si < si_length; si++)
        {
            /* Accelerated lines */
            if (!(zy_export[si].flags & ZY_FLAGS_MASK) &&
                (zy_export[si].flags & ZY_FLAGS_SAMPLED))
            {
                frame = arcGetBamFrameNumber(zy_export[si].view,
                                             zy_export[si].slice,
                                             echo, dayres, nEchoes,
                                             noSortFlag, si,
                                             packBamFlag,
                                             phRemapTable, slRemapTable);

                fprintf(kacq, "%d\t%d\t%d\t%d\n", frame, 0,
                        zy_export[si].view, zy_export[si].slice);
            }
        }

        patternCount++;
    }

    /* Print calibration acquisition sampling patterns */
    if (calibrationPoints != -1)
    {
        for (echo = 0; echo < nEchoes; echo++)
        {
            fprintf(kacq, "# Sampling Pattern %d (Calibration)\n", patternCount);
            fprintf(kacq, "# View Offset, Pass Offset, ky, kz\n");
            fprintf(kacq, "SAMPLING_PATTERN\t%d\t%d\n", calibrationPoints, 4);
            fprintf(kacq, "pattern_dimensions\t%d\t%d\n",
                    unaccelPhases, unaccelSlices);
            fprintf(kacq, "fully_sampled_start\t%d\t%d\n",
                    calRegion.phaseCutoffLower, calRegion.sliceCutoffLower);
            fprintf(kacq, "fully_sampled_length\t%d\t%d\n",
                    calRegion.phaseCutoffUpper - calRegion.phaseCutoffLower + 1,
                    calRegion.sliceCutoffUpper - calRegion.sliceCutoffLower + 1);
            fprintf(kacq, "cal_apodization_kasier_bessel_beta\t%f\t%f\n", 1.0, 1.0);
            fprintf(kacq, "---\n");

            for (si = 0; si < si_length; si++)
            {
                /* Calibration lines */
                if (!(zy_export[si].flags & ZY_FLAGS_MASK) &&
                    (zy_export[si].flags & ZY_FLAGS_CAL))
                {
                    frame = arcGetBamFrameNumber(zy_export[si].view,
                                                 zy_export[si].slice,
                                                 echo, dayres, nEchoes,
                                                 noSortFlag, si,
                                                 packBamFlag,
                                                 phRemapTable, slRemapTable);

                    fprintf(kacq, "%d\t%d\t%d\t%d\n", frame, 0,
                            zy_export[si].view, zy_export[si].slice);
                }
            }

            patternCount++;
        }
    }

    /* Print mask pattern */
    if (maskPoints != -1)
    {
        fprintf(kacq, "# Mask pattern 0\n");
        fprintf(kacq, "# ky, kz\n");
        fprintf(kacq, "MASK_PATTERN\t%d\t%d\n", maskPoints, 2);
        fprintf(kacq, "pattern_dimensions\t%d\t%d\n", unaccelPhases, unaccelSlices);
        fprintf(kacq, "---\n");

        for (si = sampledPoints; si < sampledPoints + maskPoints; si++)
        {
            if (zy_export[si].flags & ZY_FLAGS_MASK)
            {
                fprintf(kacq, "%d\t%d\n", zy_export[si].view, zy_export[si].slice);
            }
        }
    }

    fclose(kacq);

    /* If saving raw data, copy kacq to a unique filename in /usr/g/mrraw */
    if (copyKacqToMrrawFlag)
    {
        copyKacqToMrraw(kacqFilename, kacqPath, kacqFilename);
    }

    return SUCCESS;
}

/* ------------------------ Host only functions ------------------------ */
#ifdef HOST_TGT

/* Host side only local includes */
#include <math.h>
#include <stdlib.h>
#include "epic.global.h" /* Just the #defines and typedefs from epic.h.
                            No global variables! */
#include "support_func.host.h"

/* --- Host only local function prototypes -- */

static STATUS
writeZyDistDebug(const CHAR * filename, const CHAR * prefix,
                 const ZY_DIST * zy_dist, const int zy_dist_length);

static FLOAT
calc_angle(const FLOAT kz, const FLOAT ky);

static int
dist_compare(const void *dist1, const void *dist2);

static int
dist_compare_rev(const void *dist1, const void *dist2);

static int
angle_compare(const void *dist1, const void *dist2);

static STATUS
radfbsort(ZY_DIST *zy_sort, const int zy_sort_length, const int total_segments);

static STATUS
discosort(ZY_DIST *zy_sort, const int zy_sort_length, const int segmented_flag, const int views_per_segment, PARAM4D *param4d);

static STATUS
reorder_region(ZY_DIST *region_sort, const int region_length, const float num_transition_fraction);

void
copy_vector(int n, float* a, float* b);

void
copy_vector_i(int n, int* a, int* b);

static int
comparefun(const void *array1, const void *array2);

static int
comparefun2(const void *array1, const void *array2);

void 
sort_vectors(int index_start, int index_end, int dir, float* a, float* b, float* c, int* d);

static STATUS
phslGroupSort(ZY_DIST *zy_sort, const int zy_sort_length, const int views_per_segment);

static STATUS
tricksRegionSort(ZY_DIST *zy_sort, const int zy_sort_length, const int regions,
                 const int transition_views);

static STATUS
markSegStart(ZY_DIST *zy_sort, const int zy_sort_length, const int total_segments);

static INT
onAccelGrid(const INT index, const FLOAT outerReductionFactor);

static INT
inCalBorder(const INT index, const INT cutoffLower, const INT cutoffUpper);

static INT
calibration_voxel(const INT phase, const INT slice, const CAL_PARAM calRegion);

static INT
accelerated_voxel(const INT phase, const INT slice, const CAL_PARAM calRegion,
                  const FLOAT phOuterReductionFactor,
                  const FLOAT slOuterReductionFactor);

static STATUS
markXzDone(ZY_EXPORT *zy_export, const INT sampledPoints);

static STATUS
slice_order_efgre3d(INT *slicetab,
                    const INT zy_slices,
                    const INT slorder,
                    const INT nsegments,
                    const INT chemseqs,
                    const INT chemseq0,
                    const INT linestodiscard,
                    const INT pfkz_flag,
                    const INT pfkz_total,
                    const INT pfkz_segments,
                    const INT pfkz_views_per_segment,
                    const INT arc_flag,
                    const CAL_PARAM calRegion,
                    const FLOAT arc_sl_stride,
                    INT *extraspecial_slice);

static INT
irslice(INT const index, INT const equant, INT const slorder,
        INT const nsegments, INT const chemseqs, INT const chemseq0);

static INT
countSampledPoints(const ZY_DIST *zy_sort, const INT zy_sort_length);

/* --- End host only local function prototypes --- */

/* writeZyDistDebug
 *
 *  Description:
 *    Write ZY_DIST structure to dist for debuggind.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (I) const CHAR * filename - Filename to write output to
 *  (I) const CHAR * prefix - String to prepend to each output line
 *  (I) const ZY_DIST * zy_dist - Array of zy_dist structures to write
 *  (I) const int zy_dist_length - Number of elements in zy_dist to write
 */
static STATUS
writeZyDistDebug(const CHAR * filename, const CHAR * prefix,
                 const ZY_DIST * zy_dist, const int zy_dist_length)
{
    int i, retval;
    FILE * fid = NULL;
    const CHAR * funcName = "writeZyDistDebug";

    fid = fopen(filename, "w");
    if (NULL == fid)
    {
        printf("%s: open file %s for writing failed!\n", funcName, filename);
        return FAILURE;
    }

    for (i = 0; i < zy_dist_length ; i++)
    {
        retval = fprintf(fid, "%s:view = %d; slice = %d; done = %d; mask = %d; superindex = %d; yz_dist = %4f; flags = %d\n",
                         prefix,
                         zy_dist[i].view,
                         zy_dist[i].slice,
                         (zy_dist[i].flags & ZY_FLAGS_XZ_DONE) == ZY_FLAGS_XZ_DONE,
                         (zy_dist[i].flags & ZY_FLAGS_MASK) == ZY_FLAGS_MASK,
                         i,
                         zy_dist[i].distance,
                         zy_dist[i].flags);

        if (retval < 0)
        {
            printf("%s: Error writing line %d to %s\n", funcName, i, filename);
            return FAILURE;
        }
    }

    retval = fclose(fid);
    if (0 != retval)
    {
        printf("%s: Error closing file %s\n", funcName, filename);
        return FAILURE;
    }

    return SUCCESS;
}

/*  calc_angle
 *
 *  Description:
 *    Calculate angle of specified encode on kz-ky plane.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) float return variable - angle in degrees
 *  (I) const FLOAT kz - spectral distance in slice encode direction
 *  (I) const FLOAT ky - spectral distance in phase encode direction
 *
 */
static FLOAT calc_angle(const FLOAT kz, const FLOAT ky)
{
    FLOAT theta = atan(ky/kz)*180.0/PI;
    if ( (theta > 0) && (ky < 0) )
        theta = 180.0 + fabs(theta);
    if ( (theta < 0) && (kz > 0) )
        theta += 360.0;
    if ( (theta < 0) && (kz < 0) )
        theta += 180.0;
    return theta;
}

/*  dist_compare
 *
 *  Description:
 *    dist_compare is a function used for sorting the zy_sort structure
 *    with qsort. It returns "1" if the dist field of the first argument is
 *    greater than than the second, otherwise it returns "-1".  This result
 *    is used to sort structure elements by distance from the center of
 *    k-space for elliptical centric k-space ordering.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) int return variable - comparison result
 *  (I) const void *dist1 - Pointer to a ZY_DIST structure
 *  (I) const void *dist2 - Pointer to a ZY_DIST structure
 *
 */
static int
dist_compare(const void *dist1, const void *dist2)
{
    return (((ZY_DIST *)dist2)->distance < ((ZY_DIST *)dist1)->distance )? 1: -1;
}

/*  dist_compare_rev
 *
 *  Description:
 *    dist_compare_rev is a function used for sorting the zy_sort structure
 *    with qsort. It returns "1" if the dist field of the first argument is
 *    less than the second, otherwise it returns "-1".  This result is used
 *    to sort structure elements by distance from the edge to the center of
 *    k-space for reverse elliptical centric k-space ordering.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) int return variable - comparison result
 *  (I) const void *dist1 - Pointer to a ZY_DIST structure
 *  (I) const void *dist2 - Pointer to a ZY_DIST structure
 *
 */
static int
dist_compare_rev(const void *dist1, const void *dist2)
{
    return (((ZY_DIST *)dist2)->distance >= ((ZY_DIST *)dist1)->distance )? 1: -1;
}

/*  angle_compare
 *
 *  Description:
 *    angle_compare is a function used for sorting the zy_sort structure
 *    with qsort. It returns "1" if the angle field of the first argument is
 *    greater than than the second, otherwise it returns "-1".  This result
 *    is used to sort structure elements by angle for radial fan beam
 *    k-space ordering.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) int return variable - comparison result
 *  (I) const void *dist1 - Pointer to a ZY_DIST structure
 *  (I) const void *dist2 - Pointer to a ZY_DIST structure
 *
 */
static int
angle_compare(const void *dist1, const void *dist2)
{
    return (((ZY_DIST *)dist2)->angle < ((ZY_DIST *)dist1)->angle )? 1: -1;
}

/*  copy_vector
 *
 *  Description:
 *    copy_vector is a function used for copying vector. The element is float type.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) int n - number of vector
 *  (I) float *a - Pointer to a vector structure
 *  (O) float *b - Pointer to a vector structure
 */

void copy_vector(
    int    n, /* I */
    float* a, /* I */
    float* b  /* O */
    )
{
    int i;

    if ((b!=NULL) && (a!=NULL))
    {
        for (i=0; i<n; i++)
        {
            b[i] = a[i];
        }
    }
}

/*  copy_vector_i
 *
 *  Description:
 *    copy_vector_i is a function used for copying vector. The element is integer type.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) int n - number of vector
 *  (I) int *a - Pointer to a vector structure
 *  (O) int *b - Pointer to a vector structure
 */

void copy_vector_i(
    int  n, /* I */
    int* a, /* I */
    int* b  /* O */
    )
{
    int i;

    if ((b!=NULL) && (a!=NULL))
    {
        for (i=0; i<n; i++)
        {
            b[i] = a[i];
        }
    }
}

/*  comparefun
 *
 *  Description:
 *    comparefun is a function used for comparing each elements of array in qsort().
 *    It returns "1" if the value of the first argument is greater than the second,
 *    otherwise it returns "-1". This result is used to sort structure elements.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) int return variable - comparison result
 *  (I) const int *array1 - Pointer to a vector structure
 *  (I) const int *array2 - Pointer to a vector structure
 */

/* Compare Function for sorting forward direction */
static int
comparefun(const void *array1, const void *array2)
{
    return (((arraytosort *)array1)->a > ((arraytosort *)array2)->a )? 1: -1;
}

/*  comparefun2
 *
 *  Description:
 *    comparefun is a function used for comparing each elements of array in qsort().
 *    It returns "1" if the value of the first argument is smaller than the second,
 *    otherwise it returns "-1". This result is used to sort structure elements.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) int return variable - comparison result
 *  (I) const int *array1 - Pointer to a vector structure
 *  (I) const int *array2 - Pointer to a vector structure
 */

/* Compare Function for sorting reverse direction */
static int
comparefun2(const void *array1, const void *array2)
{
    return (((arraytosort *)array1)->a < ((arraytosort *)array2)->a )? 1: -1;
}

/*  sort_vectors
 *
 *  Description:
 *    sort_vectors is a function used for sorting vector. qsort() is used.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) int index_start - start point of vector
 *  (I) int index_end - end point of vector
 *  (I) int dir - determine comparison function
 *  (I/O) float *a - Pointer to a vector structure to be sorted.
 *  (I/O) float *b - Pointer to a vector structure to be sorted.
 *  (I/O) float *c - Pointer to a vector structure to be sorted.
 *  (I/O) int *d   - Pointer to a vector structure to be sorted.
 */

/* based on sort_vectors() in ARC_3dfse.e */
void sort_vectors(
    int  index_start, /*  I  */
    int  index_end,   /*  I  */
    int  dir,         /*  I  */ /* direction 1=forward, -1=reverse */
    float* a,         /* I/O */
    float* b,         /* I/O */
    float* c,         /* I/O */
    int*   d          /* I/O */
    )
{
    /* HCSDM00170864 Implement the sorting algorithm to be a faster qsort
     * approach. The input and output is not impacted. DLH Nov 2012 */
    int   i;
    arraytosort *temparray = NULL;
    int arraysize = index_end - index_start + 1;
    if (arraysize < 1)
    {
        return;
    }

    if (a == NULL)
    {
        return;
    }

    temparray = (arraytosort *) malloc(sizeof(arraytosort) * arraysize);
    if (temparray == NULL)
    {
        return;
    }

    for (i = index_start; i <= index_end; i++)
    {
        temparray[i-index_start].a = a[i];
        if (b!=NULL)
        {
            temparray[i-index_start].b = b[i];
        }
        else
        {
            temparray[i-index_start].b = 0;
        }
        if (c!=NULL)
        {
            temparray[i-index_start].c = c[i];
        }
        else
        {
            temparray[i-index_start].c = 0;
        }
        if (d!=NULL)
        {
            temparray[i-index_start].d = d[i];
        }
        else
        {
            temparray[i-index_start].d = 0;
        }
    }
    if (dir > 0)
    {
        qsort(&temparray[0], arraysize, sizeof(arraytosort), comparefun);
    }
    else
    {
        qsort(&temparray[0], arraysize, sizeof(arraytosort), comparefun2);
    }
    for (i = index_start; i <= index_end; i++)
    {
        a[i] = temparray[i-index_start].a;
        if (b!=NULL)
        {
            b[i] = temparray[i-index_start].b;
        }
        if (c!=NULL)
        {
            c[i] = temparray[i-index_start].c;
        }
        if (d!=NULL)
        {
            d[i] = temparray[i-index_start].d;
        }
    }
    free(temparray);
}

/*  radfbsort
 *
 *  Description:
 *    Sort k-space encodes into total_segments radial fan segments.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * zy_sort - array of structures for containing all
 *        encodes to sort.  Assumes that dist and angle fields are already
 *        calculated.
 *  (I) const int zy_sort_length - number of elements in zy_sort to sort
 *  (I) const int total_segments - number of segments to divide zy_sort into.
 *        If zy_sort_length/total_segments is not an integer, it will divide
 *        into total_segments with variable length as close to
 *        zy_sort_length/total_segments as possible.
 *
 */
static STATUS
radfbsort(ZY_DIST *zy_sort, const int zy_sort_length, const int total_segments)
{
    const char funcName[] = "radfbsort";
    int seg, seg_start, vps_curr;
    float vps_target;

    /* Calculate desired views per segments */
    vps_target = (float)zy_sort_length / (float)total_segments;

    /* Sort all encodes by angle */
    qsort(zy_sort, zy_sort_length, sizeof(ZY_DIST), angle_compare);

    seg_start = 0;
    for (seg = 1; seg <= total_segments; seg++)
    {
        /* Calculate length of current segment */
        if (seg < total_segments)
        {
            vps_curr = (int)floor(seg*vps_target + 0.5) - seg_start;
        }
        else
        {
            vps_curr = zy_sort_length - seg_start;
        }

        /* Defensive check to avoid memory corruption bugs. This should
           never fail. */
        if (seg_start + vps_curr > zy_sort_length)
        {
            printf("%s: seg_start (%d) + vps_curr (%d) > zy_sort_length (%d) for segment %d or %d\n",
                   funcName, seg_start, vps_curr, zy_sort_length, seg, total_segments);
            return FAILURE;
        }

        /* Sort current segment by distance */
        qsort(&(zy_sort[seg_start]), vps_curr, sizeof(ZY_DIST), dist_compare);

        /* Set the segment start flag on the first encode of each segment */
        zy_sort[seg_start].flags |= ZY_FLAGS_SEG_START;

        seg_start += vps_curr;
    }

    return SUCCESS;
}

/*  orderviews_y
 *
 *  Description:
 *    Sort k-space encodes into sequential manner ky segments within coner removal.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) int num_views - acquired number of views in segmented views
 *  (I) int num_segs - number of segmented views
 *  (I) int num_echoes - number of views including dummy view
 *  (I) int skips_start - skipped echo at start
 *  (I) int yres - y matrix
 *  (I) int ystride - y stride of ARC or ASSET
 *  (I) int echo_dir - view direction
 *  (I) int seg_dir - view segmentation direction
 *  (I) int phorder - centric flag of view segmentation direction
 *  (I) float * y_list - array of y view structures
 *  (I) float * z_list - array of z view structures
 *  (I) float * flag_list - array of flag structures
 *  (O) float * y_sort - sorted array of y view structures
 *  (O) float * z_sort - sorted array of z view structures
 *  (O) float * flag_sort - sorted array of flag structures
 */

/* based on orderviews_y() in ARC_3dfse.e */
void orderviews_y(
    int   num_views,   /* I */
    int   num_segs,    /* I */
    int   num_echoes,  /* I */
    int   skips_start, /* I */
    int   yres,        /* I */
    int   ystride,     /* I */
    int   echo_dir,    /* I */
    int   seg_dir,     /* I */
    int   phorder,     /* I */
    float *y_list,     /* I */
    float *z_list,     /* I */
    int   *flag_list,  /* I */
    float *y_sort,     /* O */
    float *z_sort,     /* O */
    int   *flag_sort   /* O */
    )
{
    int    i, n, y, seg, echo, sort_index;
    int    index_start, index_end;
    int    views_to_sort, skips_end_total;
    float* s_list;
    float* y_temp;
    float* z_temp;
    int*   flag_temp;
    int*   i_temp;
    float* y_sort_temp;
    float* z_sort_temp;
    int*   flag_sort_temp;

    /* allocate data structures */
    s_list         = (float*)malloc(num_views * sizeof(float));
    y_sort_temp    = (float*)malloc(num_segs*num_echoes * sizeof(float));
    z_sort_temp    = (float*)malloc(num_segs*num_echoes * sizeof(float));
    y_temp         = (float*)malloc(num_segs*num_echoes * sizeof(float));
    z_temp         = (float*)malloc(num_segs*num_echoes * sizeof(float));
    flag_sort_temp = (int*)malloc(num_segs*num_echoes * sizeof(int));
    flag_temp      = (int*)malloc(num_segs*num_echoes * sizeof(int));
    i_temp         = (int*)malloc(num_segs*num_echoes * sizeof(int));

    /*** STEP 1: Sort by Y (with jittering of positions a little to enourage interleaving) ***/

    for (i=0; i<num_views; i++)
    {
        float stride_shift = - 0.99*((int)y_list[i]%ystride);
        float jitter       = (fmod(z_list[i]*PI,8)-4)/10; /* altered a little */
        if (s_list != NULL)
        {
            s_list[i] = y_list[i] + stride_shift + jitter;
        }
    }
    sort_vectors(0, num_views-1, echo_dir, s_list, y_list, z_list, flag_list);

    /*** STEP 2: Assign to Trains ***/

    /* initialize */
    for (i=0; i<num_segs*num_echoes; i++)
    {
        y_sort[i] = 0; /* flag for skipped echo */
        z_sort[i] = 0;
        flag_sort[i] = ZY_FLAGS_SAMPLED; /* use ZY_FLAGS_SAMPLE. don't use ZY_FLAGS_MASK */
        if (y_sort_temp != NULL)
        {
            y_sort_temp[i] = 0;
        }
        if (z_sort_temp != NULL)
        {
            z_sort_temp[i] = 0;
        }
        if (flag_sort_temp != NULL)
        {
            flag_sort_temp[i] = 0;
        }
    }

    /* for each echo, sort by z and distribute to segments */
    for (echo=skips_start; echo<num_echoes; echo++)
    {
        index_start     = (echo-skips_start  )*num_segs;
        index_end       = (echo-skips_start+1)*num_segs-1;
        views_to_sort   = index_end-index_start+1;
        skips_end_total = 0;

        /* last echo may be skipped in some segments */
        if (index_end > num_views-1)
        {
            skips_end_total = index_end - (num_views-1);
            views_to_sort  -= skips_end_total;
            index_end       = (num_views-1);
        }

        /* sort by z */
        copy_vector(views_to_sort, &y_list[index_start], y_temp);
        copy_vector(views_to_sort, &z_list[index_start], z_temp);
        copy_vector_i(views_to_sort, &flag_list[index_start], flag_temp);

        /* segmented views direction added to better accomodate 1/2-nex breath-hold scans */
        sort_vectors(0, views_to_sort-1, seg_dir, z_temp, y_temp, 0, flag_temp);

        /* distribute to segmented views */
        for (i=0; i<views_to_sort; i++)
        {
            seg = i + skips_end_total/2;
            y_sort[seg*num_echoes + echo] = y_temp[i];
            z_sort[seg*num_echoes + echo] = z_temp[i];
            flag_sort[seg*num_echoes + echo] = flag_temp[i];
        }
    }

    /*** STEP 3: Sort by Z for each Y column (to consolidate segmented views / minimize step size) ***/
    for (y=0; y<=yres; y+=ystride)
    {
        /* pull out points in Y column */
        n = 0;
        for (sort_index=0; sort_index<num_segs*num_echoes; sort_index++)
            if (y_sort[sort_index]>=y && y_sort[sort_index]<(y+ystride))
            {
                if (y_temp != NULL)
                {
                    y_temp[n]  = y_sort[sort_index];
                }
                if (z_temp != NULL)
                {
                    z_temp[n]  = z_sort[sort_index];
                }
                if (flag_temp != NULL)
                {
                    flag_temp[n]  = flag_sort[sort_index];
                }
                if (i_temp != NULL)
                {
                    i_temp[n]  = sort_index;
                }
                n = n+1;
            }

        /* sort by Z */
        if (n>1)
            sort_vectors(0, n-1, seg_dir, z_temp, y_temp, 0, flag_temp); /* seg_dir */

        /* rebuild sorted list */
        if (n>0)
            for (i=0; i<n; i++)
            {
                y_sort_temp[i_temp[i]] = y_temp[i];
                z_sort_temp[i_temp[i]] = z_temp[i];
                flag_sort_temp[i_temp[i]] = flag_temp[i];
            }
    }
    copy_vector(num_segs*num_echoes, y_sort_temp, y_sort);
    copy_vector(num_segs*num_echoes, z_sort_temp, z_sort);
    copy_vector_i(num_segs*num_echoes, flag_sort_temp, flag_sort);

    /*** STEP 4: Sort by actual Y within segs (to remove jitter effect) ***/
    for (seg=0; seg<num_segs; seg++)
    {
        /* changed from ascending to descending to accomodate half-nex */
        sort_vectors(seg*num_echoes+skips_start, (seg+1)*num_echoes-2, echo_dir, y_sort, z_sort, 0, flag_sort);
        flag_sort[seg*num_echoes] |= ZY_FLAGS_SEG_START;
    }

    /*** STEP 5: Centric view ordering in segs ***/
    if (phorder == CENTRIC)
    {
        int seg_increment=0, seg_cent=0, seg_index1=0, seg_index2=0, sign=1;

        /* initialization of temporary arrays to zero */
        memset(y_temp, 0, sizeof(float) * num_segs * num_echoes);
        memset(z_temp, 0, sizeof(float) * num_segs * num_echoes);
        memset(flag_temp, 0, sizeof(int) * num_segs * num_echoes);

        /* copy arrays */
        copy_vector(num_segs*num_echoes, y_sort, y_temp);
        copy_vector(num_segs*num_echoes, z_sort, z_temp);
        copy_vector_i(num_segs*num_echoes, flag_sort, flag_temp);

        seg_cent = (num_segs/2);

        for (seg_index1=0; seg_index1<num_segs; seg_index1++)
        {
            /* Sorting */
            sign = (((seg_index1%2) == 0) ? 1: -1);
            seg_increment = seg_increment + seg_index1*sign;

            if (seg_index1 == 0)
            {
                seg_increment = 0;
            }

            seg_index2 = seg_cent + seg_increment;

            if (seg_index2 < 0)
            {
                seg_index2 = 0;
            }

            if (seg_index2 >= num_segs)
            {
                seg_index2 = num_segs-1;
            }

            /* return temporary array into main sort array */
            for (i=0; i<num_echoes; i++)
            {
                y_sort[i+num_echoes*seg_index1] = y_temp[i+num_echoes*seg_index2];
                z_sort[i+num_echoes*seg_index1] = z_temp[i+num_echoes*seg_index2];
                flag_sort[i+num_echoes*seg_index1] = flag_temp[i+num_echoes*seg_index2];
            }
        }
    }

    /* free data structures */
    free(s_list);
    free(y_temp);
    free(z_temp);
    free(flag_temp);
    free(i_temp);
    free(y_sort_temp);
    free(z_sort_temp);
    free(flag_sort_temp);
}

/*  orderviews_z
 *
 *  Description:
 *    Sort k-space encodes into sequential manner kz segments within coner removal.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) int num_views - acquired number of views in segmented views
 *  (I) int num_segs - number of segmented views
 *  (I) int num_echoes - number of views including dummy view
 *  (I) int skips_start - skipped echo at start
 *  (I) int zres - z matrix
 *  (I) int zstride - z stride of ARC or ASSET
 *  (I) int echo_dir - view direction
 *  (I) int seg_dir - view segmentation direction
 *  (I) int phorder - centric flag of  view segmentation direction
 *  (I) float * y_list - array of y view structures
 *  (I) float * z_list - array of z view structures
 *  (I) float * flag_list - array of flag structures
 *  (O) float * y_sort - sorted array of y view structures
 *  (O) float * z_sort - sorted array of z view structures
 *  (O) float * flag_sort - sorted array of flag structures
 */

/* based on orderviews_z() in ARC_3dfse.e */
void orderviews_z(
    int   num_views,   /* I */
    int   num_segs,    /* I */
    int   num_echoes,  /* I */
    int   skips_start, /* I */
    int   zres,        /* I */
    int   zstride,     /* I */
    int   echo_dir,    /* I */
    int   seg_dir,     /* I */
    int   phorder,     /* I */
    float *y_list,     /* I */
    float *z_list,     /* I */
    int   *flag_list,  /* I */
    float *y_sort,     /* O */
    float *z_sort,     /* O */
    int   *flag_sort   /* O */
    )
{
    /* just swap y and z arguments */
    orderviews_y(num_views, num_segs, num_echoes, skips_start, zres, zstride, echo_dir, seg_dir, phorder, z_list, y_list, flag_list, z_sort, y_sort, flag_sort);
}

/*  phslGroupSort
 *
 *  Description:
 *    Sort k-space encodes into views_per_segment groups either in slice or phase dir
 *    Supports sequential, reverse sequential and centric ordering in either direction 
 *    Supports arbitrary partial Fourier and non-separable sampling patterns
 * 
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * zy_sort - array of structures for containing all
 *        encodes to sort.  Assumes that dist and angle fields are already
 *        calculated.
 *  (I) const int zy_sort_length - number of elements in zy_sort to sort
 *  (I) const int views_per_segments - number of segments to divide zy_sort into.
 *      if the zy_sort_length / views_per_segment is not an exact integer then  
 *      last segment will have the extra views. 
 */
static STATUS
phslGroupSort(ZY_DIST *zy_sort, const int zy_sort_length, const int views_per_segment)
{
    const char funcName[] = "phslGroupSort";
    int seg, seg_start, vps_curr;
    int total_segments = zy_sort_length / views_per_segment; /* Number of segments */

    /* Sort all encodes by angle */
    qsort(zy_sort, zy_sort_length, sizeof(ZY_DIST), angle_compare);

    seg_start = 0;
    for (seg = 1; seg <= total_segments; seg++)
    {
        /* Calculate length of current segment */
        if (seg < total_segments)
        {
            vps_curr = views_per_segment; 
        }
        else
        {
            vps_curr = zy_sort_length - seg_start;
        }

        /* Defensive check to avoid memory corruption bugs. This should
           never fail. */
        if (seg_start + vps_curr > zy_sort_length)
        {
            printf("%s: seg_start (%d) + vps_curr (%d) > zy_sort_length (%d) for segment %d or %d\n",
                   funcName, seg_start, vps_curr, zy_sort_length, seg, total_segments);
            return FAILURE;
        }

        /* Sort current segment by distance */
        qsort(&(zy_sort[seg_start]), vps_curr, sizeof(ZY_DIST), dist_compare);

        /* Set the segment start flag on the first encode of each segment */
        zy_sort[seg_start].flags |= ZY_FLAGS_SEG_START;

        seg_start += vps_curr;
    }

    return SUCCESS;
}


/*  discosort
 *
 *  Description:
 *    Sort k-space encodes for DISCO.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * zy_sort - array of structures for containing all
 *        encodes to sort.  Assumes that dist and angle fields are already
 *        calculated.
 *  (I) const int zy_sort_length - number of elements in zy_sort to sort
 *  (I) const int segmented_flag - flag for segmentation
 *  (I) const int views_per_segment - number of views per segment
 *  (I/O) PARAM4D * param4d - structure describing segmentation/ordering
 *        scheme
 *
 */
static STATUS
discosort(ZY_DIST *zy_sort, const int zy_sort_length, const int segmented_flag, const int views_per_segment, PARAM4D *param4d)
{
    const char funcName[] = "discosort";
    int reg1_length = 0, reg2_length = 0;
    int vps = 0, reg = 0;
    int j = 0, jst = 0;
    int regi = 0, viewi = 0;
    int subreg = 0;
    int count = 0;
    int vps_res = 0;
    float areg_fr = param4d->aregion_fraction;
    int num_outer_regions = param4d->num_outer_regions;
    int num_sub_regions = param4d->num_sub_regions;
    float num_transition_fraction = param4d->num_transition_fraction;
    int nr_of_seg_reg = 0;
    int subseg = 0, view_subseg = 0;
 
    if ((num_transition_fraction < 0.0) || (num_transition_fraction > 1.0))
    {
        printf("%s: ERROR num_transition_fraction = %f is out of range.\n", funcName, num_transition_fraction);
        return FAILURE;
    }

    ZY_DIST *zy_sort2 = NULL;
    ZY_DIST *zy_sort3 = NULL;

    if (NULL == (zy_sort2 = (ZY_DIST *) malloc(sizeof(ZY_DIST) * zy_sort_length)))
    {
        printf("%s: ERROR Failure allocating zy_sort2.\n", funcName);
        return FAILURE;
    }

    if (segmented_flag)
    {
        /* nr_of_segA is calculated in efgre3d.e */
        reg1_length = param4d->nr_of_segA * views_per_segment;
    }
    else
    {
        reg1_length = (int)(areg_fr*zy_sort_length);
    }
    reg2_length = zy_sort_length-reg1_length;

    if (segmented_flag)
    {
        if ( reg2_length%(views_per_segment*num_sub_regions) != 0 )
        {
            printf("%s: ERROR total number of points not good for segmented_flag ON.\n", funcName);
            free(zy_sort2);
            return FAILURE;
        }
    }
    else
    {
        /* ensure same number of points in interleaved sub regions */
        if (1 == num_outer_regions)
        {
            vps_res = reg2_length % num_sub_regions;
        }
        else
        {
            unsigned int fact = 1;
            for(j=2; j<=num_outer_regions+1; j++)
            {
                fact = fact*j;
            }
            vps_res = reg2_length % (fact*num_outer_regions);
        }
        reg1_length += vps_res;
        reg2_length -= vps_res;
    }
        
    vps = reg2_length/num_outer_regions;

    /* Now for each region, copy successively undersampled versions of zy_sort into zy_sort2 */
    /* Creating central and outer regions */
    for (reg=1; reg <= (num_outer_regions+1); reg++)
    {
        if (1 == reg)
        {
            /* Central region */
            memcpy(&zy_sort2[0], &zy_sort[0], sizeof(ZY_DIST)*reg1_length);
            if ((1.0-__FLT_EPSILON__) < (num_transition_fraction*reg1_length))
            {
                /* re-order A region */
                if (FAILURE == reorder_region(&zy_sort2[0], reg1_length, num_transition_fraction))
                {
                    printf("%s: reorder_region() failed.\n", funcName);
                    free(zy_sort2);
                    return FAILURE;
                }
            }

            if (segmented_flag)
            {
                if (param4d->regViewOrderMode == INTERLEAVE) /* interleaving views */
                {
                    if ((zy_sort3 = (ZY_DIST *) malloc(sizeof(ZY_DIST) * reg1_length)) == NULL)
                    {
                        printf("%s: Failure allocating zy_sort3.\n", funcName);
                        free(zy_sort2);
                        return FAILURE;
                    }

                    memcpy(&zy_sort3[0], &zy_sort2[0], sizeof(ZY_DIST)*reg1_length);

                    nr_of_seg_reg = param4d->nr_of_segA;
                }

                for (j = 0; j < reg1_length; j++)
                {
                    if (param4d->regViewOrderMode == REGULAR)
                    {
                        view_subseg = j%views_per_segment;

                        if (view_subseg == 0)
                        {
                            zy_sort2[j].flags |= ZY_FLAGS_SEG_START;
                        }
                    }
                    else if (param4d->regViewOrderMode == INTERLEAVE) /* interleaving views */
                    {
                        subseg = j%nr_of_seg_reg;
                        view_subseg = j/nr_of_seg_reg;
                        memcpy(&zy_sort2[views_per_segment*subseg+view_subseg], &zy_sort3[j], sizeof(ZY_DIST));

                        if (view_subseg == 0)
                        {
                            zy_sort2[views_per_segment*subseg+view_subseg].flags |= ZY_FLAGS_SEG_START;
                        }
                    }
                }

                if ((NULL != zy_sort3) && (param4d->regViewOrderMode == INTERLEAVE)) /* interleaving views */
                {
                    free(zy_sort3);
                }
            }

            viewi = reg1_length;
            param4d->views_per_region[regi] = viewi;
            regi++;
        }
        else
        {
            /* Two region mode is just A and B with B divided into subregions */
            subreg = ((num_outer_regions==1) ? num_sub_regions: reg);

            for (jst = 0; jst < subreg; jst++)
            {
                count = 0;
                for (j = jst + reg1_length + ((reg-2)*vps); j < reg1_length + ((reg-1)*vps); j += subreg)
                {
                    zy_sort2[viewi].view = zy_sort[j].view;
                    zy_sort2[viewi].slice = zy_sort[j].slice;
                    zy_sort2[viewi].flags = zy_sort[j].flags;
                    zy_sort2[viewi].distance = zy_sort[j].distance;
                    zy_sort2[viewi].angle = zy_sort[j].angle;

                    viewi++;
                    count++;
                }
                param4d->views_per_region[regi] = count;

                if (segmented_flag)
                {
                    int views_per_subregion = param4d->views_per_region[regi];
                    int view_start = 0;
                    int ii = 0;

                    for (ii = 0; ii < regi; ii++)
                    {
                        view_start += param4d->views_per_region[ii];
                    }

                    if (param4d->regViewOrderMode == INTERLEAVE) /* interleaving views */
                    {
                        if ((zy_sort3 = (ZY_DIST *) malloc(sizeof(ZY_DIST) * views_per_subregion)) == NULL)
                        {
                            printf("%s: Failure allocating zy_sort3.\n", funcName);
                            free(zy_sort2);
                            return FAILURE;
                        }
                        memcpy(&zy_sort3[0], &zy_sort2[view_start], sizeof(ZY_DIST)*views_per_subregion);
                        nr_of_seg_reg = (int)ceil((float)views_per_subregion/(float)views_per_segment);
                    }

                    for (j = view_start; j < view_start + views_per_subregion; j++)
                    {
                        if (param4d->regViewOrderMode == REGULAR)
                        {
                            view_subseg = (j-view_start)%views_per_segment;
                            if (view_subseg == 0)
                            {
                                zy_sort2[j].flags |= ZY_FLAGS_SEG_START;
                            }
                        }
                        else if (param4d->regViewOrderMode == INTERLEAVE) /* interleaving views */
                        {
                            subseg = (j-view_start)%nr_of_seg_reg;
                            view_subseg = (j-view_start)/nr_of_seg_reg;
                            memcpy(&zy_sort2[views_per_segment*subseg+view_subseg+view_start], &zy_sort3[j-view_start], sizeof(ZY_DIST));

                            if (view_subseg == 0)
                            {
                                zy_sort2[views_per_segment*subseg+view_subseg+view_start].flags |= ZY_FLAGS_SEG_START;
                            }
                        }
                    }

                    if ((NULL != zy_sort3) && (param4d->regViewOrderMode == INTERLEAVE)) /* interleaving views */
                    {
                        free(zy_sort3);
                    }
                }
                regi++;
            }
        }
    }

    /* Copy entire zy_sort2 back to zy_sort */
    memcpy(&zy_sort[0], &zy_sort2[0], sizeof(ZY_DIST)*zy_sort_length);

    free(zy_sort2);
    return SUCCESS;
}

/*  reorder_region
 *
 *  Description:
 *    Sort DISCO A region to include transition points between B region and
 *    center of A region
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * region_sort - array of structures for containing all
 *        encodes to sort.  Assumes that it has already been sorted with EC
 *  (I) const int region_length - number of elements in region_sort to sort
 *  (I) const float num_transition_fraction - fraction of A region to use
 *      for transition.
 */
static STATUS
reorder_region(ZY_DIST *region_sort, const int region_length, const float num_transition_fraction)
{
    const char funcName[] = "reorder_region";

    int ii = 0;
    float d_reserve = 0;

    const float left_fraction = num_transition_fraction;
    int left_counts = 0; /* count of encodes from edge of A region to center */
    int right_counts = 0; /* count of encodes from center to edge of A region */
    int *left_idx = NULL;
    int *right_idx = NULL;

    ZY_DIST* tmp_samples = NULL;

    if (NULL == (left_idx = (int*) malloc(region_length*sizeof(int))))
    {
        printf("%s: Failure allocating left_idx.\n", funcName);
        return FAILURE;
    }

    if (NULL == (right_idx = (int*) malloc(region_length*sizeof(int))))
    {
        printf("%s: Failure allocating right_idx.\n", funcName);
        free(left_idx);
        return FAILURE;
    }

    if (NULL == (tmp_samples = (ZY_DIST*) malloc(region_length*sizeof(ZY_DIST))))
    {
        printf("%s: Failure allocating tmp_samples.\n", funcName);
        free(left_idx);
        free(right_idx);
        return FAILURE;
    }

    memset(tmp_samples, 0, (size_t)(region_length*sizeof(ZY_DIST)));

    for (ii = 0; ii < region_length; ii++)
    {
        d_reserve += left_fraction;
        if (1 <= d_reserve)
        {
            left_idx[left_counts] = ii;
            left_counts++;
            d_reserve--;
        }
        else
        {
            right_idx[right_counts] = ii;
            right_counts++;
        }
    }

    for (ii = 0; ii < left_counts; ii++)
    {
        tmp_samples[ii] = region_sort[left_idx[left_counts-1-ii]];
    }

    for (ii = 0; ii < right_counts; ii++)
    {
        tmp_samples[left_counts+ii] = region_sort[right_idx[ii]];
    }

    memcpy(region_sort, tmp_samples, (size_t)(region_length*sizeof(ZY_DIST)));

    free(left_idx);
    free(right_idx);
    free(tmp_samples);

    return SUCCESS;
}


/* MRIhc10955: TRICKS enhancement for HD Lower Leg */

/*  tricksRegionSort
 *
 *  Description:
 *    Sort k-space encodes into total_segments radial fan segments.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * zy_sort - array of structures for containing all
 *        encodes to sort.  Assumes that dist and angle fields are already
 *        calculated.  Assumes encodes ordered A, B ... in structure.
 *  (I) const int zy_sort_length - number of elements in zy_sort to sort.
 *        Must be evenly divisible by regions.
 *  (I) const int regions - number of TRICKS regions (A,B,C, D so on)
 *  (I) int transition_views - number of views per transition beam between regions.
 *
 */
static STATUS
tricksRegionSort(ZY_DIST *zy_sort, const int zy_sort_length, const int regions,
                 const int transition_views)
{
    const CHAR * funcName = "tricksRegionSort";
    int reg, i, j, tmp_transition_views;

    if (transition_views > 0)
    {
        int vpr = zy_sort_length / regions; /* Views per TRICKS region */
        ZY_DIST *zy_tricks = NULL; /* Structure to create transition regions */

        if (vpr * regions != zy_sort_length)
        {
            printf("%s: zy_sort_length is not divisible by the number of regions!\n", funcName);
            return FAILURE;
        }

        if ((zy_tricks = (ZY_DIST *) malloc(sizeof(ZY_DIST) * vpr)) == NULL)
        {
            printf("%s: Failure allocating zy_tricks.\n", funcName);
            return FAILURE;
        }

        memset(zy_tricks, 0, sizeof(ZY_DIST) * vpr);

        for (reg = 0; reg < regions; reg++)
        {
            tmp_transition_views = IMax(2,transition_views - 6*reg, 6);
            /* Copy current region to temporary buffer */
            memcpy(zy_tricks, &(zy_sort[reg*vpr]), sizeof(ZY_DIST) * vpr);

            /* Sort all encodes by angle */
            qsort(zy_tricks, vpr, sizeof(ZY_DIST), angle_compare);

            /* Sort the tmp_transition_views (selected based on angular position)
               encodes by reverse distance for smooth region transition */
            qsort(zy_tricks,tmp_transition_views, sizeof(ZY_DIST), dist_compare_rev);

            /* Sort the remaining encodes by spectal distance */
            qsort(&(zy_tricks[tmp_transition_views]), vpr - tmp_transition_views,
                  sizeof(ZY_DIST), dist_compare);

            /* Put the transition region to beginning of region A and at the end of other regions */
            if (0 == reg)
            {
                memcpy(&(zy_sort[reg*vpr]), zy_tricks, sizeof(ZY_DIST) * vpr);
            }
            else
            {
                for (i=0; i< vpr; i++)
                {
                    if (i < tmp_transition_views)
                    {
                        j = vpr - tmp_transition_views + i;
                    }
                    else
                    {
                        j = i - tmp_transition_views;
                    }

                    memcpy(&(zy_sort[reg*vpr + j]), &(zy_tricks[i]), sizeof(ZY_DIST));
                }
            }
        }

        free(zy_tricks);
    }

    return SUCCESS;
}

/*  markSegStart
 *
 *  Description:
 *    Mark segment starts for segmented (non-radial fan beam) acquisitions.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - status of function (SUCCESS or FAILURE)
 *  (I/O) ZY_DIST * zy_sort - array of structures for containing all
 *        encodes to sort.  Assumes that dist and angle fields are already
 *        calculated.
 *  (I) const int zy_sort_length - number of elements in zy_sort to sort
 *  (I) const int total_segments - number of segments to divide zy_sort into.
 *        If zy_sort_length/total_segments is not an integer, it will divide
 *        into total_segments with variable length as close to
 *        zy_sort_length/total_segments as possible.
 *
 */
static STATUS
markSegStart(ZY_DIST *zy_sort, const int zy_sort_length, const int total_segments)
{
    const char funcName[] = "markSegStart";
    int seg, seg_start, vps_curr;
    float vps_target;

    /* Calculate desired views per segments */
    vps_target = (float)zy_sort_length / (float)total_segments;

    seg_start = 0;
    for (seg = 1; seg <= total_segments; seg++)
    {
        /* Calculate length of current segment */
        if (seg < total_segments)
        {
            vps_curr = (int)floor(seg*vps_target + 0.5) - seg_start;
        }
        else
        {
            vps_curr = zy_sort_length - seg_start;
        }

        /* Defensive check to avoid memory corruption bugs. This should
           never fail. */
        if (seg_start + vps_curr > zy_sort_length)
        {
            printf("%s: seg_start (%d) + vps_curr (%d) > zy_sort_length (%d) for segment %d or %d\n",
                   funcName, seg_start, vps_curr, zy_sort_length, seg, total_segments);
            return FAILURE;
        }

        /* Set the segment start flag on the first encode of each segment */
        zy_sort[seg_start].flags |= ZY_FLAGS_SEG_START;

        seg_start += vps_curr;
    }

    return SUCCESS;
}

/*  onAccelGrid
 *
 *  Description:
 *  This function reports whether a certain voxel falls on the
 *  accelerated cartesian grid locations or not.
 *  calibration region covers the center of kspace.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (O) return INT - true if index falls on acceleration grid.
 *  (I) const INT index - current kspace index (zero based)
 *  (I) const FLOAT outerReductionFactor - Outer reduction factor
 */
static INT
onAccelGrid(const INT index, const FLOAT outerReductionFactor)
{
    return (((INT)(100*index) % (INT)(100.0*outerReductionFactor))<100);
}

/*  inCalBorder
 *
 *  Description:
 *  This function reports whether a certain voxel falls within the
 *  box bounded by the borders of the calibration region end points.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (O) return INT - true if index is within the borders of the
 *                   box that encompasses the calibration region.
 *  (I) const INT index - current kspace index (zero based)
 *  (I) const INT cutoffLower - Lower calibration border (zero based)
 *  (I) const INT cutoffUpper - Upper calibration border (zero based)
 */
static INT
inCalBorder(const INT index, const INT cutoffLower, const INT cutoffUpper)
{
    return ((index >= cutoffLower ) && (index <= cutoffUpper));
}

/*  calibration_voxel
 *
 *  Description:
 *  This function decides whether or not a certain voxel belongs to the
 *  fully-sampled calibration region. The assumption is that the
 *  calibration region covers the center of kspace.
 *
 *  Supported sampling types are CROSS_CAL, BOX_CAL and ELLIPTICAL_CAL.
 *  The function returns 1 if the voxel is in the calibration region or
 *  0 otherwise.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) return INT - true if voxel is a calibration voxel
 *  (I) const INT phase - View number (zero based) in fully-sampled k-space
 *  (I) const INT slice - Slice number (zero based) in fully-sampled k-space
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 */
static INT
calibration_voxel(const INT phase, const INT slice, const CAL_PARAM calRegion)
{
    INT cal_voxel = 0;
    INT phasecal, slicecal;
    FLOAT cal_y, cal_z, cal_r;

    switch (calRegion.shape)
    {
    case CROSS_CAL:
    case BOX_CAL:
        phasecal = inCalBorder(phase,calRegion.phaseCutoffLower, calRegion.phaseCutoffUpper);
        slicecal = inCalBorder(slice,calRegion.sliceCutoffLower, calRegion.sliceCutoffUpper);

        cal_voxel = (phasecal && slicecal) ? 1 : 0;
        break;

    case ELLIPTICAL_CAL:
        cal_y = (FLOAT)phase - calRegion.phaseOrigin;
        cal_z = (FLOAT)slice - calRegion.sliceOrigin;
        cal_r = ((cal_y*cal_y)/(calRegion.phaseRadius * calRegion.phaseRadius)) +
            ((cal_z*cal_z)/(calRegion.sliceRadius * calRegion.sliceRadius));

        /* Inclusive of ellipse boundary */
        cal_voxel = (cal_r <= 1) ? 1 : 0;
        break;
    }

    return cal_voxel;
}

/*  accelerated_voxel
 *
 *  Description:
 *  This function decides whether or not a certain voxel is sampled in
 *  partially parallel self-calibrated acqusitions. It calls calibration_voxel()
 *  to mark all calibration voxels as sampled.  Outside the calibration region,
 *  the decision is based on the prescribed acceleration parameters.
 *
 *  Supported sampling types are CROSS_CAL, BOX_CAL and ELLIPTICAL_CAL.
 *  The function returns 1 if the voxel is sample region or 0 otherwise.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) return INT - true if voxel is sampled
 *  (I) const INT phase - View number (zero based) in fully-sampled k-space
 *  (I) const INT slice - Slice number (zero based) in fully-sampled k-space
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 *  (I) const FLOAT phOuterReductionFactor - Outer acceleration factor in
 *                                           phase direction (>= 1)
 *  (I) const FLOAT slOuterReductionFactor - Outer acceleration factor in
 *                                           slice direction (>= 1)
 */
static INT
accelerated_voxel(const INT phase, const INT slice, const CAL_PARAM calRegion,
                  const FLOAT phOuterReductionFactor,
                  const FLOAT slOuterReductionFactor)
{
    INT sample = 0;
    INT phsample, slsample;

    /*  Round to the nearest integer */
    phsample = onAccelGrid(phase, phOuterReductionFactor);
    slsample = onAccelGrid(slice, slOuterReductionFactor);

    switch (calRegion.shape)
    {
    case BOX_CAL:
    case ELLIPTICAL_CAL:
        if ( phsample  && slsample )
        {
            sample = 1;
        }
        break;
    case CROSS_CAL:
        if ( phsample  && slsample )
        {
            sample = 1;
        }
        /* If the encodes falls on arms of the cross */
        else if ( slsample &&
                  inCalBorder(phase,calRegion.phaseCutoffLower, calRegion.phaseCutoffUpper) )
        {
            sample = 1;
        }

        else if ( phsample &&
                  inCalBorder(slice,calRegion.sliceCutoffLower, calRegion.sliceCutoffUpper) )
        {
            sample = 1;
        }
        break;
    }

    return sample;
}

/* markXzDone
 *
 *  Description:
 *    Set the XZ_DONE flag in the zy_sort table to indicate when all the
 *    slices for a particular xz-plane have been acquired.  Assumes that the
 *    frames are acquired in the order the appear in the zy_sort table.
 *    Also assumes that the first sampledPoints elements of zy_sort
 *    contain the sampled and calibration data.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) STATUS return variable - Did function complete successfully.
 *  (I/O) ZY_EXPORT *zy_export - Playout order structure
 *  (I) const INT sampledPoints - Number of encodes sampled (including
 *        calibration encodes)
 *
 */
static STATUS
markXzDone(ZY_EXPORT *zy_export, const INT sampledPoints)
{
    INT n;
    const char funcName[] = "markXzDone";
    n8 *xzPlanes = NULL;
    INT maxView = 0;

    /* Find maximum view acquired (Search rather than passing as argument
       to avoid potential memory corruption using wrong argument) */
    for (n=0; n < sampledPoints; n++)
    {
        if (zy_export[n].view > maxView)
        {
            maxView = zy_export[n].view;
        }
    }
    /* Increment maxView such that it is the # of views to allocate */
    maxView++;

    /* Allocate buffer to keep track of XZ-planes completed */
    xzPlanes = (n8 *) malloc(sizeof(n8) * maxView);
    if (NULL == xzPlanes)
    {
        printf("%s: malloc memory for xzPlanes failed!\n", funcName);
        return FAILURE;
    }

    /* Initialize all XZ-planes */
    memset(xzPlanes, 1, sizeof(n8) * maxView);

    /* Loop through the playout in reverse order.  Mark each plane as done
       the last time that a view is played-out */
    for (n = sampledPoints - 1; n >= 0; n--)
    {
        if (xzPlanes[zy_export[n].view])
        {
            zy_export[n].flags |= ZY_FLAGS_XZ_DONE;
            xzPlanes[zy_export[n].view] = 0;
        }
        else
        {
            /* Clear the flag for all other views */
            zy_export[n].flags &= ~ZY_FLAGS_XZ_DONE;
        }
    }

    free(xzPlanes);
    return SUCCESS;
}

/* slice_order_efgre3d
 *
 *  Description:
 *    Calculate slice encode order.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) return variable - status of function (SUCCESS or FAILURE)
 *  (O) INT slicetab[] - Slice order table.  Must be allocated to with
 *        zy_slices elements.  zero-based indicies.
 *  (I) const INT zy_slices - Number of slices (fully sampled for ARC)
 *  (I) const INT slorder - Slice order
 *  *** Extra SPECIAL parameters ***
 *  (I) const INT nsegments - number of segments
 *  (I) const INT chemseqs  - number of acquisitions per segment
 *  (I) const INT chemseq0  - number of acquisitions after the Extra SpecIR pulse
 *  (I) const INT linestodiscard - number of discarded lines in order to segment
 *                 total acquired slices with Extra SpecIR pulse
 *  *** Partial kz parameters ***
 *  (I) const INT pfkz_flag - Partial kz
 *  (I) const INT pfkz_total - number of acquired kz lines
 *  (I) const INT pfkz_segments - Partial kz number of segments
 *  (I) const INT pfkz_views_per_segment - Partial kz number of encodes per
 *        segment
 *  *** ARC parameters ***
 *  (I) const INT arc_flag - Set if ARC is enabled
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 *  (I) const FLOAT arc_sl_stride - ARC slice outer reduction factor
 *  (I) INT *extraspecial_slice - Physical Slices including dummy slices
 */
static STATUS
slice_order_efgre3d(INT *slicetab,
                    const INT zy_slices,
                    const INT slorder,
                    const INT nsegments,
                    const INT chemseqs,
                    const INT chemseq0,
                    const INT linestodiscard,
                    const INT pfkz_flag,
                    const INT pfkz_total,
                    const INT pfkz_segments,
                    const INT pfkz_views_per_segment,
                    const INT arc_flag,
                    const CAL_PARAM calRegion,
                    const FLOAT arc_sl_stride,
                    INT *extraspecial_slice)
{
    int j, accelerated_data, cal_data;
    const char funcName[] = "slice_order_efgre3d";
    /* Vector mapping accelerated slices to fully sampled slices */
    int acq2full[zy_slices];
    int acqSlices = zy_slices;

    if (0 > pfkz_total)
    {
        printf("%s: Array access out of bounds\n", funcName);
        return FAILURE;
    }

    /* If not slice acceleration with cross sampling, calculate
       using fully sampled slice numbers */
    for (j=0; j < zy_slices; j++)
    {
        acq2full[j] = j;
    }

    if (arc_flag && (CROSS_CAL == calRegion.shape) && (arc_sl_stride > 1.0))
    {
        /* Using cross calibration with slice acceleration.
           Calculate slice order using only the slices acquired without
           considering pfkz */
        acqSlices = 0;

        /* Count acquired slice and generate mapping from acquired to
           fully sampled slice numbers */
        for (j=0; j < zy_slices; j++)
        {
            /* Just use view 0 and arc_ph_stride 1.0 since the slice pattern
               is independent of the view pattern for cross sampling */
            accelerated_data = accelerated_voxel(0, j, calRegion,
                                                 1.0, arc_sl_stride);
            cal_data = calibration_voxel(0, j, calRegion);

            if (accelerated_data || cal_data)
            {
                acq2full[acqSlices] = j;
                acqSlices++;
            }
            else
            {
                /* Not acquired.  Just keep the original slice number */
                slicetab[j] = j;
            }
        }
    }

    /* Calculate slice order for acquired slices */
    if (pfkz_flag)
    {
        /* Handle segmentation for pfkz */
        int last_slice = pfkz_total - 1;
        int segment_cnt, slice_cnt, origSlice, newSlice;

        for (segment_cnt = 0; segment_cnt < pfkz_segments; segment_cnt++)
        {
            for (slice_cnt = 0 ; slice_cnt < pfkz_views_per_segment ; slice_cnt++ )
            {
                origSlice = segment_cnt * pfkz_views_per_segment + slice_cnt;
                newSlice = (last_slice - segment_cnt) - pfkz_segments * slice_cnt;
                if ((origSlice < acqSlices) && (origSlice < pfkz_total))
                {
                    /* NOTE: acqSlices should be less than pfkz_total,
                       but check both anyways because if > acqSlices
                       we will access non-initialized memory */
                    slicetab[acq2full[origSlice]] = acq2full[newSlice];
                }
                else
                {
                    /* Invalid slice number */
                    printf("%s: WARNING: pfkz_segments (%d) * "
                           "pfkz_views_per_segment (%d) < "
                           "acqSlices (%d) or pfkz_total (%d)\n",
                           funcName, pfkz_segments,
                           pfkz_views_per_segment, acqSlices, pfkz_total);
                }
            }
        }

        /* Fill slices not acquired with sequential order */
        for (j=pfkz_total; j < acqSlices; j++)
        {
            slicetab[acq2full[j]] = acq2full[j];
        }
    }
    else
    {
        /* No partial kz, just use irslice to calculate slice order
           based on packed slice number */

        if (5 == slorder)
        {
            /* IMPORTANT: These cutoffs should match the scancore lowercutoff
               and uppercutoff values in efgre3d.e */

            /* smallest kz line number to acquire */
            int extraSpecialLowerCutoff = floor((float)(linestodiscard)/2);
            /* largest kz line number to acquire + 1 */
            int extraSpecialUpperCutoff = acqSlices + extraSpecialLowerCutoff;

            int n = 0;
            for (j=0; j < acqSlices + linestodiscard; j++)
            {
                int newSlice = irslice(j, acqSlices, slorder,
                                       nsegments, chemseqs, chemseq0);

                /* Save the physical slices including dummy slices in extraspecial_slice*/
                extraspecial_slice[j] = newSlice;

                /*Acquired Slices are saved in slicetab*/
                if ((newSlice >= extraSpecialLowerCutoff) &&
                    (newSlice < extraSpecialUpperCutoff))
                {
                    /* This slice is acquired */
                    slicetab[acq2full[n]] = acq2full[newSlice-extraSpecialLowerCutoff];
                    n++;
                }

                if (n > acqSlices)
                {
                    /* NOTE: n should always be less than acqSlices but
                       check anyways because if > acqSlices we will
                       exceed the allocated array */

                    /* Invalid slice number */
                    printf("%s: Extra-SPECIAL slice order failed.\n", funcName);
                    return FAILURE;
                }
            }
        }
        else
        {
            /* Not Extra-SPECIAL, just loop through acquired slices */
            for (j=0; j < acqSlices; j++)
            {
                int newSlice = irslice(j, acqSlices, slorder,
                                       nsegments, chemseqs, chemseq0);

                slicetab[acq2full[j]] = acq2full[newSlice];
            }
        }
    }

    return SUCCESS;
}

/* irslice
 *
 *  Description:
 *    Reorder the slices based on the inputs and return the reordered slice
 *    number for the given input slice index.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - Reordered slice
 *  (I) const INT index - Input slice
 *  (I) const INT nSlices - Number of slices
 *  (I) const INT slorder - Slice order
 *  (I) const INT nsegments - Extra SPECIAL: number of segments
 *  (I) const INT chemseqs  - Extra SPECIAL: number of acquisitions per segment
 *  (I) const INT chemseq0  - Extra SPECIAL: number of acquisitions after the
 *        SpecIR pulse
 *
 */
static INT
irslice(const INT index, const INT nSlices, const INT slorder,
        const INT nsegments, const INT chemseqs, const INT chemseq0)
{
    INT center;
    INT slice_num=0;
    INT kzlines;
    INT rownumber;
    INT columnnumber;

    switch (slorder)
    {
    case 1:
        center = nSlices/2;
        if ((index % 2) == 1)
            slice_num = center - index/2 - 1;
        else
            slice_num = center + index/2;
        break;

    case 2:
        center = nSlices/2;
        if (index  < center)
            slice_num = center + index;
        else
            slice_num = center - (index - nSlices/2 + 1);
        break;

    case 3:
        center = nSlices/2;
        if (index < nSlices/4)
            slice_num = center + index*2;
        else if (index < nSlices/2)
            slice_num = center - (index - nSlices/4)*2 - 1;
        else if (index < 3*nSlices/4 )
            slice_num = center + (index - nSlices/2)*2 + 1;
        else
            slice_num = center - (index - 3*nSlices/4)*2 - 2;
        break;

    case 4:
        center = nSlices/2;
        if (index < nSlices/8)
            slice_num = center + index*4;
        else if (index < nSlices/4)
            slice_num = center - (index - nSlices/8)*4 - 1;
        else if (index < 3*nSlices/8 )
            slice_num = center + (index - nSlices/4)*4 + 1;
        else if (index < nSlices/2)
            slice_num = center - (index - 3*nSlices/8)*4 - 2;
        else if (index < 5*nSlices/8)
            slice_num = center + (index - nSlices/2)*4 + 2;		
        else if (index < 3*nSlices/4)
            slice_num = center - (index - 5*nSlices/8)*4 - 3;		
        else if (index < 7*nSlices/8)
            slice_num = center + (index - 3*nSlices/4)*4 + 3;		
        else
            slice_num = center - (index - 7*nSlices/8)*4 - 4;
        break;

    case 5:

        /* BBA - Improved SPECIAL
           chemseq0 is the number of acquisitions after the SpecIR pulse
           prior to the central points in Kz space
           e.g. if arc_equant=32, chemseqs = 8, and chemseq0=4,
           then the following is the order of Kz acquisition after application of specIR pulse:
           IR 3, 7, 11, 15, 19, 23, 27, 31,
           IR 4, 8, 12, 16, 20, 24, 28, 0,
           IR 5, 9, 13, 17, 21, 25, 29, 1,
           IR 6, 10, 14, 18, 22, 26, 30, 2, */

        kzlines = nsegments*chemseqs;
        rownumber = ceil((float)(index)/chemseqs+0.00001);
        columnnumber = fmod(index, chemseqs);
        slice_num = ceil(kzlines/2.0) + (rownumber - ceil(nsegments/2.0))+ (columnnumber-chemseq0)*nsegments;
        if (slice_num >= kzlines) {
            slice_num = slice_num - kzlines;
        }
        if (slice_num < 0) {
            slice_num = slice_num + kzlines;
        }
        break;

    case 0:
        slice_num = index;
        break;
    }

    return (slice_num);
}

/* countSampledPoints
 *
 *  Description:
 *    Count the number of points in the zy_sort table that are sampled
 *    (and not mask points).
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - Number of sampled points
 *  (I) const ZY_DIST *zy_sort - Playout order structure
 *  (I) const INT zy_sort_length - Number of elements in zy_sort
 */
static INT
countSampledPoints(const ZY_DIST *zy_sort, const INT zy_sort_length)
{
    INT sampledPoints = 0;
    int i;

    for (i = 0; i < zy_sort_length; i++)
    {
        if (!(zy_sort[i].flags & ZY_FLAGS_MASK) &&
            (zy_sort[i].flags & ZY_FLAGS_SAMPLED))
        {
            sampledPoints++;
        }
    }

    return sampledPoints;
}

/*  arcPackBam
 *
 *  Description:
 *  For non-fullySampled acquisitions (parallel imaging, partial-ky, partial-kz),
 *  a ZY_EXPORT table calculated using the fully sampled data will have sections
 *  of k-space not populated with data.  This function collapses the data along
 *  y and z to reduce the amount of data acquired while preserving the basic
 *  relationship between the data frames.  This is done by identifying all views
 *  that have no slices acquired and all slices that have no views acquired.
 *  The phaseIndexRemap and sliceIndexRemap then are filled with the "packed"
 *  phase and slice.  In the acquisition DAB packets, the dabview and dabslice
 *  can be calculated as follows:
 *
 *    dabview = phRemapTable[zy_export.view] + 1;
 *    dabslice = slRemapTable[zy_export.slice];
 *
 *  For a cross-sampled ARC acquisition, all of the unaccelerated view can
 *  be removed using these remapping vectors.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT *phRemapTable - Vector containing mapping from view to packed view
 *        (zero-based, no baselines).  Any used views are set to
 *        ARC_UNUSED_ENCODE.  Vector with unaccelPhases elements must be
 *        allocated prior to function call.
 *  (O) INT *slRemapTable - Vector containing mapping from slice to packed
 *        slice (zero-based).  Any used views are set to ARC_UNUSED_ENCODE.
 *        Vector with unaccelSlices elements must be allocated prior to
 *        function call.
 *  (0) INT packedPhases - Number of y-phase encodes after packing
 *  (O) INT packedSlices - Number of z-phase encodes after packing
 *  (I) const ZY_EXPORT *zy_export - Vector of view and slices to be acquired
 *  (I) const INT zyExpLength - Number of elements in of zy_export
 *        to search for acquired views and slices
 *  (I) const INT unaccelPhases - Number of unaccelerated y-phase encodes
 *  (I) const INT unaccelSlices - Number of unaccelerated z-phase encodes
 */
STATUS
arcPackBam(INT *phRemapTable, INT *packedPhases,
           INT *slRemapTable, INT *packedSlices,
           const ZY_EXPORT *zy_export, const INT zyExportLength,
           const INT unaccelPhases, const INT unaccelSlices)
{
    INT n, count;
    const char funcName[] = "arcPackBam";

    /* Initialize arrays to "unused" */
    for (n = 0; n < unaccelPhases; n++)
    {
        phRemapTable[n] = ARC_UNUSED_ENCODE;
    }

    for (n = 0; n < unaccelSlices; n++)
    {
        slRemapTable[n] = ARC_UNUSED_ENCODE;
    }

    /* Mark all views sampled in any slices and all slices sampled in any frame */
    for (n = 0; n < zyExportLength; n++)
    {
        if (zy_export[n].flags & ZY_FLAGS_SAMPLED)
        {
            phRemapTable[zy_export[n].view] = 1;
            slRemapTable[zy_export[n].slice] = 1;
        }

        /* Catch errors while they are easy to debug */
        if (zy_export[n].view >= unaccelPhases)
        {
            printf("%s: view (%d) out of range (0 < view < %d)\n", funcName,
                   zy_export[n].view, unaccelPhases);
            return FAILURE;
        }

        if (zy_export[n].slice >= unaccelSlices)
        {
            printf("%s: slice (%d) out of range (0 < slice < %d)\n", funcName,
                   zy_export[n].slice, unaccelSlices);
            return FAILURE;
        }
    }

    /* Collapse along y */
    count = 0;
    for (n = 0; n < unaccelPhases; n++)
    {
        if (1 == phRemapTable[n])
        {
            phRemapTable[n] = count;
            count++;
        }
    }
    *packedPhases = count;

    /* Collapse along z */
    count = 0;
    for (n = 0; n < unaccelSlices; n++)
    {
        if (1 == slRemapTable[n])
        {
            slRemapTable[n] = count;
            count++;
        }
    }
    *packedSlices = count;

    return SUCCESS;
}

/* calcPfkyzTotalUnaccel
 *
 *  Description:
 *    Calculate the encode index for partial ky/kz in self-calibrated parallel imaging
 *    assuming a cross pattern.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - full kspace index of the cutoff point on a (zero based).
 *  (I) const INT pfkPoints - Number of acq encodes with parallel imaging in pfky/z.
 *  (I) const INT cutoffLower - Lower boundary for calibration region
 *  (I) const INT cutoffUpper - Upper boundary for calibration region
 *  (I) const FLOAT outerReductionFactor - Outer acceleration factor (>= 1)
 *
 */
INT
calcPfkyzTotalUnaccel(const INT pfkPoints, const INT cutoffLower, const INT cutoffUpper,
                      const FLOAT outerReductionFactor)
{
    INT pfkCounter = 0;
    INT fullInd = 0;
    INT sampledPoint, calPoint;

    while (pfkCounter < pfkPoints)
    {
        /*  Round to the nearest integer */
        sampledPoint = onAccelGrid(fullInd, outerReductionFactor);
        calPoint =  inCalBorder(fullInd, cutoffLower, cutoffUpper);

        if (sampledPoint || calPoint)
        {
            pfkCounter++;
        }
        fullInd++;
    }

    return fullInd;
}

/* calcAccelEncodeNum
 *
 *  Description:
 *    Calculate the encode index for partial ky/kz in self-calibrated parallel imaging
 *    assuming a cross pattern.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - number of accelerated encodes on a full kspace basis (zero based).
 *  (I) INT cutoffLower - Lower boundary for calibration region
 *  (I) INT cutoffUpper - Upper boundary for calibration region.
 *  (I) const INT unaccelEncodes - Number of Encodes for fully sampled data
 *  (I) const FLOAT outerReductionFactor - Outer acceleration factor (>= 1)
 */
INT
calcAccelEncodeNum(const INT cutoffLower, const INT cutoffUpper,
                   const INT unaccelEncodes, const FLOAT outerReductionFactor)
{

    INT accelEncodes = 0;
    INT sampledPoint, calPoint, i;

    for (i= 0; i < unaccelEncodes; i++)
    {
        /*  Round to the nearest integer */
        sampledPoint = onAccelGrid(i, outerReductionFactor);
        calPoint = inCalBorder(i, cutoffLower, cutoffUpper);

        if (sampledPoint || calPoint)
        {
            accelEncodes++;
        }
    }
    return accelEncodes;
}

/*  crossCalBoundary
 *
 *  Description:
 *    Calculate the start and end encode of the cross sampling pattern calibration
 *    region. The calibration region is larger than what is originally prescribed
 *    when a sampled kz/ky line(s) falls right next to the original boundary. Function checks
 *    outer acceleration step size distance in both upper and lower cutoff directions to
 *    add the extra calibration lines due to sampling pattern to the originally prescribed
 *    calibration region.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT *cutoffLowerNew - First encode of calibration region (zero based)
 *  (O) INT *cutoffUpperNew - Last encode of calibration region (zero based)
 *  (I) const INT cutoffLowerOld - First encode of prescribed calibration region (zero based)
 *  (I) const INT cutoffUpperOld - Last encode of prescribed calibration region (zero based)
 *  (I) const FLOAT orFactor - Outer reduction factor along the encoded dimension
 *
 */
STATUS
crossCalBoundary(INT *cutoffLower, INT *cutoffUpper,
                 const FLOAT orFactor, const INT upperLimit)
{
    INT i;

    for (i = *cutoffUpper + 1; i < upperLimit; i++)
    {
        if (!(onAccelGrid(i, orFactor)))
        {
            break;
        }
    }
    *cutoffUpper = i - 1;

    for (i = *cutoffLower -1; i > 0; i--)
    {
        if (!(onAccelGrid(i, orFactor)))
        {
            break;
        }
    }
    *cutoffLower = i + 1;

    return SUCCESS;
}

/*  generateZyExport
 *
 *  Description:
 *    Generate zy_export structure containing encodes to playout in the view
 *    order requested.  This includes all efgre3d view and slice orderings and
 *    also handles fractional NEX, partial kz, and partial kr.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (O) ZY_EXPORT * zy_export - Array of structures containing y and z phase
 *        encode playout order.  Must be allocated to zy_views*zy_slice elements
 *  (I/O) int * delay_ec_framesIO - Number of frames to delay for delayed
 *        elliptic centric view orders.  If the requested delay is greater than
 *        the number of frames, this is set to the max number of frames.
 *  (I) const int zy_views - Number of views (fully sampled for ARC)
 *  (I) const int zy_slices - Number of slices (fully sampled for ARC)
 *  (I) const int ellipt_flag - Use elliptic centric view order
 *  (I) const int reverse_ellipt_flag - Use reverse elliptic centric view order
 *  (I) const int radfb_flag - Use radial fan beam view order
 *  (I) const float fn - Fractional NEX (pfky)
 *  (I) const int pfky_total_unaccel - Fractional NEX min view number to skip
 *  (I) const int pfkz_flag - Partial kz
 *  (I) const int pfkz_total_unaccel - Partial kz min slice number to skip
 *  (I) const int pfkz_total - Number of slices after pfkz and acceleration
 *  (I) const int pfkz_segments - Partial kz number of segments
 *  (I) const int pfkz_views_per_segment - Partial kz number of encodes per
 *        segment
 *  (I) const int pfkr_flag - Partial kr
 *  (I) const float pfkr_fraction - Fraction of encodes to keep
 *  (I) const int pfkr_yz_flag - Corner removal with sequential manner y or z view ordering
 *  (I) const int echo_sort_dir - Direction echoes are acquired within segmented 
 *        views(1=ascending, -1=descending)
 *  (I) const int seg_sort_dir - Direction segmented views are acquired within 
 *        scan (1=ascending, -1=descending)
 *  (I) const float yFov - FOV in phase direction in mm (opfov*nop*opphasefov)
 *  (I) const float zFov - FOV in slice direction in mm (ethick)
 *  (I) const int phaseres - Number of phases (unaccelerated for ARC)
 *  (I) const int equant - Number of slices (unaccelerated for ARC)
 *  (I) const int delay_ec_flag - Use delayed elliptic centric view order
 *  (I) const int segmented_flag - Use segmented acquisition
 *  (I) const int nr_of_segments - Number of segments when segmented_flag
 *  (I) const int views_per_segment - Views per segment or radial beam
 *  (I) const int encode_group - View order grouping: 0:NONE 1:ZY 2:YZ
 *  (I) const int phorder - Phase order for non-elliptic centric view orders
 *  (I) const int viewoffs - Number of views to offset a centric order
 *         acquisition
 *  (I) const int rhnframes, - Number of recon frames (accelerated)
 *  (I) const int rhhnover - Number of Fractional NEX recon overscans
 *        (accelerated)
 *  (I) const slorder - Slice order for non-elliptic centric view orders
 *  (I) const nsegments - Extra SPECIAL: number of segments
 *  (I) const chemseqs  - Extra SPECIAL: number of acquisitions per segment
 *  (I) const chemseq0  - Extra SPECIAL: number of acquisitions after the
 *        SpecIR pulse
 *  (I) const int linestodiscard - EXTRA SPECIAL: number of discarded lines
 *          in order to segment total acquired slices with Extra SpecIR pulse
 *  (I) const int arc_flag - Set if ARC is enabled
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 *  (I) const float arc_ph_stride - ARC phase outer reduction factor
 *  (I) const float arc_sl_stride - ARC slice outer reduction factor
 *  (I) const int tricks_flag - TRICKS mode
 *  (I) const int tricks_mask_regions - Number of TRICKS regions in mask
 *  (I) const int tricks_transition_views - Number of views in TRICKS
 *        transition regions
 *  (I) const int ellipt_debug_files - Debug flag
 *  (I) INT *extraspecial_slice - Physical slices with dummy slices
 *  (I/O) PARAM4D *param4d - parameters for 4D imaging
 */
STATUS
generateZyExport(ZY_EXPORT * zy_export,
                 int * delay_ec_framesIO,
                 const int zy_views,
                 const int zy_slices,
                 const int ellipt_flag,
                 const int reverse_ellipt_flag,
                 const int radfb_flag,
                 const float fn,
                 const int pfky_total_unaccel,
                 const int pfkz_flag,
                 const int pfkz_total_unaccel,
                 const int pfkz_total,
                 const int pfkz_segments,
                 const int pfkz_views_per_segment,
                 const int pfkr_flag,
                 const float pfkr_fraction,
                 const int pfkr_yz_flag,
                 const int echo_sort_dir,
                 const int seg_sort_dir,
                 const float yFov,
                 const float zFov,
                 const int phaseres,
                 const int equant,
                 const int delay_ec_flag,
                 const int segmented_flag,
                 const int nr_of_segments,
                 const int views_per_segment,
                 const int encode_group,
                 const int phorder,
                 const int viewoffs,
                 const int rhnframes,
                 const int rhhnover,
                 const int slorder,
                 const int nsegments,
                 const int chemseqs,
                 const int chemseq0,
                 const int linestodiscard,
                 const int arc_flag,
                 const CAL_PARAM calRegion,
                 const float arc_ph_stride,
                 const float arc_sl_stride,
                 const int tricks_flag,
                 const int tricks_mask_regions,
                 const int tricks_transition_views,
                 const int ellipt_debug_files,
                 int *extraspecial_slice,
                 PARAM4D *param4d)
{
    const CHAR * funcName = "generateZyExport";
    int i, j;
    float dist_ky, dist_kz;
    float grp_dist_ky, grp_dist_kz;
    int superindex = 0;
    const CHAR * presort_filename = "presort.info";
    const CHAR * postsort_filename = "postsort.info";
    const CHAR * export_filename = "export.info";
    const CHAR * distance_filename = "distance.info";
    const CHAR * prediscoinc_filename = "prediscoinc.info"; /* pre disco increase */
    const CHAR * postdiscoinc_filename = "postdiscoinc.info"; /* post disco increase */
    FILE * distance_file = NULL;
    int delay_ec_frames = *delay_ec_framesIO;
    int cal_data, accelerated_data; /* Is data calibration or accelerated data */
    int pfky_flag = (fn < 1.0);
    int sampledPoints = 0;
    int zy_encodes = zy_views * zy_slices;
    float maskDist = 0;  /* Fake distance for sorting  masked encodess */
    float skipDist = 0;  /* Fake distance for sorting  encodes skipped due to
                            parallel imaging */

    /* pfkr and elliptic centric view order parameters:
       Calculate the center of k-space. The purpose of the "0.01's" is to
       break the symmetry of the four quadrants.  For example, it insures
       that the distance from slice 0 to the origin is less than the
       distance from slice=opslquant-1 to the origin, so the xz-plane is
       done after slice opslquant-1 is acquired.  This is not necessary
       or desired for the elliptical calibration (calRegion) calculations.*/
    float delta_ky = 1.0/yFov;  /* inverse mm */
    float delta_kz = 1.0/zFov;  /* inverse mm also */
    float origin_y = (float)(phaseres-1)/2.0 - 0.01;
    float origin_z = (float)(equant-1)/2.0 - 0.01;
    float kr_fraction = sqrt(pfkr_fraction*4.0/PI);
    float max_dist_ky = 0.505*kr_fraction*delta_ky*(float)(phaseres-1);
    float max_dist_kz = 0.505*kr_fraction*delta_kz*(float)(equant-1);
    float sq_max_dist_ky = max_dist_ky * max_dist_ky;
    float sq_max_dist_kz = max_dist_kz * max_dist_kz;
    float sq_normdist_ky = 0.0;
    float sq_normdist_kz = 0.0;

    float grp_origin_y = origin_y;
    float grp_origin_z = origin_z;
    float grp_delta_ky = delta_ky;
    float grp_delta_kz = delta_kz;

    float dist_y = 0, dist_z = 0;
    float alpha = (float)phaseres/(float)equant; /* anisotropy factor */
    
    /*  Use dynamic memory allocation for zy_sort & zy_export */
    ZY_DIST *zy_sort = NULL;

    if ((zy_sort = (ZY_DIST *) malloc(sizeof(ZY_DIST) * zy_encodes)) == NULL) {
        printf("%s: Failure allocating zy_sort.\n", funcName);
        return FAILURE;
    }
    memset(zy_sort, 0, sizeof(ZY_DIST) * zy_encodes);

    /* allocate data structures */
    float* y_list = NULL;
    float* z_list = NULL;
    int*   flag_list = NULL;
    float* y_sort = NULL;
    float* z_sort = NULL;
    int*   flag_sort = NULL;

    if (pfkr_yz_flag)
    {
        if ((y_list = (float *) malloc(sizeof(float) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating y_list.\n", funcName);
            return FAILURE;
        }
        memset(y_list, 0, sizeof(float) * zy_views * zy_slices);

        if ((z_list = (float *) malloc(sizeof(float) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating z_list.\n", funcName);
            free(y_list);
            return FAILURE;
        }
        memset(z_list, 0, sizeof(float) * zy_views * zy_slices);

        if ((flag_list = (int *) malloc(sizeof(int) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating flag_sort.\n", funcName);
            free(y_list);
            free(z_list);
            return FAILURE;
        }
        memset(flag_list, 0, sizeof(int) * zy_views * zy_slices);

        if ((y_sort = (float *) malloc(sizeof(float) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating y_sort.\n", funcName);
            free(y_list);
            free(z_list);
            free(flag_list);
            return FAILURE;
        }
        memset(y_sort, 0, sizeof(float) * zy_views * zy_slices);

        if ((z_sort = (float *) malloc(sizeof(float) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating z_sort.\n", funcName);
            free(y_list);
            free(z_list);
            free(flag_list);
            free(y_sort);
            return FAILURE;
        }
        memset(z_sort, 0, sizeof(float) * zy_views * zy_slices);

        if ((flag_sort = (int *) malloc(sizeof(int) * zy_views * zy_slices)) == NULL) {
            printf("%s: Failure allocating flag_sort.\n", funcName);
            free(y_list);
            free(z_list);
            free(flag_list);        
            free(y_sort);
            free(z_sort);
            return FAILURE;
        }
        memset(flag_sort, 0, sizeof(int) * zy_views * zy_slices);
    }

    if (ellipt_debug_files == 1)
    {
        distance_file = fopen(distance_filename, "w");
    }

    /* Calculate a distance that is larger than any radial distance for
       elliptic centric encodes and number of encodes for other view orders.
       This distance will be used to sort the mask points after the sampled
       points and before the skipped points */
    maskDist = 100.0*sqrt(sq_max_dist_ky + sq_max_dist_kz);
    if (maskDist < 10.0 * (float)(zy_encodes))
    {
        maskDist = 10.0 * (float)(zy_encodes);
    }

    skipDist = 2.0 * maskDist;

    if (ENCODE_GROUP_ZY == encode_group) {
        /* If ZY grouping make the largest distance in ZY smaller 
           than ky step size */
        grp_delta_kz = delta_kz/zy_slices;
        grp_delta_ky = (zy_slices + 1)*grp_delta_kz;
    }

    if (ENCODE_GROUP_YZ == encode_group) {
         /* If ZY grouping make the largest distance in ZY smaller 
           than ky step size */
        grp_delta_ky = delta_ky/zy_views;
        grp_delta_kz = (zy_views + 1)*grp_delta_ky;
    }
    
    /* Define k-space origin according to view order so a generic 
       distance based sorting work for all cases.*/
    if (CENTRIC == slorder) {
        grp_origin_z = (float)(equant-1)/2.0 - 0.25;
    } else if (REVERSE_SEQUENTIAL == slorder) {
        grp_origin_z = zy_slices - 1;
    } else { /* assume sequential */
        grp_origin_z = 0;
    }
    
    if (CENTRIC == phorder) {
        grp_origin_y = (float)(phaseres-1)/2.0 - 0.25;
    } else if (REVERSE_SEQUENTIAL == phorder) {
        grp_origin_y = zy_views - 1;
    } else { /* assume sequential */
        grp_origin_y = 0;
    }
    
    /* For non-ARC case, all voxels are accelerated and calibration */
    accelerated_data = 1;
    cal_data = 1;

    if (pfkr_yz_flag && (VIEWSHARING_OFF == param4d->vieworder_mode))
    {
        int pfkrIN = 1;
        int pfkyIN = 1;
        int pfkzIN = 1;
        int view_count = 0;
        int tmp_maskPoints = 0;

        /* input into arrays which view is acquired and used as calibration data for ARC */
        for (i = 0; i < zy_views; i++)
        {
            if (pfkr_flag)
            {
                dist_ky = delta_ky * ((float)(i) - origin_y);
                sq_normdist_ky = dist_ky*dist_ky / sq_max_dist_ky;
            }

            for (j = 0; j < zy_slices; j++)
            {
                if (pfkr_flag)
                {
                    dist_kz = delta_kz*((float)(j) - origin_z);
                    pfkrIN = ((sq_normdist_ky + (dist_kz*dist_kz) / sq_max_dist_kz) <= 1.0);
                }
                else
                {
                    pfkrIN = 1;
                }

                pfkzIN = (pfkz_flag) ? (j < pfkz_total_unaccel) : 1;
                pfkyIN = (pfky_flag) ? (i < pfky_total_unaccel) : 1;

                if (!(pfkrIN && pfkyIN && pfkzIN))
                {
                    tmp_maskPoints++;
                }

                if (arc_flag)
                {
                    /* support kyz_shift view ordering */
                    accelerated_data = accelerated_voxel(i, j, calRegion,
                                                         arc_ph_stride, arc_sl_stride);
                    cal_data = calibration_voxel(i, j, calRegion);
                }

                if (cal_data || accelerated_data)
                {
                    if (pfkrIN && pfkyIN && pfkzIN)
                    {
                        y_list[view_count] = (float)i;
                        z_list[view_count] = (float)j;
                        flag_list[view_count] = ZY_FLAGS_SAMPLED;
                        if (cal_data)
                        {
                            flag_list[view_count] = ZY_FLAGS_SAMPLED + ZY_FLAGS_CAL;
                        }
                        view_count = view_count + 1;
                    }
                }
            } /*j*/
        } /*i*/

        if (pfkr_yz_flag == 1)
        {
            orderviews_z(view_count, nr_of_segments, views_per_segment, 0, pfkz_total_unaccel, (int)arc_sl_stride, echo_sort_dir, seg_sort_dir, phorder, y_list, z_list, flag_list, y_sort, z_sort, flag_sort);
        }
        else if (pfkr_yz_flag == 2)
        {
            orderviews_y(view_count, nr_of_segments, views_per_segment, 0, phaseres, (int)arc_ph_stride, echo_sort_dir, seg_sort_dir, phorder, y_list, z_list, flag_list, y_sort, z_sort, flag_sort);
        }

        for (i = 0; i < nr_of_segments * views_per_segment ; i++)
        {
            zy_export[i].view = y_sort[i];
            zy_export[i].slice = z_sort[i];
            zy_export[i].flags = flag_sort[i];
        }
    }
    else
    {
        /* MRIge57602 - added reverse elliptical centric encoding */
        if ( (ellipt_flag == 1) || (reverse_ellipt_flag == 1) ||
             (radfb_flag == 1) || (ENCODE_GROUP_NONE != encode_group) || (DISCO_ORDER == param4d->vieworder_mode) )
        {
            /* Negate distance for reverse elliptical since zy_sort will be
               reversed when it is copied to zy_export */
            if (reverse_ellipt_flag)
            {
                skipDist = -skipDist;
                maskDist = -maskDist;
            }

            superindex = 0;
            for (i=0; i<zy_views; i++)
            {
                dist_y = ((float)(i) - origin_y);
                dist_ky = delta_ky*dist_y;
                sq_normdist_ky = pow(dist_ky, 2) / sq_max_dist_ky;
            
                grp_dist_ky = fabs(grp_delta_ky*((float)(i) - grp_origin_y));

                for (j=0; j<zy_slices; j++)
                {
                    if (arc_flag)
                    {
                        accelerated_data = accelerated_voxel(i, j, calRegion,
                                                             arc_ph_stride, arc_sl_stride);
                        cal_data = calibration_voxel(i, j, calRegion);
                    }

                    zy_sort[superindex].view = i;
                    zy_sort[superindex].slice = j;
                    zy_sort[superindex].flags = 0; /* Initialize all flags to off */

                    dist_z = ((float)(j) - origin_z);
                    dist_kz = delta_kz*dist_z;
                    grp_dist_kz = fabs(grp_delta_kz*((float)(j) - grp_origin_z));

                    sq_normdist_kz = pow(dist_kz, 2) / sq_max_dist_kz;

                    if (ENCODE_GROUP_NONE != encode_group) 
                    {
                        /* Angles are overloaded with grouping distances
                         * Once each group is created then distance sorting
                         * handles within group ordering.
                         * Angle sort:
                         *    ENCODE_GROUP_ZY => phorder and slice based grouping 
                         *    ENCODE_GROUP_YZ => slorder and phase based grouping 
                         * Distance sort:
                         *    slorder and phorder control within each group
                         */
                        if (ENCODE_GROUP_ZY == encode_group) {
                            zy_sort[superindex].distance = grp_dist_kz;
                        }

                        if (ENCODE_GROUP_YZ == encode_group) {
                            zy_sort[superindex].distance = grp_dist_ky;
                        }

                        zy_sort[superindex].angle = grp_dist_ky + grp_dist_kz;

                    }
                    else
                    {
                        zy_sort[superindex].distance = sqrt(pow(dist_ky, 2) + pow(dist_kz, 2));
                        zy_sort[superindex].angle = calc_angle(dist_kz, dist_ky);
                    }

                    if (param4d->smoothec)
                    {
                        zy_sort[superindex].distance = (zy_sort[superindex].angle)/360.0 +
                            ceil(sqrt(pow(dist_y, 2) + pow(dist_z*alpha, 2)));
                    }

                    if (cal_data)
                    {
                        zy_sort[superindex].flags |= (ZY_FLAGS_CAL | ZY_FLAGS_SAMPLED);
                    }
                    else if (accelerated_data)
                    {
                        zy_sort[superindex].flags |= ZY_FLAGS_SAMPLED;
                    }
                    else
                    {
                        zy_sort[superindex].distance = skipDist;
                    }

                    float distBkp = zy_sort[superindex].distance; /* backup before setting to maskDist */

                    if (pfkr_yz_flag)
                    {
                        int pfkrIN = 1;
                        int pfkyIN = 1;
                        int pfkzIN = 1;

                        pfkrIN = (pfkr_flag) ? ((sq_normdist_ky + sq_normdist_kz) <= 1.0) : 1;
                        pfkzIN = (pfkz_flag) ? (zy_sort[superindex].slice < pfkz_total_unaccel) : 1;
                        pfkyIN = (pfky_flag) ? (zy_sort[superindex].view < pfky_total_unaccel) : 1;

                        if (!(pfkrIN && pfkyIN && pfkzIN))
                        {
                            zy_sort[superindex].flags |= ZY_FLAGS_MASK;
                            zy_sort[superindex].distance = maskDist;
                        }
                    }
                    else if ((pfkz_flag && (zy_sort[superindex].slice >= pfkz_total_unaccel)) ||
                        (pfky_flag && (zy_sort[superindex].view >= pfky_total_unaccel)))
                    {
                        zy_sort[superindex].flags |= ZY_FLAGS_MASK;
                        zy_sort[superindex].distance = maskDist;
                    }
                    else if (pfkr_flag)
                    {
                        if ((sq_normdist_ky + sq_normdist_kz) > 1.0)
                        {
                            zy_sort[superindex].flags |= ZY_FLAGS_MASK;
                            zy_sort[superindex].distance = maskDist;
                        }
                    }

                    if ((DISCO_ORDER == param4d->vieworder_mode) && segmented_flag && (param4d->num_outer_regions == 1))
                    {
                        if ((zy_sort[superindex].flags & ZY_FLAGS_MASK) == ZY_FLAGS_MASK)
                        {
                            /* Add the un-masked distance back because we may need to increase the size of sampledPoints later,
                             * and we need to keep the un-masked distance info for proper sorting.
                             * Note that maskDist+distanceForSampledPoints is less than skipDist */
                            zy_sort[superindex].distance += distBkp;
                        }
                    }

                    superindex += 1;
                }
            }

            if (ellipt_debug_files == 1)
            {
                writeZyDistDebug(presort_filename, "pre", zy_sort, zy_encodes);
            }

            /* MRIge91682 */
            qsort(zy_sort, zy_encodes, sizeof(ZY_DIST), dist_compare);

            /* Count the number of sampled encodes */
            sampledPoints = countSampledPoints(zy_sort, zy_encodes);

            /* increase sampledPoints to ensure it is divisible by views_per_segment for DISCO with segmented_flag ON */
            if ((DISCO_ORDER == param4d->vieworder_mode) && segmented_flag && (param4d->num_outer_regions == 1))
            {
                if (ellipt_debug_files == 1)
                {
                    writeZyDistDebug(prediscoinc_filename, "pre", zy_sort, zy_encodes);
                }

                /* Sample views_per_segment * nr_of_segments points */
                int inc_pts = 0;

                if (zy_encodes < views_per_segment * nr_of_segments)
                {
                    inc_pts = zy_encodes - sampledPoints;
                }
                else
                {
                    inc_pts = views_per_segment * nr_of_segments - sampledPoints;
                }

                for (i = sampledPoints; i < sampledPoints + inc_pts; i++)
                {
                    zy_sort[i].flags &= ~ZY_FLAGS_MASK;
                    zy_sort[i].distance -= maskDist;
                }

                sampledPoints += inc_pts;
                qsort(zy_sort, zy_encodes, sizeof(ZY_DIST), dist_compare);

                if (ellipt_debug_files == 1)
                {
                    writeZyDistDebug(postdiscoinc_filename, "post", zy_sort, zy_encodes);
                }
            }

            if (radfb_flag)
            {
                if (FAILURE == radfbsort(zy_sort, sampledPoints, nr_of_segments))
                {
                    printf("%s: radfbsort() failed.\n", funcName);
                    free(zy_sort);
                    return FAILURE;
                }
            }

            if (DISCO_ORDER == param4d->vieworder_mode)
            {
                if (FAILURE == discosort(zy_sort, sampledPoints, segmented_flag, views_per_segment, param4d))
                {
                    printf("%s: discosort() failed.\n", funcName);
                    free(zy_sort);
                    return FAILURE;
                }

                if (1 == param4d->reverse_first_region_flag)
                {
                    /* need to create one more region at the end, to be the reverseEC version of first sub-region */

                    /* create a backup of original zy_sort */
                    ZY_DIST *zy_sort_old = zy_sort;

                    /* re-allocate memory and let zy_sort point to it */
                    const int extra_length = param4d->views_per_region[1]; /* first sub-region */

                    if (NULL == (zy_sort = (ZY_DIST *) malloc(sizeof(ZY_DIST) * (zy_encodes + extra_length))))
                    {
                        printf("%s: ERROR Failure re-allocating zy_sort.\n", funcName);
                        return FAILURE;
                    }

                    memcpy(zy_sort, zy_sort_old, sizeof(ZY_DIST) * sampledPoints);

                    for (i = 0; i < extra_length; i++)
                    {
                        memcpy(&(zy_sort[sampledPoints+extra_length-1-i]), &(zy_sort_old[param4d->views_per_region[0]+i]), sizeof(ZY_DIST));
                    }

                    /* also need to copy un-sampled points */
                    memcpy(&zy_sort[sampledPoints+extra_length], &zy_sort_old[sampledPoints], sizeof(ZY_DIST) * (zy_encodes-sampledPoints));

                    sampledPoints += extra_length;
                    param4d->views_per_region[1+param4d->num_sub_regions] = extra_length; /* assume 2 == num_regions */

                    free(zy_sort_old); /* this will free the old memory block */
                }
            }

            if (ENCODE_GROUP_NONE != encode_group)
            {
                if (FAILURE == phslGroupSort(zy_sort, sampledPoints, views_per_segment))
                {
                    printf("%s: phslGroupSort() failed.\n", funcName);
                    free(zy_sort);
                    return FAILURE;
                }
            }

            /* MRIhc06911 */
            if (tricks_flag)
            {
                if (FAILURE == tricksRegionSort(zy_sort, zy_encodes, tricks_mask_regions,
                                                tricks_transition_views))
                {
                    printf("%s: tricksRegionSort failed.\n", funcName);
                    free(zy_sort);
                    return FAILURE;
                }
            }

            if (ellipt_debug_files == 1)
            {
                writeZyDistDebug(postsort_filename, "post", zy_sort, zy_encodes);
            }

            /* No need to export distances or yz_skip to tgt. Copy everything else to ipgexport
               structure */
            /* MRIge91682 */
            if (reverse_ellipt_flag == 1 )
            {
                for (i=0; i< zy_encodes; i++)
                {
                    zy_export[i].view  = zy_sort[zy_encodes-1-i].view;
                    zy_export[i].slice = zy_sort[zy_encodes-1-i].slice;
                    zy_export[i].flags = zy_sort[zy_encodes-1-i].flags;
                    if (ellipt_debug_files == 1)
                    {
                        fprintf(distance_file,"%4f\n", zy_sort[zy_encodes-1-i].distance);
                    }
                }
            }
            else /* forward elliptical */
            {
                /* MRIge91683 */
                int delay_ec_index;

                /* Cannot delay more than we have points */
                if (delay_ec_frames > sampledPoints)
                {
                    delay_ec_frames = sampledPoints;
                }

                for (i=0; i < zy_encodes; i++)
                {
                    if ( (i < delay_ec_frames/2) && delay_ec_flag )
                    {
                        delay_ec_index = delay_ec_frames-1-2*i;
                    }
                    else if ( (i >= delay_ec_frames/2) && (i < delay_ec_frames) && delay_ec_flag )
                    {
                        delay_ec_index = 2*i-delay_ec_frames;
                    }
                    else
                    {
                        delay_ec_index = i;
                    }

                    zy_export[i].view = zy_sort[delay_ec_index].view;
                    zy_export[i].slice = zy_sort[delay_ec_index].slice;
                    zy_export[i].flags = zy_sort[delay_ec_index].flags;
                    if (ellipt_debug_files == 1)
                    {
                        fprintf(distance_file,"%4f\n", zy_sort[delay_ec_index].distance);
                    }
                }
            }
        }
        else  /*ellipt_flag != 1, load standard loop order */
        {
            short viewtab[zy_views+1]; /* view encode table */
            int slicetab[zy_slices];   /* slice encode table */

            /* MRIge81273 - REVERSE_SEQUENTIAL now supported in phase_order_fgre3d */
            if (arc_flag)
            {
                /* Calculate fully-sampled phase order for ARC.
                   Fractional NEX marking is handled separately */
                phase_order_fgre3d(viewtab, phorder, zy_views,
                                   viewoffs, zy_views, 0, 1.0);
            }
            else
            {
                phase_order_fgre3d(viewtab, phorder, (rhnframes + rhhnover),
                                   viewoffs, rhnframes, rhhnover, fn);
            }

            /* Calculate slice order table */
            /* use extraspecial_slice to store the physical slices with dummy slices*/
            if (FAILURE == slice_order_efgre3d(slicetab, zy_slices, slorder,
                                               nsegments, chemseqs, chemseq0, linestodiscard,
                                               pfkz_flag, pfkz_total, pfkz_segments,
                                               pfkz_views_per_segment, arc_flag,
                                               calRegion, arc_sl_stride, extraspecial_slice))
            {
                printf("%s: slice_order_efgre3d() failed.\n", funcName);
                free(zy_sort);
                return FAILURE;
            }

            superindex = 0;

            /* MRIge91682 */
            for (i=0; i<zy_views; i++)
            {
                /*views start at 0*/
                dist_ky = delta_ky*((float)(viewtab[i] - 1) - origin_y);
                sq_normdist_ky = pow(dist_ky, 2) / sq_max_dist_ky;

                for (j=0; j<zy_slices; j++)
                {
                    if (arc_flag)
                    {
                        accelerated_data = accelerated_voxel(viewtab[i] - 1, slicetab[j],
                                                             calRegion, arc_ph_stride,
                                                             arc_sl_stride);
                        cal_data = calibration_voxel(viewtab[i] - 1, slicetab[j],
                                                     calRegion);
                    }

                    zy_sort[superindex].view = viewtab[i] - 1; /*views start at 0*/
                    zy_sort[superindex].slice = slicetab[j];  /*slices start at 0*/
                    zy_sort[superindex].flags  = 0; /* Initialized all flags to off */
                    zy_sort[superindex].distance =  (float) superindex;

                    if (cal_data)
                    {
                        zy_sort[superindex].flags |= (ZY_FLAGS_CAL | ZY_FLAGS_SAMPLED);
                    }
                    else if (accelerated_data)
                    {
                        zy_sort[superindex].flags |= ZY_FLAGS_SAMPLED;
                    }
                    else
                    {
                        zy_sort[superindex].distance = skipDist;
                    }

                    if ((pfkz_flag && (zy_sort[superindex].slice >= pfkz_total_unaccel)) ||
                        (pfky_flag && (zy_sort[superindex].view >= pfky_total_unaccel)))
                    {
                        zy_sort[superindex].flags |= ZY_FLAGS_MASK;
                        zy_sort[superindex].distance = maskDist;
                    }
                    else if (pfkr_flag)
                    {
                        /* Don't overwrite distance in zy_sort.  Distances are
                           used to sort the encodes */
                        dist_kz = delta_kz*((float)(zy_sort[superindex].slice) - origin_z);

                        if ((sq_normdist_ky + (dist_kz*dist_kz) / sq_max_dist_kz) > 1.0)
                        {
                            zy_sort[superindex].flags |= ZY_FLAGS_MASK;
                            zy_sort[superindex].distance = maskDist;
                        }
                    }

                    superindex +=1;
                }
            }

            if (ellipt_debug_files == 1)
            {
                writeZyDistDebug(presort_filename, "pre", zy_sort, zy_encodes);
            }

            /* Sort to push the skipped and mask points to the end */
            qsort(zy_sort, zy_encodes, sizeof(ZY_DIST), dist_compare);

            if (ellipt_debug_files == 1)
            {
                writeZyDistDebug(postsort_filename, "post", zy_sort, zy_encodes);
            }

            for (i=0; i < zy_encodes; i++)
            {
                zy_export[i].view = zy_sort[i].view;
                zy_export[i].slice = zy_sort[i].slice;
                zy_export[i].flags = zy_sort[i].flags;

                if (ellipt_debug_files == 1)
                    fprintf(distance_file,"%4f\n", zy_sort[i].distance);
            }

        } /* end of if (ellipt_flag==1) block */

        /* SegStart has already been marked in discosort function */
        if (segmented_flag && !radfb_flag && (VIEWSHARING_OFF == param4d->vieworder_mode))
        {
            /* For segmented acquistions with out radial fan beam,
               still need to mark segments */
            if (FAILURE == markSegStart(zy_sort, sampledPoints, nr_of_segments))
            {
                free(zy_sort);
                return FAILURE;
            }
        }

        sampledPoints = countSampledPoints(zy_sort, zy_encodes);
    }

    free(zy_sort);

    if (NULL != y_list)
    {
        free(y_list);
    }
    if (NULL != z_list)
    {
        free(z_list);
    }
    if (NULL != flag_list)
    {
        free(flag_list);
    }
    if (NULL != y_sort)
    {
        free(y_sort);
    }
    if (NULL != z_sort)
    {
        free(z_sort);
    }
    if (NULL != flag_sort)
    {
        free(flag_sort);
    }

    /* Calculate when each xz-plane will be completely acquired */
    if (pfkr_yz_flag && (VIEWSHARING_OFF == param4d->vieworder_mode))
    {
        markXzDone(zy_export, nr_of_segments*views_per_segment);
    }
    else
    {
        markXzDone(zy_export, sampledPoints);
    }

    if (ellipt_debug_files == 1)
    {
        FILE * fid;
        fid = fopen(export_filename, "w");

        for (i = 0; i < zy_encodes ; i++)
        {
            fprintf(fid, "export: superindex=%d; view=%d; slice=%d; "
                    "echo=%d; flags=%d (cal=%d,acc=%d,mask=%d,xz_done=%d,seg_start=%d)\n",
                    i, zy_export[i].view, zy_export[i].slice,
                    zy_export[i].echo, zy_export[i].flags,
                    (zy_export[i].flags & ZY_FLAGS_CAL) == ZY_FLAGS_CAL,
                    (zy_export[i].flags & ZY_FLAGS_SAMPLED) == ZY_FLAGS_SAMPLED,
                    (zy_export[i].flags & ZY_FLAGS_MASK) == ZY_FLAGS_MASK,
                    (zy_export[i].flags & ZY_FLAGS_XZ_DONE) == ZY_FLAGS_XZ_DONE,
                    (zy_export[i].flags & ZY_FLAGS_SEG_START) == ZY_FLAGS_SEG_START);
        }

        fclose(fid);
    }

    if (ellipt_debug_files == 1)
    {
        fclose(distance_file);
    }

    *delay_ec_framesIO = delay_ec_frames;

    return SUCCESS;
}

/*  walkSamplingPattern
 *
 *  Description:
 *  walks the entire k-space to know the exact number of sampledPoints.
 *  Walking the sampling pattern is done as calculations are
 *  becoming very cumbersome with corner removal and generic sampling patterns.
 *  To minimize the impact on UI response time, sampling pattern is walked
 *  only when one of the input parameters is changed.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (O) const int sampledPoints - Number of sampled points: PI + partial Fourier
 *  (O) const int sampledPointsNoMask - Number of sampled points: PI
 *  (O) const int calibrationPoints - Number of calibration points
 *  (O) const int pfkrMaskPoints - number of pfkr mask points: No PI
 *  (I) const int zy_views - Number of views (fully sampled for ARC)
 *  (I) const int zy_slices - Number of slices (fully sampled for ARC)
 *  (I) const float fn - Fractional NEX (pfky)
 *  (I) const int pfky_total_unaccel - Fractional NEX min view number to skip
 *  (I) const int pfkz_fraction - Partial kz
 *  (I) const int pfkz_total_unaccel - Partial kz min slice number to skip
 *  (I) const float pfkr_fraction - Fraction of encodes to keep
 *  (I) const float yFov - FOV in phase direction in mm (opfov*nop*opphasefov)
 *  (I) const float zFov - FOV in slice direction in mm (ethick)
 *  (I) const int phaseres - Number of phases (unaccelerated for ARC)
 *  (I) const int equant - Number of slices (unaccelerated for ARC)
 *  (I) const int arc_flag - Set if ARC is enabled
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 *  (I) const float arc_ph_stride - ARC phase outer reduction factor
 *  (I) const float arc_sl_stride - ARC slice outer reduction factor
 *
 */
STATUS
walkSamplingPattern(int *sampledPoints,
                    int *sampledPointsNoMask,
                    int *calibrationPoints,
                    int *maskPoints,
                    const int zy_views,
                    const int zy_slices,
                    const float fn,
                    const int pfky_total_unaccel,
                    const float pfkz_fraction,
                    const int pfkz_total_unaccel,
                    const float pfkr_fraction,
                    const float yFov,
                    const float zFov,
                    const int phaseres,
                    const int equant,
                    const int arc_flag,
                    const CAL_PARAM calRegion,
                    const float arc_ph_stride,
                    const float arc_sl_stride)
{
    /* Cache old input and outputs
       Initialize all to -1 to force first time execution*/
    static int old_sampledPoints = -1;
    static int old_sampledPointsNoMask = -1;
    static int old_calibrationPoints = -1;
    static int old_maskPoints = -1;

    static int old_zy_views = -1;
    static int old_zy_slices = -1;
    static float old_fn = -1.0;
    static int old_pfky_total_unaccel = -1;
    static float old_pfkz_fraction = -1.0;
    static int old_pfkz_total_unaccel = -1;
    static float old_pfkr_fraction = -1;
    static float old_yFov = -1.0;
    static float old_zFov = -1.0;
    static int old_phaseres = -1;
    static int old_equant = 1;
    static int old_arc_flag = -1;
    static CAL_PARAM old_calRegion;
    static float old_arc_ph_stride = -1.0;
    static float old_arc_sl_stride = -1.0;

    /* Input are the same as cached values.  Use cached result */
    int noChange = ((old_zy_views == zy_views) &&
                    (old_zy_slices == zy_slices) &&
                    (old_fn == fn) &&
                    (old_pfky_total_unaccel == pfky_total_unaccel) &&
                    (old_pfkz_fraction == pfkz_fraction) &&
                    (old_pfkz_total_unaccel == pfkz_total_unaccel) &&
                    (old_pfkr_fraction == pfkr_fraction) &&
                    (old_yFov == yFov) &&
                    (old_zFov == zFov) &&
                    (old_phaseres == phaseres) &&
                    (old_equant == equant) &&
                    (old_arc_flag == arc_flag) &&
                    !memcmp(&old_calRegion, &calRegion, sizeof(calRegion)) &&
                    (old_arc_ph_stride == arc_ph_stride) &&
                    (old_arc_sl_stride == arc_sl_stride));

    if (noChange)
    {
        *sampledPoints = old_sampledPoints;
        *sampledPointsNoMask = old_sampledPointsNoMask;
        *calibrationPoints = old_calibrationPoints;
        *maskPoints = old_maskPoints;
    }
    else
    {
        float sq_normdist_ky = 0.0;
        int view = 0;
        int slice = 0;
        float dist_ky = 0.0;
        float dist_kz = 0.0;
        int cal_data = 0;
        int accelerated_data = 0; /* Is data calibration or accelerated data */
        int pfky_flag = (fn < 1.0);
        int pfkz_flag = (pfkz_fraction < 1.0);
        int pfkr_flag = (pfkr_fraction < 1.0);
        int pfkrIN = 1;
        int pfkyIN = 1;
        int pfkzIN = 1;

        int tmp_sampledPoints = 0;
        int tmp_sampledPointsNoMask = 0;
        int tmp_calibrationPoints = 0;
        int tmp_maskPoints = 0;

        /* pfkr parameters */
        float delta_ky = 1.0/yFov;  /* inverse mm */
        float delta_kz = 1.0/zFov;  /* inverse mm also */
        float origin_y = (float)(phaseres-1)/2.0 - 0.01;
        float origin_z = (float)(equant-1)/2.0 - 0.01;
        float kr_fraction = sqrt(pfkr_fraction*4.0/PI);
        float max_dist_ky = 0.505*kr_fraction*delta_ky*(float)(phaseres-1);
        float max_dist_kz = 0.505*kr_fraction*delta_kz*(float)(equant-1);
        float sq_max_dist_ky = max_dist_ky * max_dist_ky;
        float sq_max_dist_kz = max_dist_kz * max_dist_kz;

        /* For non-ARC case, all voxels are accelerated and calibration */
        accelerated_data = 1;
        cal_data = 1;

        for (view = 0; view < zy_views; view++)
        {
            if (pfkr_flag)
            {
                dist_ky = delta_ky * ((float)(view) - origin_y);
                sq_normdist_ky = dist_ky*dist_ky / sq_max_dist_ky;
            }

            for (slice = 0; slice < zy_slices; slice++)
            {
                if (pfkr_flag)
                {
                    dist_kz = delta_kz*((float)(slice) - origin_z);
                    pfkrIN = ((sq_normdist_ky + (dist_kz*dist_kz) / sq_max_dist_kz) <= 1.0);
                }
                else
                {
                    pfkrIN = 1;
                }

                pfkzIN = (pfkz_flag) ? (slice < pfkz_total_unaccel) : 1;
                pfkyIN = (pfky_flag) ? (view < pfky_total_unaccel) : 1;

                if (!(pfkrIN && pfkyIN && pfkzIN))
                {
                    tmp_maskPoints++;
                }

                if (arc_flag)
                {
                    accelerated_data = accelerated_voxel(view, slice, calRegion,
                                                         arc_ph_stride, arc_sl_stride);
                    cal_data = calibration_voxel(view, slice, calRegion);
                }

                if (cal_data || accelerated_data)
                {
                    tmp_sampledPointsNoMask++;

                    if (pfkrIN && pfkyIN && pfkzIN)
                    {
                        tmp_sampledPoints++;
                        if (cal_data)
                        {
                            tmp_calibrationPoints++;
                        }
                    }
                }
            }
        }

        *sampledPoints = tmp_sampledPoints;
        *sampledPointsNoMask = tmp_sampledPointsNoMask;
        *calibrationPoints = tmp_calibrationPoints;
        *maskPoints = tmp_maskPoints;

        if ((*sampledPoints > *sampledPointsNoMask) || (*calibrationPoints > *sampledPoints))
        {
            /* Defensive checks.  Should never fail */
            return FAILURE;
        }

        old_sampledPoints = tmp_sampledPoints;
        old_sampledPointsNoMask = tmp_sampledPointsNoMask;
        old_calibrationPoints = tmp_calibrationPoints;
        old_maskPoints = tmp_maskPoints;

        old_zy_views = zy_views;
        old_zy_slices = zy_slices;
        old_fn = fn;
        old_pfky_total_unaccel = pfky_total_unaccel;
        old_pfkz_fraction = pfkz_fraction;
        old_pfkz_total_unaccel = pfkz_total_unaccel;
        old_pfkr_fraction = pfkr_fraction;
        old_yFov = yFov;
        old_zFov = zFov;
        old_phaseres = phaseres;
        old_equant = equant;
        old_arc_flag = arc_flag;
        memcpy(&old_calRegion, &calRegion, sizeof(calRegion));
        old_arc_ph_stride = arc_ph_stride;
        old_arc_sl_stride = arc_sl_stride;
    }

    return SUCCESS;
}

/*  setArcCalParams
 *
 *  Description:
 *   This function initiliazes calibration size, calibration shape,
 *   Furthermore, provides userCV controls in arc research mode.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O)    CAL_PARAM *calMinRegion - Structure to hold min cal size parameters
 *  (I,O)  int  *cal_shape - calibration shape 0=Cross 1=Box 2=Elliptical
 *  (O)    int  *arc_ph_mincalwidth - phase direction minimum cal size
 *  (O)    int  *arc_sl_mincalwidth - slice direction minimum cal size
 *  (O)    int  *arc_ph_calwidth - phase direction cal size
 *  (O)    int  *arc_sl_calwidth - slice direction cal size
 *  (O)    int  *arc_ph_callower - phase dir cal region lower boundary
 *  (O)    int  *arc_ph_calupper - phase dir cal region upper boundary
 *  (O)    int  *arc_sl_callower - slice dir cal region lower boundary
 *  (O)    int  *arc_sl_calupper - slice dir cal region upper boundary
 *  (I)    const float arc_ph_maxstride - phase dir. coil acceleration limit
 *  (I)    const float arc_sl_maxstride - slice dir. coil acceleration limit
 *  ARC Research Mode/CalSize Control Mode CVs
 * -------------------------------------------
 *  (I)    const int user_arc_ph_calwidth - phase direction cal size
 *  (I)    const int user_arc_sl_calwidth - slice direction cal size
 *  (I)    const int user_cal_shape       - calibration shape 0=Cross 1=Box 2=Elliptical
 * -------------------------------------------
 *  (I)    const int ctrl_calparams_flag -  0= cal parameters sets internally
 *                                          1= userCVs 9,10 & 15 control size and shape
 *  (I)    const int fullPhase  - number of unaccelerated phases
 *  (I)    const int fullSlice  - number of unaccelerated slices
 *
 */
STATUS
setArcCalParams(CAL_PARAM *calMinRegion,
                int *cal_shape,
                int *arc_ph_mincalwidth,
                int *arc_sl_mincalwidth,
                int *arc_ph_calwidth,
                int *arc_sl_calwidth,
                int *arc_ph_callower,
                int *arc_ph_calupper,
                int *arc_sl_callower,
                int *arc_sl_calupper,
                const float arc_ph_maxstride,
                const float arc_sl_maxstride,
                const int user_arc_ph_calwidth,
                const int user_arc_sl_calwidth,
                const int user_cal_shape,
                const int ctrl_calparams_flag,
                const int fullPhase,
                const int fullSlice,
                int research_flag)
{
    if (ctrl_calparams_flag)
    {
        *cal_shape = user_cal_shape;
        if(PSD_ON == research_flag)
        {
            *arc_ph_mincalwidth = IMin(2, fullPhase, user_arc_ph_calwidth);
            *arc_sl_mincalwidth = IMin(2, fullSlice, user_arc_sl_calwidth);
        }
    }

    *arc_ph_calwidth = *arc_ph_mincalwidth;
    *arc_sl_calwidth = *arc_sl_mincalwidth;

    if ((CROSS_CAL == *cal_shape) && (1.0 == arc_ph_maxstride))
    {
        /* Cross: slice only acceleration */
        *arc_ph_callower = 0;
        *arc_ph_calupper = (int)(fullPhase - 1);
    }
    else
    {
        *arc_ph_callower = IMax(2, 0, (INT)floorf((FLOAT)((fullPhase - 1) - *arc_ph_calwidth) / 2.0 + 0.5));
        *arc_ph_calupper = IMin(2, (int)fullPhase - 1, *arc_ph_callower + *arc_ph_calwidth - 1);
    }

    if ((CROSS_CAL == *cal_shape) && (1.0 == arc_sl_maxstride))
    {
        /* Cross: phase only acceleration */
        *arc_sl_callower = 0;
        *arc_sl_calupper = (int)(fullSlice - 1);
    }
    else
    {
        *arc_sl_callower = IMax(2, 0, (INT)floorf((FLOAT)((fullSlice - 1) - *arc_sl_calwidth) / 2.0 + 0.5));
        *arc_sl_calupper = IMin(2, (int)fullSlice - 1, *arc_sl_callower + *arc_sl_calwidth - 1);
    }

    /* Pack cal region parameters into a structure to pass them into a function easily */
    (*calMinRegion).shape = *cal_shape;
    (*calMinRegion).phaseCutoffUpper = *arc_ph_calupper;
    (*calMinRegion).phaseCutoffLower = *arc_ph_callower;
    (*calMinRegion).sliceCutoffUpper = *arc_sl_calupper;
    (*calMinRegion).sliceCutoffLower = *arc_sl_callower;
    (*calMinRegion).phaseOrigin = (float)(fullPhase-1)/2.0;
    (*calMinRegion).phaseRadius = (float)(*arc_ph_calupper -*arc_ph_callower + 1)/2.0;
    (*calMinRegion).sliceOrigin = (float)(fullSlice-1)/2.0;
    (*calMinRegion).sliceRadius = (float)(*arc_sl_calupper - *arc_sl_callower + 1)/2.0;

    return SUCCESS;
}

/*  splitArcFactor
 *
 *  Description:
 *   This function splits the internal ARC acceleration factor into
 *   phase and slice direction acceleration factors depending on the
 *   full y-z resolutions and cal type.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I)    const float opgem_factor - the internal arc acceleration factor
 *  (I)    const float fullPhase - number of phase encoding line when it's
 *                           fully sampled in phase encoding direction
 *  (I)    const float fullSlice - number of slices when it's fully sampled in
 *                           slice direction
 *  (I)    const int cal_shape - calibration shape. cross, box, ellipse, etc.
 *  (I)    const float phLimit - phase direction coil acceleration limit
 *  (I)    const float slLimit - slice direction coil acceleration
 *                                limit
 *  (I)    const float arc_maxnetaccel - maximum total net acceleration
 *  (I)    const float arc_recnetaccel - recommended total net acceleration
 *  (I)    const float arc_reclimnetaccel - recommended limit total net acceleration
 *  (I)    const float arc_phmaxslreclim_netaccel - Ph max and sl recommended
 *                                                  total net acceleration
 *  (I)    const float arc_ph_maxnetaccel - maximum phase net acceleration
 *  (I)    const float arc_sl_maxnetaccel - maximum slice acceleration given
 *  (I)    const float arc_ph_recstride - recommended phase outer acceleration
 *  (I)    const float arc_sl_recstride - recommended slice outer acceleration
 *  (I)    const float arc_ph_reclimstride - recommended limit phase outer acceleration
 *  (I)    const float arc_sl_reclimstride - recommended limit slice outer acceleration
 *  (I)    const float arc_ph_recnetaccel - recommended phase net acceleration
 *  (I)    const float arc_sl_recnetaccel - recommended slice net acceleration
 *  (I)    const float arc_ph_reclimnetaccel - recommended limit phase net acceleration
 *  (I)    const float arc_sl_reclimnetaccel - recommended limit slice net acceleration
 *  (I)    const int opautogem_factor - 1: set recommended net acceleration
 *  (I)    const int arc_ph_intaccel - 1: use integer acceleration factor
 *                                     for phase outer region
 *  (I)    const int arc_sl_intaccel - 1: use integer acceleration factor
 *                                     for slice outer region
 *  (I)    const int calibrationPoints - #of point in cal region
 *  (I)    const int arc_ph_mincalwidth - phase direction min. cal size
 *  (I)    const int arc_sl_mincalwidth - slice direction min. cal size
 *  (O)    float *arc_netaccel  - arc net acceleration for given prescription
 *  (O)    float *arc_ph_factor - phase direction accel factor
 *  (I,O)  float *arc_ph_stride - phase direction outer accel factor
 *  (O)    int *arc_ph_calwidth - phase direction cal size
 *  (O)    int *arc_sl_calwidth - slice direction cal size
 *  (O)    float *arc_sl_factor - slice direction accel factor
 *  (I,O)  float *arc_sl_stride - slice direction outer accel factor
 *
 */
STATUS
splitArcFactor(const float opgem_factor,
               const float fullPhase,
               const float fullSlice,
               const int cal_shape,
               const float phLimit,
               const float slLimit,
               const float arc_maxnetaccel,
               const float arc_recnetaccel,
               const float arc_reclimnetaccel,
               const float arc_phmaxslreclim_netaccel,
               const float arc_ph_maxnetaccel,
               const float arc_sl_maxnetaccel,
               const float arc_ph_recstride,
               const float arc_sl_recstride,
               const float arc_ph_reclimstride,
               const float arc_sl_reclimstride,
               const float arc_ph_recnetaccel,
               const float arc_sl_recnetaccel,
               const float arc_ph_reclimnetaccel,
               const float arc_sl_reclimnetaccel,
               const int opautogem_factor,
               const int arc_ph_intaccel,
               const int arc_sl_intaccel,
               const int calibrationPoints,
               const int arc_ph_mincalwidth,
               const int arc_sl_mincalwidth,
               float *arc_netaccel,
               float *arc_ph_factor,
               float *arc_ph_stride,
               float *arc_sl_factor,
               float *arc_sl_stride,
               int *arc_ph_calwidth,
               int *arc_sl_calwidth)
{
    float fullSize;
    float calSize;
    float accelSize;

    fullSize = (FLOAT) (fullPhase * fullSlice);

    if (opautogem_factor)
    {
        *arc_netaccel = arc_recnetaccel;
        accelSize = ceil(fullSize/ (*arc_netaccel));
        *arc_ph_factor = arc_ph_recnetaccel;
        *arc_sl_factor = arc_sl_recnetaccel;
        *arc_ph_stride = arc_ph_recstride;
        *arc_sl_stride = arc_sl_recstride;
    }
    else
    {
        *arc_netaccel = opgem_factor;
        accelSize = ceil(fullSize/ (*arc_netaccel));
        if (calibrationPoints > 0)
        {
            calSize = (FLOAT)calibrationPoints;
        }
        else
        {
            calSize = (float)(arc_ph_mincalwidth * arc_sl_mincalwidth);
            if (ELLIPTICAL_CAL == cal_shape)
            {
                calSize = ceil(PI/4.0* calSize);
            }
        }

        if ((*arc_netaccel) > 1.0) /*split arc_netaccel into slice and phase direction */
        {
            if (phLimit > 1.0)
            {
                if (slLimit > 1.0)
                { /* Phase and slice acceleration capable coil */

                    if ((*arc_netaccel) <= arc_ph_reclimnetaccel + 0.01)
                    { /* Phase rec acceleration is sufficient */
                        *arc_sl_factor = 1.0;
                        *arc_sl_stride = 1.0;
                        *arc_ph_factor = *arc_netaccel;

                        if (CROSS_CAL == cal_shape)
                        {
                            *arc_ph_stride = (fullPhase - (float)arc_ph_mincalwidth) /
                                (fullPhase / *arc_ph_factor  - (float)arc_ph_mincalwidth);
                        }
                        else
                        {
                            *arc_ph_stride = (fullSize - calSize) / (accelSize - calSize);
                        }
                    }
                    else if ((*arc_netaccel) <= arc_reclimnetaccel + 0.01)
                    { /* Rec acceleration is sufficient */
                        *arc_ph_factor = arc_ph_reclimnetaccel;
                        *arc_ph_stride = arc_ph_reclimstride;

                        *arc_sl_factor = (*arc_netaccel)/(*arc_ph_factor);

                        if (CROSS_CAL == cal_shape)
                        {
                            *arc_sl_stride = (fullSlice - (float)arc_sl_mincalwidth) /
                                (fullSlice / *arc_sl_factor  - (float)arc_sl_mincalwidth);
                        }
                        else
                        {
                            *arc_sl_stride = (fullSize - calSize) /
                                ((*arc_ph_stride) * (accelSize - calSize));
                        }
                    }
                    else if ((*arc_netaccel) <= arc_phmaxslreclim_netaccel + 0.01)
                    { /* Max Ph Rec Sl acceleration is sufficient */
                        *arc_sl_factor = arc_sl_reclimnetaccel;
                        *arc_sl_stride = arc_sl_reclimstride;

                        *arc_ph_factor = (*arc_netaccel)/(*arc_sl_factor);

                        if (CROSS_CAL == cal_shape)
                        {
                            *arc_ph_stride = (fullPhase - (float)arc_ph_mincalwidth) /
                                (fullPhase / *arc_ph_factor  - (float)arc_ph_mincalwidth);
                        }
                        else
                        {
                            *arc_ph_stride = (fullSize - calSize) /
                                ((*arc_sl_stride) * (accelSize - calSize));
                        }
                    }
                    else
                    { /* Max Ph Max Sl acceleration is sufficient */
                        *arc_ph_factor = arc_ph_maxnetaccel;
                        *arc_ph_stride = phLimit;

                        *arc_sl_factor = (*arc_netaccel)/(*arc_ph_factor);

                        if (CROSS_CAL == cal_shape)
                        {
                            *arc_sl_stride = (fullSlice - (float)arc_sl_mincalwidth) /
                                (fullSlice / *arc_sl_factor  - (float)arc_sl_mincalwidth);
                        }
                        else
                        {
                            *arc_sl_stride = (fullSize - calSize) /
                                ((*arc_ph_stride) * (accelSize - calSize));
                        }
                    }
                }
                else
                {
                    /* Phase only acceleration capable coil */
                    if (CROSS_CAL == cal_shape)
                    {
                        if( (*arc_netaccel) <= arc_ph_maxnetaccel + 0.01 )
                        {
                            *arc_ph_factor = *arc_netaccel;
                        }
                        else
                        {
                            *arc_ph_factor = 1.0;
                        }
                        *arc_ph_stride = (fullPhase - (float)arc_ph_mincalwidth) /
                            (fullPhase / *arc_ph_factor  - (float)arc_ph_mincalwidth);
                    }
                    else
                    {
                        if ( (*arc_netaccel) <= arc_maxnetaccel + 0.01 )
                        {
                            *arc_ph_factor = *arc_netaccel;
                            *arc_ph_stride = (fullSize - calSize) / (accelSize - calSize);
                        }
                        else
                        {
                            *arc_ph_factor = 1.0;
                        }
                    }

                    *arc_sl_factor = 1.0;
                    *arc_sl_stride = 1.0;
                }
            }
            else
            {
                /* Slice only acceleration capable coil */
                if (arc_sl_maxnetaccel > 1.0)
                {
                    if (CROSS_CAL == cal_shape)
                    {
                        if( (*arc_netaccel) <= arc_sl_maxnetaccel + 0.01 )
                        {
                            *arc_sl_factor = *arc_netaccel;
                        }
                        else
                        {
                            *arc_sl_factor = 1.0;
                        }
                        *arc_sl_stride = (fullSlice - (float)arc_sl_mincalwidth) /
                            (fullSlice / *arc_sl_factor - (float)arc_sl_mincalwidth);
                    }
                    else
                    {
                        if( (*arc_netaccel) <= arc_maxnetaccel + 0.01 )
                        {
                            *arc_sl_factor = *arc_netaccel;
                            *arc_sl_stride = (fullSize - calSize) / (accelSize - calSize);
                        }
                        else
                        {
                            *arc_sl_factor = 1.0;
                        }
                    }
                    *arc_ph_factor = 1.0;
                    *arc_ph_stride = 1.0;
                }
            }
        }
        else
        {
            *arc_ph_factor = (float)1.0;
            *arc_sl_factor = (float)1.0;
            *arc_ph_stride = (float)1.0;
            *arc_sl_stride = (float)1.0;
        }
    }

    *arc_ph_calwidth = arc_ph_mincalwidth;
    *arc_sl_calwidth = arc_sl_mincalwidth;

    /* recalculate or factors and cal size when integer accel */
    if ((arc_ph_intaccel || arc_sl_intaccel) && (opautogem_factor || ((*arc_netaccel) > 1.0)))
    {
        /* Limit based on coil capabilities */
        if (arc_ph_intaccel)
        {
            *arc_ph_stride = FMin(2, phLimit, ceilf(*arc_ph_stride));
        }
        if (arc_sl_intaccel)
        {
            *arc_sl_stride = FMin(2, slLimit, ceilf(*arc_sl_stride));
        }

        if (CROSS_CAL == cal_shape)
        {
            /* 1D:  cal + (accel outer lines) = accel lines */
            if (arc_ph_intaccel)
            {
                *arc_ph_calwidth = IMin(2,(int)fullPhase,
                                        (int)((fullPhase*((*arc_ph_stride) - *arc_ph_factor)) /
                                              ((*arc_ph_stride - 1.0) * (*arc_ph_factor))) );
                *arc_ph_calwidth = IMax(2, arc_ph_mincalwidth, *arc_ph_calwidth);
                *arc_ph_calwidth = IMin(2, (int)fullPhase, *arc_ph_calwidth);
            }
            if (arc_sl_intaccel)
            {
                *arc_sl_calwidth = IMin(2, (int)fullSlice,
                                        (int)((fullSlice*((*arc_sl_stride) - *arc_sl_factor)) /
                                              ((*arc_sl_stride - 1.0) * (*arc_sl_factor))) );
                *arc_sl_calwidth = IMax(2, arc_sl_mincalwidth, *arc_sl_calwidth);
                *arc_sl_calwidth = IMin(2, (int)fullSlice, *arc_sl_calwidth);
            }
        }
        else
        {
            /* BOX and ELLIPSE are non-separable. Adjust both sides */
            /* 2D: cal + (accel outer lines) = accel lines */
            /* Pack calibration based on or factors to accomodate ARC kernel better */
            float calAspectRatio = (*arc_ph_stride)/(*arc_sl_stride);
            float or_factor = (*arc_ph_stride) * (*arc_sl_stride);

            calSize = (or_factor * accelSize - fullSize) / (or_factor - 1.0);

            if (ELLIPTICAL_CAL == cal_shape)
            {   /* Find the bounding box */
                calSize = calSize * 4.0/PI;
            }
            *arc_sl_calwidth = IMin(2, (int)fullSlice, (int)ceil(sqrt(calSize)/calAspectRatio));
            *arc_sl_calwidth = IMax(2, arc_sl_mincalwidth, *arc_sl_calwidth);
            *arc_sl_calwidth = IMin(2, (int)fullSlice, *arc_sl_calwidth);

            *arc_ph_calwidth = IMin(2, (int)fullPhase, (int)ceil(calSize/(float)(*arc_sl_calwidth)));
            *arc_ph_calwidth = IMax(2, arc_ph_mincalwidth, *arc_ph_calwidth);
            *arc_ph_calwidth = IMin(2, (int)fullPhase, *arc_ph_calwidth);
        }
    }

    return SUCCESS;
}

/*  setMaxArcFactor()
 *  Description:
 *     This function sets the maximum ARC factor in phase and slice
 *     direction given user prescribed resolution (fully sampled), accel
 *     limit, and the overscan size and shapes.
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I)    const float phLimit - phase direction acceleration limit
 *  (I)    const float slLimit - slice direction acceleration limit
 *  (I)    const float phRecStride - phase direction recommended outer acceleration
 *  (I)    const float slRecStride - slice direction recommended outer acceleration
 *  (I)    const float phRecLimStride - phase direction recommended limit outer acceleration
 *  (I)    const float slRecLimStride - slice direction recommended limit outer acceleration
 *  (I)    const float fullPhase - number of phase encoding when fully sampled
 *  (I)    const float fullSlice - number of slice encoding when fully sampled
 *  (I)    const CAL_PARAM calMinregion - structure holding min. size
 *                                        calibration region info
 *
 *  (O)    float *arc_phmaxslreclim_netaccel - max phase accel combined with recommended limit
 *                                  slice accel given user prescribed resolution
 *  (O)    float *arc_maxnetaccel - max combined accel factor given user
 *                                  prescribed resolution
 *  (O)    float *arc_ph_maxnetaccel - max accel factor in phase given user
 *                                  presribed fully sampled phase encoding
 *  (O)    float *arc_sl_maxnetaccel - max accel factor in slice given user
 *                                  presribed fully sampled slice encoding
 *  (O)    float *arc_recnetaccel - recommended combined accel factor given user
 *                                  prescribed resolution
 *  (O)    float *arc_reclimnetaccel - recommended limit combined accel factor given user
 *                                  prescribed resolution
 *  (O)    float *arc_ph_recnetaccel - Recommended net acceleration in phase dir
 *  (O)    float *arc_sl_recnetaccel - Recommended net acceleration in slice dir
 *  (O)    float *arc_ph_reclimnetaccel - Recommended limit net acceleration in phase dir
 *  (O)    float *arc_sl_reclimnetaccel - Recommended limit net acceleration in slice dir
 *
 */
STATUS
setMaxArcFactor(const float phLimit,
                const float slLimit,
                const float phRecStride,
                const float slRecStride,
                const float phRecLimStride,
                const float slRecLimStride,
                const float fullPhase,
                const float fullSlice,
                const CAL_PARAM calMinRegion,
                float *arc_phmaxslreclim_netaccel,
                float *arc_maxnetaccel,
                float *arc_ph_maxnetaccel,
                float *arc_sl_maxnetaccel,
                float *arc_recnetaccel,
                float *arc_reclimnetaccel,
                float *arc_ph_recnetaccel,
                float *arc_sl_recnetaccel,
                float *arc_ph_reclimnetaccel,
                float *arc_sl_reclimnetaccel)
{
    const CHAR * funcName = "setMaxArcFactor";

    int phOverscans = calMinRegion.phaseCutoffUpper - calMinRegion.phaseCutoffLower + 1;
    int slOverscans = calMinRegion.sliceCutoffUpper - calMinRegion.sliceCutoffLower + 1;

    /* Cache old input and outputs
       Initialize all to -1 to force first time execution*/
    static float old_arc_phmaxslreclim_netaccel = -1.0;
    static float old_arc_maxnetaccel = -1.0;
    static float old_arc_ph_maxnetaccel = -1.0;
    static float old_arc_sl_maxnetaccel = -1.0;
    static float old_arc_recnetaccel = -1.0;
    static float old_arc_reclimnetaccel = -1.0;
    static float old_arc_ph_recnetaccel = -1.0;
    static float old_arc_sl_recnetaccel = -1.0;
    static float old_arc_ph_reclimnetaccel = -1.0;
    static float old_arc_sl_reclimnetaccel = -1.0;

    static float old_phLimit = -1.0;
    static float old_slLimit = -1.0;
    static float old_phRecStride = -1.0;
    static float old_slRecStride = -1.0;
    static float old_phRecLimStride = -1.0;
    static float old_slRecLimStride = -1.0;
    static float old_fullPhase = -1.0;
    static float old_fullSlice = -1.0;
    static int old_calshape = 1;
    static int old_phOverscans = -1;
    static int old_slOverscans = -1;

    /* Input are the same as cached values.  Use cached result */
    int noChange = ((old_phLimit == phLimit) && (old_slLimit == slLimit) &&
                    (old_phRecStride == phRecStride) && (old_slRecStride == slRecStride) &&
                    (old_phRecLimStride == phRecLimStride) && (old_slRecLimStride == slRecLimStride) &&
                    (old_fullPhase == fullPhase) && (old_fullSlice == fullSlice) &&
                    (old_calshape == calMinRegion.shape) &&
                    (old_phOverscans == phOverscans) && (old_slOverscans == slOverscans));

    if (noChange)
    {
        *arc_phmaxslreclim_netaccel = old_arc_phmaxslreclim_netaccel;
        *arc_maxnetaccel = old_arc_maxnetaccel;
        *arc_ph_maxnetaccel = old_arc_ph_maxnetaccel;
        *arc_sl_maxnetaccel = old_arc_sl_maxnetaccel;
        *arc_recnetaccel = old_arc_recnetaccel;
        *arc_reclimnetaccel = old_arc_reclimnetaccel;
        *arc_ph_recnetaccel = old_arc_ph_recnetaccel;
        *arc_sl_recnetaccel = old_arc_sl_recnetaccel;
        *arc_ph_reclimnetaccel = old_arc_ph_reclimnetaccel;
        *arc_sl_reclimnetaccel = old_arc_sl_reclimnetaccel;
    }
    else
    {
        float fullSize = 0;
        float calSize = 0;
        int view, slice;
        int isCal;     /* Is data calibration */
        int isMaxSampled; /* Is sampled at max acceleration */
        int isRecSampled; /* Is sampled at rec acceleration */
        int isRecLimSampled; /* Is sampled at rec limit acceleration */
        int isphMaxslRecLimSampled; /* Is sampled at ph max and sl rec lim acceleration */
        int isphMaxSampled; /* Is sampled at ph max and sl=1 acceleration */
        int isslMaxSampled; /* Is sampled at sl max and ph=1 acceleration */
        int isphRecSampled; /* Is sampled at ph rec and sl=1 acceleration */
        int isslRecSampled; /* Is sampled at sl rec and ph=1 acceleration */
        int isphRecLimSampled; /* Is sampled at ph rec lim and sl=1 acceleration */
        int isslRecLimSampled; /* Is sampled at sl rec lim and ph=1 acceleration */
        int phMaxslRecLimSampledNoMask = 0;
        int maxSampledNoMask = 0;
        int recSampledNoMask = 0;
        int recLimSampledNoMask = 0;
        int phMaxSampledNoMask = 0;
        int slMaxSampledNoMask = 0;
        int phRecSampledNoMask = 0;
        int slRecSampledNoMask = 0;
        int phRecLimSampledNoMask = 0;
        int slRecLimSampledNoMask = 0;

        if (CROSS_CAL == calMinRegion.shape)
        {
            /* Cross sampling pattern.  Used simple relationships */
            float accelPhCalMax = ceil((fullPhase - phOverscans)/phLimit + phOverscans);
            float accelSlCalMax = ceil((fullSlice - slOverscans)/slLimit + slOverscans);
            float accelPhCalRec = ceil((fullPhase - phOverscans)/phRecStride + phOverscans);
            float accelSlCalRec = ceil((fullSlice - slOverscans)/slRecStride + slOverscans);
            float accelPhCalRecLim = ceil((fullPhase - phOverscans)/phRecLimStride + phOverscans);
            float accelSlCalRecLim = ceil((fullSlice - slOverscans)/slRecLimStride + slOverscans);

            *arc_ph_maxnetaccel = FMax(2, fullPhase / accelPhCalMax, 1.0);
            *arc_sl_maxnetaccel = FMax(2, fullSlice / accelSlCalMax, 1.0);
            *arc_maxnetaccel = *arc_ph_maxnetaccel * *arc_sl_maxnetaccel;

            *arc_ph_recnetaccel = FMax(2, fullPhase / accelPhCalRec, 1.0);
            *arc_sl_recnetaccel = FMax(2, fullSlice / accelSlCalRec, 1.0);
            *arc_recnetaccel = *arc_ph_recnetaccel * *arc_sl_recnetaccel;

            *arc_ph_reclimnetaccel = FMax(2, fullPhase / accelPhCalRecLim, 1.0);
            *arc_sl_reclimnetaccel = FMax(2, fullSlice / accelSlCalRecLim, 1.0);
            *arc_reclimnetaccel = *arc_ph_reclimnetaccel * *arc_sl_reclimnetaccel;
            *arc_phmaxslreclim_netaccel = *arc_ph_maxnetaccel * *arc_sl_reclimnetaccel;
        }
        else
        {
            /* Walk sampling pattern for other sampling patterns */
            for (view=0; view<fullPhase; view++)
            {
                for (slice=0; slice<fullSlice; slice++)
                {
                    isCal = calibration_voxel(view, slice, calMinRegion);

                    isMaxSampled = accelerated_voxel(view, slice, calMinRegion,
                                                     phLimit, slLimit);

                    isRecSampled = accelerated_voxel(view, slice, calMinRegion,
                                                     phRecStride, slRecStride);

                    isRecLimSampled = accelerated_voxel(view, slice, calMinRegion,
                                                        phRecLimStride, slRecLimStride);

                    isphMaxSampled = accelerated_voxel(view, slice, calMinRegion,
                                                       phLimit, 1.0);

                    isslMaxSampled = accelerated_voxel(view, slice, calMinRegion,
                                                       1.0, slLimit);

                    isphRecSampled = accelerated_voxel(view, slice, calMinRegion,
                                                       phRecStride, 1.0);

                    isslRecSampled = accelerated_voxel(view, slice, calMinRegion,
                                                       1.0, slRecStride);

                    isphRecLimSampled = accelerated_voxel(view, slice, calMinRegion,
                                                          phRecLimStride, 1.0);

                    isslRecLimSampled = accelerated_voxel(view, slice, calMinRegion,
                                                          1.0, slRecLimStride);

                    isphMaxslRecLimSampled = accelerated_voxel(view, slice, calMinRegion,
                                                               phLimit, slRecLimStride);

                    if (isCal || isMaxSampled)
                    {
                        maxSampledNoMask++;
                        if (isCal)
                        {
                            calSize++;
                        }
                    }
                    if (isCal || isRecSampled)
                    {
                        recSampledNoMask++;
                    }
                    if (isCal || isRecLimSampled)
                    {
                        recLimSampledNoMask++;
                    }
                    if (isCal || isphMaxSampled)
                    {
                        phMaxSampledNoMask++;
                    }
                    if (isCal || isslMaxSampled)
                    {
                        slMaxSampledNoMask++;
                    }
                    if (isCal || isphRecSampled)
                    {
                        phRecSampledNoMask++;
                    }
                    if (isCal || isslRecSampled)
                    {
                        slRecSampledNoMask++;
                    }
                    if (isCal || isphRecLimSampled)
                    {
                        phRecLimSampledNoMask++;
                    }
                    if (isCal || isslRecLimSampled)
                    {
                        slRecLimSampledNoMask++;
                    }
                    if (isCal || isphMaxslRecLimSampled)
                    {
                        phMaxslRecLimSampledNoMask++;
                    }
                }
            }
            fullSize = fullPhase * fullSlice;

            if (0 == maxSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_maxnetaccel = FMax(2, fullSize/(float)maxSampledNoMask, 1.0);

            if (0 == phMaxSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_ph_maxnetaccel = FMax(2, fullSize/(float)phMaxSampledNoMask, 1.0);

            if (0 == slMaxSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_sl_maxnetaccel = FMax(2, fullSize/(float)slMaxSampledNoMask, 1.0);

            if (0 == recSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_recnetaccel = FMax(2, fullSize/(float)recSampledNoMask, 1.0);

            if (0 == recLimSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_reclimnetaccel = FMax(2, fullSize/(float)recLimSampledNoMask, 1.0);

            if (0 == phRecSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_ph_recnetaccel = FMax(2, fullSize/(float)phRecSampledNoMask, 1.0);

            if (0 == slRecSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_sl_recnetaccel = FMax(2, fullSize/(float)slRecSampledNoMask, 1.0);

            if (0 == phRecLimSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_ph_reclimnetaccel = FMax(2, fullSize/(float)phRecLimSampledNoMask, 1.0);

            if (0 == slRecLimSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_sl_reclimnetaccel = FMax(2, fullSize/(float)slRecLimSampledNoMask, 1.0);

            if (0 == phMaxslRecLimSampledNoMask)
            {
                printf("%s: Division by zero\n", funcName);
                return FAILURE;
            }
            *arc_phmaxslreclim_netaccel = FMax(2, fullSize/(float)phMaxslRecLimSampledNoMask, 1.0);
        }

        old_arc_maxnetaccel = *arc_maxnetaccel;
        old_arc_ph_maxnetaccel = *arc_ph_maxnetaccel;
        old_arc_sl_maxnetaccel = *arc_sl_maxnetaccel;

        old_arc_recnetaccel = *arc_recnetaccel;
        old_arc_reclimnetaccel = *arc_reclimnetaccel;
        old_arc_ph_recnetaccel = *arc_ph_recnetaccel;
        old_arc_sl_recnetaccel = *arc_sl_recnetaccel;
        old_arc_ph_reclimnetaccel = *arc_ph_reclimnetaccel;
        old_arc_sl_reclimnetaccel = *arc_sl_reclimnetaccel;
        old_arc_phmaxslreclim_netaccel = *arc_phmaxslreclim_netaccel;

        old_phLimit = phLimit;
        old_slLimit = slLimit;
        old_phRecStride = phRecStride;
        old_slRecStride = slRecStride;
        old_phRecLimStride = phRecLimStride;
        old_slRecLimStride = slRecLimStride;
        old_fullPhase = fullPhase;
        old_fullSlice = fullSlice;
        old_calshape = calMinRegion.shape;
        old_phOverscans = calMinRegion.phaseCutoffUpper - calMinRegion.phaseCutoffLower + 1;
        old_slOverscans = calMinRegion.sliceCutoffUpper - calMinRegion.sliceCutoffLower + 1;
    }

    return SUCCESS;
}


/* setAutoArcFactor()
 *  Description:
 *    This function sets the arc_netaccel to user defined arc factor or
 *    recommended value
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const float phLimit - acceleration limit in phase
 *  (I) const float slLimit - acceleration limit in slice
 *  (I) const int higherOuterAccel - 1: use higher recommended outer Accel values
 *                                   0: use typical Outer Acceleration values
 *  (O) float arc_ph_recstride - ARC outer acceleration factor in phase dir
 *  (O) float arc_sl_recstride - ARC outer acceleration factor in slice dir
 *  (O) float arc_ph_reclimstride - ARC outer acceleration rec. limit factor in phase dir
 *  (O) float arc_sl_reclimstride - ARC outer acceleration rec. limit factor in slice dir
 *
 */
STATUS
setAutoArcFactor(const float phLimit,
                 const float slLimit,
                 const int higherOuterAccel,
                 float *arc_ph_recstride,
                 float *arc_sl_recstride,
                 float *arc_ph_reclimstride,
                 float *arc_sl_reclimstride)

{
    if ((1.0 == slLimit) && (1.0 == phLimit))
    {
        *arc_ph_recstride = 1.0;
        *arc_sl_recstride = 1.0;
        *arc_ph_reclimstride = 1.0;
        *arc_sl_reclimstride = 1.0;
    }
    else if (1.0 == slLimit)
    {  /* Phase only acceleration */
        *arc_sl_recstride = 1.0;
        *arc_sl_reclimstride = 1.0;
        *arc_ph_reclimstride = phLimit;

        if (phLimit <= 2.0)
        {
            *arc_ph_recstride = phLimit;
        }
        else if (phLimit <= 2.5)
        {
            *arc_ph_recstride = 2.0;
        }
        else
        {
            *arc_ph_recstride = FMax(2, phLimit - 2.0, 2.5);
        }
    }
    else if (1.0 == phLimit)
    {   /* Slice only acceleration */
        *arc_ph_recstride = 1.0;
        *arc_ph_reclimstride = 1.0;
        *arc_sl_reclimstride = slLimit;

        if (slLimit <= 2.0)
        {
            *arc_sl_recstride = slLimit;
        }
        else if (slLimit <= 2.5)
        {
            *arc_sl_recstride = 2.0;
        }
        else if (slLimit <= 3.0)
        {
            *arc_sl_recstride = 2.5;
        }
        else
        {
            *arc_sl_recstride = FMax(2, slLimit - 2.0, 2.5);
        }
    }
    else
    { /* 2D acceleration capable */
        if ((phLimit <= 2.0) && (slLimit <= 2.0))
        {
            *arc_ph_recstride = phLimit;
            *arc_sl_recstride = 1.0;
            *arc_ph_reclimstride = phLimit;
            *arc_sl_reclimstride = 1.0;
        }
        else if ((phLimit <= 3.0) && (slLimit <= 2.5))
        {
            *arc_ph_recstride = FMin(2, phLimit, 2.0);
            *arc_sl_recstride = FMin(2, slLimit, 1.0);
            *arc_ph_reclimstride = FMin(2, phLimit, 2.0);
            *arc_sl_reclimstride = FMin(2, slLimit, 1.75);
        }
        else if ((phLimit <= 2.5) && (slLimit <= 3.0))
        {
            *arc_ph_recstride = FMin(2, phLimit, 2.0);
            *arc_sl_recstride = FMin(2, slLimit, 1.0);
            *arc_ph_reclimstride = FMin(2, phLimit, 2.0);
            *arc_sl_reclimstride = FMin(2, slLimit, 1.75);
        }
        else
        { /* Limit recommended outer accel to 2x2 or coil limits if lower */
            *arc_ph_recstride = FMin(2, phLimit, 2.0);
            *arc_sl_recstride = FMin(2, slLimit, 1.5);
            *arc_ph_reclimstride = FMin(2, phLimit, 2.5);
            *arc_sl_reclimstride = FMin(2, slLimit, 2.0);
        }
    }

    return SUCCESS;
}

/*  calcTargetAmp()
 *  Description:
 *    Compute gradient amplitute that would yield
 *    trapezoidal or triangular shape with duration close to
 *    the desired duration.
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const FLOAT targetArea - desired gradient area (G*us/cm)
 *  (I) const FLOAT slewRate - desired slew rate (G/cm*us)
 *  (I) const INT targetDuration - desired pulse duration (us)
 *  (I) const FLOAT targetAmpMin - minimum gradient amplitude (G/cm)
 *  (I) const FLOAT targetAmpMax - maximum gradient amplitude (G/cm)
 *  (I) const FLOAT startAmp -  amplitude of start point (G/cm)
 *  (I) const FLOAT endAmp - amplitude of end point (G/cm)
 *  (I) const INT bridge_flag - flag to identify bridge pulse: 1-bridge pulse, 0-trapezoid pulse
 *  (O) FLOAT targetAmp - desired gradient amplitude (G/cm)
 *
 */

FLOAT
calcTargetAmp(const FLOAT targetArea,
              const FLOAT slewRate,
              const INT targetDuration,
              const FLOAT targetAmpMin,
              const FLOAT targetAmpMax,
              const FLOAT startAmp,
              const FLOAT endAmp,
              const INT bridge_flag)
{
    FLOAT a, b, c, d, e, delta, ta, biggerAmp, smallerAmp;
    FLOAT targetAmp = 0.0;

    if (bridge_flag) /* to amplitude for Bridge pulse */
    {
        ta = fabs(startAmp-endAmp)/slewRate; /* ramp time from startAmp to endAmp */
        d = ta*(startAmp+endAmp)*0.5; /* area of trapezoid */
        biggerAmp = (startAmp > endAmp) ? startAmp : endAmp;
        smallerAmp = (startAmp > endAmp) ? endAmp : startAmp;

        e = d+(targetDuration-ta)*biggerAmp; /* area @ amplitude = biggerAmp */

        if (targetArea <= e) /* solution @ amplitude <= bigggerAmp */
        {
            if (targetArea < (d+(targetDuration-ta)*smallerAmp))
            {
                /* This situation should not happen. If happened, return minimum Amplitude. */
                targetAmp = targetAmpMin;
            } 
            else
            {
                targetAmp = (targetArea-d)/(targetDuration-ta);
            }
        }
        else /* solution @ amplitude > biggerAmp */
        {
            a = 1.0/slewRate;
            b = ta-targetDuration;
            c = targetArea-e;
            delta = b*b-4.0*a*c;

            if (delta < 0.0)
            {
                targetAmp = targetAmpMax;
            }
            else
            {
                targetAmp = biggerAmp + (-b - sqrt(delta))/(2.0*a);
            }
        }
    }
    else /* same as original algorithm: to get amplitude for Trapezoid and Triangular pulses */
    {
        a = -1.0/slewRate;
        b = 1.0*targetDuration;
        c = -targetArea;
        delta = (b*b-4.0*a*c);
        if (delta < 0.0)
        {
            if ( targetArea <= (targetAmpMax*targetAmpMax/slewRate) )
            {
                /* Triangular solution */
                targetAmp = sqrt(targetArea*slewRate);
            }
            else
            {
                targetAmp = targetAmpMax;
            }
        }
        else
        {
            targetAmp = (-b + sqrt(delta))/(2.0*a);
        }
    }

    targetAmp = FMax (2, targetAmp, targetAmpMin);
    targetAmp = FMin (2, targetAmp, targetAmpMax);

    return targetAmp;
}

/*  calcTargetAmp2()
 *  Description:
 *    Compute gradient amplitute that would yield two
 *    trapezoidal or triangular shapes with duration close to
 *    the desired duration.
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const FLOAT targetArea1 - desired gradient area1 (G*us/cm)
 *  (I) const FLOAT targetArea2 - desired gradient area2 (G*us/cm)
 *  (I) const FLOAT slewRate - desired slew rate (G/cm*us)
 *  (I) const INT targetDuration - desired pulse duration (us)
 *  (I) const FLOAT targetAmpMin - minimum gradient amplitude (G/cm)
 *  (I) const FLOAT targetAmpMax - maximum gradient amplitude (G/cm)
 *  (O) FLOAT targetAmp - desired gradient amplitude (G/cm)
 *
 */

FLOAT
calcTargetAmp2(const FLOAT targetArea1,
               const FLOAT targetArea2,
               const FLOAT slewRate,
               const INT targetDuration,
               const FLOAT targetAmpMin,
               const FLOAT targetAmpMax)
{
    int i, tmpDuration;
    float targetAmp, tmpAmpMin, tmpAmpMax;

    tmpAmpMin = targetAmpMin;
    tmpAmpMax = targetAmpMax;
    targetAmp = targetAmpMax;

    /* initial tmpDuration to ensure it can enter for{} */
    tmpDuration = targetDuration + 8;

    for (i=0; (i<30) && (fabs(tmpDuration - targetDuration)>=4) ;i++)
    {
        targetAmp = (tmpAmpMin + tmpAmpMax)*0.5;
        tmpDuration = calcDuration(targetArea1,slewRate,0,0.0,0.0,targetAmp) +
                      calcDuration(targetArea2,slewRate,0,0.0,0.0,targetAmp);

        if(tmpDuration < targetDuration)
        {
            tmpAmpMax = targetAmp;
        }
        else
        {
            tmpAmpMin = targetAmp;
        }
    }

    return targetAmp;
}

/*  calcPower()
 *  Description:
 *    Compute power that would yield
 *    trapezoidal or triangular shape or bridge trapezoidal
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const FLOAT targetArea - desired gradient area (G*us/cm)
 *  (I) const FLOAT slewRate - desired slew rate (G/cm*us)
 *  (I) const INT bridge_flag  - flag to identify if bridge trapezoidal is used
 *  (I) const FLOAT startAmp - gradient amplitude of start point (G/cm)
 *  (I) const FLOAT endAmp -  gradient amplitude of end point (G/cm)
 *  (I) const FLOAT targetAmp - maximum gradient amplitude (G/cm)
 *  (O) FLOAT outputPower - power generated 
 *
 */

FLOAT
calcPower(const FLOAT targetArea,
          const FLOAT slewRate,
          const INT bridge_flag,
          const FLOAT startAmp,
          const FLOAT endAmp,
          const FLOAT targetAmp)
{
    FLOAT a,b,c,d,e,f,biggerAmp,ta,tb,tmpArea,outputPower,smallerAmp;
    INT targetDuration;

    if (bridge_flag) /* solution to get duration for bridge pulse */
    {
        ta = fabs(startAmp-endAmp)/slewRate; /* ramp time from startAmp to endAmp */
        a = ta*fabs(startAmp+endAmp)*0.5; /* minimum legal area */

        biggerAmp = (startAmp > endAmp) ? startAmp : endAmp;
        smallerAmp = (startAmp < endAmp) ? startAmp : endAmp;

        if (targetAmp > biggerAmp)
        {
            c = (targetAmp-biggerAmp)/slewRate; /* ramp time from biggerAmp to targetAmp */
            b = a+(targetAmp+biggerAmp)*c; /* minimum area @ amplitude = targetAmp */
        }
        else /* if targetAmp <= biggerAmp, only one situation will happen; so set b = a */
        {
            c = 0.0;
            b = a;
        }
 
        e = smallerAmp/slewRate; /* ramp time from zero to smallerAmp */
        f = e+ta; /* ramp time from zero to biggerAmp */

        if (targetArea < a)
        {
            /* this situation should not happen. Reture 0 when it happen. */
            outputPower = 0;
        }
        else if (targetArea < b) /* solution for "part of triangle pulse" */
        {
            tmpArea = targetArea-a;
            tb = (sqrt(tmpArea*slewRate+biggerAmp*biggerAmp)-biggerAmp)/slewRate;
            d = tb+ta+e;
            outputPower = 1.0/3.0*((d*slewRate)*(d*slewRate)*d*2.0 - (e*slewRate)*(e*slewRate)*e - (f*slewRate)*(f*slewRate)*f);
        }
        else /* solution for "part of trapezoid pulse" */
        {
            tmpArea = targetArea-b;

            if (targetAmp < biggerAmp)
            {
                outputPower = tmpArea*targetAmp + 1.0/3.0*biggerAmp*biggerAmp*f - 1.0/3.0*smallerAmp*smallerAmp*e;
            }
            else
            {
                outputPower = tmpArea*targetAmp + 1.0/3.0*(targetAmp*targetAmp*(c+f)*2.0 - biggerAmp*biggerAmp*f - smallerAmp*smallerAmp*e);
            }
        }
    }
    else /* solution for triangle and trapezoid pulses */
    {
        a = targetAmp * targetAmp / slewRate; /* maximum area for triangle case */
        if (targetArea < a) /* triangle */
        {
            targetDuration = (int)(2*targetAmp/slewRate*sqrt(targetArea/a));
            outputPower = (1.0/12.0)*slewRate*slewRate*targetDuration*targetDuration*targetDuration;
        }
        else /* trapezoid */
        {
            targetDuration = (int)(targetArea/targetAmp + targetAmp/slewRate);
            outputPower = (targetAmp*targetAmp)*(targetDuration - 4.0/3.0*targetAmp/slewRate);
        }
    }

    return outputPower;
}

/*  calcDuration()
 *  Description:
 *    Compute duration that would yield
 *    trapezoidal or triangular shape or bridge trapezoidal
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const FLOAT targetArea - desired gradient area (G*us/cm)
 *  (I) const FLOAT slewRate - desired slew rate (G/cm*us)
 *  (I) const INT bridge_flag  - flag to identify if bridge trapezoidal is used
 *  (I) const FLOAT startAmp - gradient amplitude of start point (G/cm)
 *  (I) const FLOAT endAmp -  gradient amplitude of end point (G/cm)
 *  (I) const FLOAT targetAmp - maximum gradient amplitude (G/cm)
 *  (O) INT targetDuration - desired pulse duration (us) 
 *
 */

INT
calcDuration(const FLOAT targetArea,
             const FLOAT slewRate,
             const INT bridge_flag,
             const FLOAT startAmp,
             const FLOAT endAmp,
             const FLOAT targetAmp)
{
    FLOAT a,b,c,biggerAmp,ta,tb,tmpArea;
    INT targetDuration;

    if (bridge_flag) /* solution to get duration for bridge pulse */
    {
        ta = fabs(startAmp-endAmp)/slewRate;
        /* SVBranch GEHmr03661 Add fabs() fpr a_gx1, and a_gxw */
        a = ta*fabs(startAmp+endAmp)*0.5; /* minimum legal area */

        biggerAmp = (startAmp > endAmp) ? startAmp : endAmp;

        if (targetAmp > biggerAmp)
        {
            c = (targetAmp-biggerAmp)/slewRate; /* ramp time from biggerAmp to targetAmp */
            b = a+(targetAmp+biggerAmp)*c; /* minimum area @ amplitude = targetAmp */
        }
        else /* if targetAmp <= biggerAmp, only one situation will happen; so set b = a */
        {
            c = 0.0;
            b = a;
        }

        if (targetArea < a)
        {
            /* this situation should not happen. Reture 0 when it happen. */
            targetDuration = 0;
        }
        else if(targetArea < b) /* solution for "part of triangle pulse" */
        {
            tmpArea = targetArea-a;
            tb = (sqrt(tmpArea*slewRate+biggerAmp*biggerAmp)-biggerAmp)/slewRate;
            targetDuration = (int)(ta+2*tb);
        }
        else /* solution for "part of trapezoid pulse" */
        {
            tmpArea = targetArea-b;
            targetDuration = (int)(ta+2*c+tmpArea/targetAmp);
        }
    }
    else /* solution for triangle and trapezoid pulses */
    {
        a = targetAmp * targetAmp / slewRate; /* maximum area for triangle case */

        if (targetArea < a) /* triangle case */
        {
            targetDuration = (int)(2*targetAmp/slewRate*sqrt(targetArea/a));
        }
        else /* trapezoid case */
        {
            targetDuration = (int)(targetArea/targetAmp + targetAmp/slewRate);
        }
    }

    return targetDuration;
}

/*  setOptimizedGradientScalingFactor()
 *  Description:
 *    Compute optimal scaling factor to limit the
 *    maximum available gradient amplitute per axis.
 *    The maximum gradident amplitude is determined
 *    by the required encoding area and the available
 *    encoding time per axis. The maximum availale
 *    encoding time is based on the required encoding
 *    time of the most demanding axis for given protocol.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const FLOAT a_gx1 - amplitude of the frequency dephaser pulse (G/cm)
 *  (I) const INT pw_gx1a - attack ramp pulse width of GX1 (us)
 *  (I) const INT pw_gx1 - constant pulse width of GX1 (us)
 *  (I) const INT pw_gx1d - decay ramp pulse width of GX1 (us)
 *  (I) const FLOAT a_gxfc -  amplitude of the read-out flowcomp pulse (G/cm)
 *  (I) const INT pw_gxfca - attack ramp pulse width of GXFC (us)
 *  (I) const INT pw_gxfc - constant pulse width of GXFC (us)
 *  (I) const INT pw_gxfcd - decay ramp pulse width of GXFC (us)
 *  (I) const FLOAT a_gxw - amplitude of the read-out pulse (G/cm)
 *  (I) const INT pw_gxwa -  attack ramp pulse width of GXW (us)
 *  (I) const INT pw_gxw - constant pulse width of GXW (us)
 *  (I) const INT pw_gxwd - decay ramp pulse width of GXW (us)
 *  (I) const FLOAT a_gxwex - amplitude of the read-out killer pulse (G/cm)
 *  (I) const INT pw_gxwexa -  attack ramp pulse width of GXWEX (us)
 *  (I) const INT pw_gxwex - constant pulse width of GXWEX (us)
 *  (I) const INT pw_gxwexd - decay ramp pulse width of GXWEX (us)
 *  (I) const FLOAT a_gy1 - amplitude of the phase encoding pulse (G/cm)
 *  (I) const INT pw_gy1a - attack ramp pulse width of GY1 (us)
 *  (I) const INT pw_gy1_tot - total duration of phase encoding pulse (us)
 *  (I) const FLOAT a_gzrf1 - amplitude of GZRF1 (G/cm)
 *  (I) const INT pw_gzrf1d - decay ramp pulse width of GZRF1 (us)
 *  (I) const FLOAT a_gyr1 - amplitude of the phase rewinder pulse (G/cm)
 *  (I) const INT pw_gy1ra - attack ramp pulse width of GY1r (us)
 *  (I) const INT pw_gy1r_tot - total duration of phase rewinder pulse (us)
 *  (I) const FLOAT a_gz1 - amplitude of the rephaser/flowcomp pulse (G/cm)
 *  (I) const INT pw_gz1a - attack ramp pulse width of GZ1 (us)
 *  (I) const INT pw_gz1 - constant pulse width of GZ1 (us)
 *  (I) const INT pw_gz1d - decay ramp pulse width of GZ1 (us)
 *  (I) const FLOAT a_gzcomba - amplitude of the slab encoding + rephaser pulse (G/cm)
 *  (I) const INT pw_gzcomba - attack ramp pulse width of GZCOMB (us)
 *  (I) const INT pw_gzcomb - constant pulse width of GZCOMB (us)
 *  (I) const INT pw_gzcombd - decay ramp pulse width of GZCOMB (us)
 *  (I) const INT pw_gzcomb_tot - total duration of slab encoding + rephaser pulse (us)
 *  (I) const FLOAT a_gzpa - amplitude of the slab rewinder + killer pulse (G/cm)
 *  (I) const INT pw_gzpa - attack ramp pulse width of GZP (us)
 *  (I) const INT pw_gzp - constant pulse width of GZP (us)
 *  (I) const INT pw_gzpd - decay ramp pulse width of GZP (us)
 *  (I) const INT gzptime - total duration of slab rewinder + killer pulse (us)
 *  (I) const INT phaseres - number of unaccelerated phase encoding steps
 *  (I) const FLOAT opfov - prescribed FOV (cm)
 *  (I) const FLOAT opphasefov - fraction of FOV in phase encoding direction
 *  (I) const FLOAT fov_phase_scale - scale of FOV in phase encoding direction
 *  (I) const FLOAT asset_factor - ASSET phase encoding reduction factor
 *  (I) const FLOAT nop - no phase wrap processing flag
 *  (I) const INT equant - number of unaccelerated slab encoding steps
 *  (I) const FLOAT ethick - FOV in slab encoding direction (mm)
 *  (I) const FLOAT refocus - slab rephaser area (G*us/cm)
 *  (I) const INT aTEopt_flag - adaptive TE optimization flag
 *  (I) const INT aTRopt_flag - adaptive TR optimization flag
 *  (I) const INT gxwex_bridge - flag to indicate GXW bridge with GXWEX
 *  (I) const FLOAT fecho_factor - percentage of the echo acquired
 *  (I) const FLOAT GAM - gyromagnetic ratio (Hz/G)
 *  (I) const INT opfcomp - flowcomp flag
 *  (I) const FLOAT ogsfMin - maximum normalize scaling factor
 *  (I) const FLOAT ogsfMax - minimum normalize scaling factor
 *  (I) const FLOAT xTargetAmp - target Amplitude for gx1(&gxfc) (Gs/cm)
 *  (I) const FLOAT yTargetAmp - target Amplitude for gy1 (Gs/cm)
 *  (I) const FLOAT zTargetAmp - target Amplitude for gzcomb(&gz1) (Gs/cm)
 *  (I) const FLOAT xkTargetAmp - target Amplitude for gxwex (Gs/cm)
 *  (I) const FLOAT ykTargetAmp - target Amplitude for gy1r (Gs/cm)
 *  (I) const FLOAT zkTargetAmp - target Amplitude for gzp (Gs/cm)
 *  (I) const FLOAT slewRate - slewRate for all gradient pulses (Gs/cm)
 *  (I) const INT method - new method flag: 0- legacy method, 1- new method
 *  (O) FLOAT *ogsfX1 - scaling factor for GX1
 *  (O) FLOAT *ogsfXw - scaling factor for GXW
 *  (O) FLOAT *ogsfXwex - scaling factor for GXWEX
 *  (O) FLOAT *ogsfY - scaling factor for GY1
 *  (O) FLOAT *ogsfYk - scaling factor for GY1R
 *  (O) FLOAT *ogsfZ - scaling factor for GZ1, GZCOMB
 *  (O) FLOAT *ogsfZk - scaling factor for GZP
 *  (O) FLOAT *powerTE - power generated by Gx1(Gxfc), Gy1, Gz1(Gzcomb)
 *  (O) FLOAT *powerTR - power generated by Gxwex, Gy1r, Gzk
 *
 */

STATUS
setOptimizedGradientScalingFactor (const FLOAT a_gx1,
                                   const INT pw_gx1a,
                                   const INT pw_gx1,
                                   const INT pw_gx1d,
                                   const FLOAT a_gxfc,
                                   const INT pw_gxfca,
                                   const INT pw_gxfc,
                                   const INT pw_gxfcd,
                                   const FLOAT a_gxw,
                                   const INT pw_gxwa,
                                   const INT pw_gxw,
                                   const INT pw_gxwd,
                                   const FLOAT a_gxwex,
                                   const INT pw_gxwexa,
                                   const INT pw_gxwex,
                                   const INT pw_gxwexd,
                                   const FLOAT a_gy1a,
                                   const INT pw_gy1a,
                                   const INT pw_gy1_tot,
                                   const FLOAT a_gy1ra,
                                   const INT pw_gy1ra,
                                   const INT pw_gy1r_tot,
                                   const FLOAT a_gzrf1,
                                   const INT pw_gzrf1d,
                                   const FLOAT a_gz1,
                                   const INT pw_gz1a,
                                   const INT pw_gz1,
                                   const INT pw_gz1d,
                                   const FLOAT a_gzcomba,
                                   const INT pw_gzcomba,
                                   const INT pw_gzcomb,
                                   const INT pw_gzcombd,
                                   const INT pw_gzcomb_tot,
                                   const FLOAT a_gzpa,
                                   const INT pw_gzpa,
                                   const INT pw_gzp,
                                   const INT pw_gzpd,
                                   const INT gzptime,
                                   const INT phaseres,
                                   const FLOAT opfov,
                                   const FLOAT opphasefov,
                                   const FLOAT fov_phase_scale,
                                   const FLOAT asset_factor,
                                   const FLOAT nop,
                                   const INT equant,
                                   const FLOAT ethick,
                                   const FLOAT refocus,
                                   const INT aTEopt_flag,
                                   const INT aTRopt_flag,
                                   const INT gxwex_bridge,
                                   const FLOAT fecho_factor,
                                   const FLOAT GAM,
                                   const INT opfcomp,
                                   const FLOAT ogsfMin,
                                   const FLOAT ogsfMax,
                                   const FLOAT xTargetAmp,
                                   const FLOAT yTargetAmp,
                                   const FLOAT zTargetAmp,
                                   const FLOAT xkTargetAmp,
                                   const FLOAT ykTargetAmp,
                                   const FLOAT zkTargetAmp,
                                   const FLOAT slewRate,
                                   const INT method,
                                   const INT gradOpt_flag,  /* SVBranch HCSDM00100058 Set ogsf* based on gradOpt_flag */
                                   FLOAT *ogsfX1,
                                   FLOAT *ogsfXw,
                                   FLOAT *ogsfXwex,
                                   FLOAT *ogsfY,
                                   FLOAT *ogsfYk,
                                   FLOAT *ogsfZ,
                                   FLOAT *ogsfZk,
                                   FLOAT *powerTE,
                                   FLOAT *powerTR)
{
    float areaGx1, areaGxfc, areaGxwex, areaGzcomb, areaGz1, areaGzk, areaGy1, areaGy1r;
    float sr, scale, targetAmpMin, targetAmpMax;
    int targetDuration, areaMax, areaRead, areaRead2, areaPhase, areaPhase2, areaSlice, areaSlice2, maxRead, maxPhase, maxSlice;
    int duraMax, duraRead, duraRead2, duraPhase, duraPhase2, duraSlice, duraSlice2;

    maxRead = maxPhase = maxSlice = FALSE;

    if (opfcomp) {
        areaGx1 = fabs(a_gx1)*(0.5*pw_gx1a + pw_gx1 + 0.5*pw_gx1d);
        areaGxfc = fabs(a_gxfc)*(0.5*pw_gxfca + pw_gxfc + 0.5*pw_gxfcd);
    } else {
        areaGx1 = fabs(a_gxw)*((fecho_factor-0.5)*pw_gxw + 0.5*pw_gxwa);
        areaGxfc = 0.0;
    }

    areaGy1 = (0.5 * (FLOAT)(phaseres-1))/((nop*opfov*opphasefov*fov_phase_scale*asset_factor) * 0.1) * 1.0e6 / GAM;

    /*
    areaGy1r = (0.5 * (FLOAT)(phaseres-1))/((nop*opfov*opphasefov*fov_phase_scale*asset_factor) * 0.1) * 1.0e6 / GAM;
    */
    areaGy1r = areaGy1;

    areaGzcomb = (0.5 * (FLOAT)(equant-1))/(ethick * 0.1) * 1.0e6 / GAM + fabs(refocus);

    areaGz1 = (fabs(a_gz1)*(0.5*pw_gz1a + pw_gz1 + 0.5*pw_gz1d));

    areaGzk = fabs(a_gzpa)*(0.5*pw_gzpa + pw_gzp + 0.5*pw_gzpd);

    if (method == LEGACY_METHOD) /* legacy method: identify dominant pulse with "Area" */
    {   
        /*
        areaRead = (int) (100.0*((areaGx1+opfcomp*areaGxfc)*(pw_gx1a+pw_gx1+pw_gx1d+pw_gxwa+opfcomp*(pw_gxfca+pw_gxfc+pw_gxfcd))/
                             (pw_gx1a+pw_gx1+pw_gx1d+opfcomp*(pw_gxfca+pw_gxfc+pw_gxfcd))));
        */

    	areaRead = (int) (100.0*((areaGx1+opfcomp*areaGxfc) + fabs(a_gxw)*0.5*pw_gxwa));

        areaGxwex = fabs(a_gxwex)*(pw_gxwex+pw_gxwexd) - fabs(a_gxw)*0.5*(pw_gxwexd-pw_gxwexa);

        areaRead2 = (int) (100.0*areaGxwex*((pw_gxwexa+pw_gxwex+pw_gxwexd)+((!gxwex_bridge)*pw_gxwd))/(pw_gxwexa+pw_gxwex+pw_gxwexd));

        areaPhase = (int) (100.0*(areaGy1));

        areaPhase2 = (int) (100.0*(areaGy1r));
    
        /*
        areaSlice = (int) (100.0*((areaGzcomb+opfcomp*areaGz1)*(pw_gzcomba+pw_gzcomb+pw_gzcombd+pw_gzrf1d+opfcomp*(pw_gz1a+pw_gz1+pw_gz1d))/
                              (pw_gzcomba+pw_gzcomb+pw_gzcombd+opfcomp*(pw_gz1a+pw_gz1+pw_gz1d))));     
        */

        areaSlice = (int) (100.0*((areaGzcomb+opfcomp*areaGz1) + fabs(a_gzrf1)*0.5*pw_gzrf1d)); 

        areaSlice2 = (int) (100.0*areaGzk);
    }
    else if (method == POWER_METHOD) /* new method: identify dominant pulse with "duration" directly */
    {
        duraRead = calcDuration(areaGx1,slewRate,0,0.0,0.0,xTargetAmp) +
                   opfcomp*calcDuration(areaGxfc,slewRate,0,0.0,0.0,xTargetAmp) + pw_gxwa;

        if (gxwex_bridge)
        {
            areaGxwex = fabs(a_gxwex+a_gxw)*pw_gxwexa*0.5 + fabs(a_gxwex)*(pw_gxwex + pw_gxwexd*0.5);
        }
        else
        {
            areaGxwex = fabs(a_gxwex)*(pw_gxwex+0.5*pw_gxwexa+0.5*pw_gxwexd);
        }
 
        duraRead2 = calcDuration(areaGxwex,slewRate,gxwex_bridge,fabs(a_gxw),0.0,xkTargetAmp) + ((!gxwex_bridge)*pw_gxwd);

        duraPhase = calcDuration(areaGy1,slewRate,0,0.0,0.0,yTargetAmp);

        duraPhase2 = calcDuration(areaGy1r,slewRate,0,0.0,0.0,ykTargetAmp);

        duraSlice = calcDuration(areaGzcomb,slewRate,0,0.0,0.0,zTargetAmp) +
                    opfcomp*calcDuration(areaGz1,slewRate,0,0.0,0.0,zTargetAmp)+pw_gzrf1d;

        duraSlice2 = calcDuration(areaGzk,slewRate,0,0.0,0.0,zkTargetAmp);
    }
 
    if (method == LEGACY_METHOD) /* legacy method */
    {
        areaMax = IMax (3, areaRead, areaPhase, areaSlice);
        maxRead = (areaRead == areaMax);
        maxPhase = (areaPhase == areaMax);
        maxSlice = (areaSlice == areaMax);

        *ogsfXw = ogsfMax;

        if (maxRead)  {
            *ogsfX1 = ogsfMax;
            sr = (fabs(a_gx1)/pw_gx1a);
            scale = *ogsfX1/fabs(a_gx1);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = pw_gx1a + pw_gx1 + pw_gx1d + opfcomp*(pw_gxfca + pw_gxfc + pw_gxfcd) + pw_gxwa;
            *ogsfY = scale*calcTargetAmp(areaGy1, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfZ = scale*calcTargetAmp((areaGzcomb + opfcomp*areaGz1), sr, (targetDuration - pw_gzrf1d) , targetAmpMin, targetAmpMax, 0.0,0.0,0 );
        } else if (maxPhase)  {
            *ogsfY = ogsfMax;
            sr = (fabs(a_gy1a)/pw_gy1a);
            scale = *ogsfY/fabs(a_gy1a);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = pw_gy1_tot;
            *ogsfX1 = scale*calcTargetAmp((areaGx1+opfcomp*areaGxfc), sr, (targetDuration - pw_gxwa), targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfZ = scale*calcTargetAmp((areaGzcomb + opfcomp*areaGz1), sr, (targetDuration - pw_gzrf1d), targetAmpMin, targetAmpMax, 0.0,0.0,0);
        } else if (maxSlice)  {
            *ogsfZ = ogsfMax;
            sr = (fabs(a_gzcomba)/pw_gzcomba);
            scale = *ogsfZ/fabs(a_gzcomba);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = pw_gzcomb_tot + opfcomp*(pw_gz1a + pw_gz1 + pw_gz1d) + pw_gzrf1d;
            *ogsfY = scale*calcTargetAmp(areaGy1, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfX1 = scale*calcTargetAmp((areaGx1 + opfcomp*areaGxfc), sr, (targetDuration - pw_gxwa), targetAmpMin, targetAmpMax, 0.0,0.0,0);
        } else {
            *ogsfX1 = *ogsfXw = *ogsfY = *ogsfZ = 1.0;
        }
    }
    else if (method == POWER_METHOD)
    {
        float tmpPower;

        tmpPower = a_gxw*a_gxw*0.333333*pw_gxwa + a_gzrf1*a_gzrf1*0.333333*pw_gzrf1d;

        duraMax = IMax (3, duraRead, duraPhase, duraSlice);
        *ogsfX1 = 1.0;
        *ogsfY  = 1.0;
        *ogsfZ  = 1.0;

        if ( !(duraMax == duraRead) && (xTargetAmp > __FLT_EPSILON__) )
        {
            if (opfcomp)
            {
                *ogsfX1 = calcTargetAmp2(areaGx1, areaGxfc, slewRate, (duraMax - pw_gxwa), ogsfMin*xTargetAmp, ogsfMax*xTargetAmp)/xTargetAmp;
            }
            else
            {
                *ogsfX1 = calcTargetAmp(areaGx1, slewRate, (duraMax - pw_gxwa), ogsfMin*xTargetAmp, ogsfMax*xTargetAmp, 0.0,0.0,0)/xTargetAmp;
            }
        }

        if ( !(duraMax == duraPhase) && (yTargetAmp > __FLT_EPSILON__) )
        {
            *ogsfY = calcTargetAmp(areaGy1, slewRate, duraMax, ogsfMin*yTargetAmp, ogsfMax*yTargetAmp, 0.0,0.0,0)/yTargetAmp;
        }

        if ( !(duraMax == duraSlice) && (zTargetAmp > __FLT_EPSILON__) )
        {
            if (opfcomp)
            {
                *ogsfZ = calcTargetAmp2(areaGzcomb, areaGz1, slewRate, (duraMax - pw_gzrf1d), ogsfMin*zTargetAmp, ogsfMax*zTargetAmp)/zTargetAmp;
            }
            else
            {
                *ogsfZ = calcTargetAmp(areaGzcomb, slewRate, (duraMax - pw_gzrf1d), ogsfMin*zTargetAmp, ogsfMax*zTargetAmp, 0.0,0.0,0)/zTargetAmp;
            }
        }

        /* calculate Power for gx1,gxfc,gy1,gzcomb,gz1 */
        if (opfcomp)
        {
            *powerTE = (calcPower(areaGy1,slewRate,0,0.0,0.0,yTargetAmp*(*ogsfY)) +
                        calcPower(areaGx1,slewRate,0,0.0,0.0,xTargetAmp*(*ogsfX1)) + tmpPower +
                        calcPower(areaGxfc,slewRate,0,0.0,0.0,xTargetAmp*(*ogsfX1)) +
                        calcPower(areaGz1,slewRate,0,0.0,0.0,zTargetAmp*(*ogsfZ)) +
                        calcPower(areaGzcomb,slewRate,0,0.0,0.0,zTargetAmp*(*ogsfZ))) / duraMax;
        }
        else
        {
            *powerTE = (calcPower(areaGy1,slewRate,0,0.0,0.0,yTargetAmp*(*ogsfY)) +
                        calcPower(areaGx1,slewRate,0,0.0,0.0,xTargetAmp*(*ogsfX1)) + tmpPower +
                        calcPower(areaGzcomb,slewRate,0,0.0,0.0,zTargetAmp*(*ogsfZ))) / duraMax;
        }
    }

    if (method == LEGACY_METHOD)
    {
        areaMax = IMax (3, areaRead2, areaPhase2, areaSlice2);
        maxRead = (areaRead2 == areaMax);
        maxPhase = (areaPhase2 == areaMax);
        maxSlice = (areaSlice2 == areaMax);

        if (maxRead)  {
            *ogsfXwex = ogsfMax;
            sr = (fabs(a_gxwex)/pw_gxwexd);
            scale = *ogsfXwex/fabs(a_gxwex);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = pw_gxwexa + pw_gxwex + pw_gxwexd + (!gxwex_bridge)*(pw_gxwd);
            *ogsfYk = scale*calcTargetAmp(areaGy1r, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfZk = scale*calcTargetAmp(areaGzk, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
        } else if (maxPhase)  {
            *ogsfYk = ogsfMax;
            sr = (fabs(a_gy1ra)/pw_gy1ra);
            scale = *ogsfYk/fabs(a_gy1ra);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = pw_gy1r_tot;
            *ogsfXwex = scale*calcTargetAmp(areaGxwex, sr, (targetDuration-(!gxwex_bridge)*(pw_gxwd)), targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfZk = scale*calcTargetAmp(areaGzk, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
        } else if (maxSlice)  {
            *ogsfZk = ogsfMax;
            sr = (fabs(a_gzpa)/pw_gzpa);
            scale = *ogsfZk/fabs(a_gzpa);
            targetAmpMin = ogsfMin/scale;
            targetAmpMax = ogsfMax/scale;
            targetDuration = gzptime;
            *ogsfYk = scale*calcTargetAmp(areaGy1r, sr, targetDuration, targetAmpMin, targetAmpMax, 0.0,0.0,0);
            *ogsfXwex = scale*calcTargetAmp(areaGxwex, sr, (targetDuration-(!gxwex_bridge)*(pw_gxwd)), targetAmpMin, targetAmpMax, 0.0,0.0,0);
        } else {
            *ogsfXwex = *ogsfYk = *ogsfZk = 1.0;
        }
    }
    else if (method == POWER_METHOD)
    {
        float tmpPower;

        duraMax = IMax (3, duraRead2, duraPhase2, duraSlice2);
        *ogsfXwex = 1.0;
        *ogsfYk   = 1.0;
        *ogsfZk   = 1.0;

        if ( !(duraMax == duraRead2) && (xkTargetAmp > __FLT_EPSILON__) )
        {
            *ogsfXwex = calcTargetAmp(areaGxwex, slewRate, (duraMax-(!gxwex_bridge)*(pw_gxwd)), ogsfMin*xkTargetAmp, ogsfMax*xkTargetAmp, fabs(a_gxw),0.0,gxwex_bridge)/xkTargetAmp;
        }

        if ( !(duraMax == duraPhase2) && (ykTargetAmp > __FLT_EPSILON__) )
        {
            *ogsfYk = calcTargetAmp(areaGy1r, slewRate, duraMax, ogsfMin*ykTargetAmp, ogsfMax*ykTargetAmp, 0.0,0.0,0)/ykTargetAmp;
        }

        if ( !(duraMax == duraSlice2) && (zkTargetAmp > __FLT_EPSILON__))
        {
            *ogsfZk = calcTargetAmp(areaGzk, slewRate, duraMax, ogsfMin*zkTargetAmp, ogsfMax*zkTargetAmp, 0.0,0.0,0)/zkTargetAmp;
        }

        /* calculate Power for gxwex, gy1r, gzp */
        if (gxwex_bridge)
        {
            tmpPower = 0.0;
        }
        else
        {
            tmpPower = a_gxw*a_gxw*0.333333*pw_gxwa;
        }

        *powerTR = (calcPower(areaGy1r,slewRate,0,0.0,0.0,ykTargetAmp*(*ogsfYk)) +
                    calcPower(areaGxwex,slewRate,gxwex_bridge,fabs(a_gxw),0.0,xkTargetAmp*(*ogsfXwex)) + tmpPower +
                    calcPower(areaGzcomb,slewRate,0,0.0,0.0,zkTargetAmp*(*ogsfZk))) / duraMax;
    }

    /* SVBranch HCSDM00100058 Set ogsf* based on gradOpt_flag */
    if(gradOpt_flag)
    {
        if(!aTEopt_flag) 
        {
            *ogsfX1 = *ogsfXw = *ogsfY = *ogsfZ = 1.0;
        } 
        
        if(!aTRopt_flag) 
        {
            *ogsfXwex = *ogsfYk = *ogsfZk = 1.0;
        } 
    }
    else
    {
        if (!aTEopt_flag) {
            *ogsfX1 = *ogsfXw = *ogsfXwex = *ogsfY = *ogsfYk = *ogsfZ = *ogsfZk = 1.0;
        } else {
            if (!aTRopt_flag) {
                *ogsfZk = *ogsfZ;
                *ogsfXwex = *ogsfX1;
                *ogsfYk = *ogsfY;
            }
        }
    }

    return SUCCESS;
}   /* end setOptimizedGradientScalingFactor() */


/*  calcMedalMaxXresMinFov
 *
 *  Description:
 *    Calculate the maximum xres and the minimum FOV for MEDAL acquisitions 
 *    based on empirically determined relationships between FOV, RBW, and XRES 
 *    for a gradient configuration. For 1.5T, the curve is measured with the 
 *    parameters: slthickness=3mm,sllocs=48,opyres=256,pFOV=1.0. For 3.0T, 
 *    the curve is measured with the parameters: slthickness=3mm,sllocs=48,
 *    opyres=224,pFOV=1.0. The minimum FOV of 3T under normal mode is the FOV 
 *    which can meet the TE/TE2 limitation with the minimum Xres (128).
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (I) const float fov - Field of view (mm)
 *  (I) const float rbw - Receiver bandwidth (kHz, half bandwidth)
 *  (I) const int cfsrmode - slew rate capability (mT/m/ms)
 *  (I) const int cffield - field strength (mT)
 *  (I) const int cfgcoiltype - gradient coil type (enumeration)
 *  (I) const int axialBipoloarVibrantDeFlag - flag indicating if this is
 *        an Axial VIBRANT-DE acquistion using bipolar readout gradients
 *  (I) const int medalAutoTeFlag - flag indicating if TE will be
 *        automatically calculated
 *  (I) const int firstModeFlag _ flag indicating first dB/dt control mode
 *  (I) const int silent - ART
 *  (I) const int silentlevel - ART mode
 *  (O) int * maxXres - Maximum x resolution
 *  (O) float * minFOV - Minimum FOV
 *
 */

STATUS
calcMedalMaxXresMinFov( const float fov,
                        const float rbw,
                        const int cfsrmode,
                        const int cffield,
                        const int cfgcoiltype,
                        const int axialBipolarVibrantDeFlag,
                        const int medalAutoTeFlag,
                        const int firstModeFlag,
                        const int silent,             /* SVBranch GEHmr04241 Dual Echo support ART */
                        const int silentlevel,
                        int *maxXres,
                        float *minFOV )
{
    double C5, C4, C3, C2, C1, C0;

    if ( cfsrmode < PSD_SR200 )
    {
        /* SVBranch GEHmr04241 Dual Echo support ART */
        *minFOV = (float)FOV_MIN;
        /* MRIhc35599 - Enabling FOV-XRES curves for HDxt */
        if (cffield ==  B0_30000)
        {
            if (cfsrmode <= PSD_SR77)
            {
                if (rbw < 165.0)
                {
                    /* 143 kHz */
                    C3 = 6.25E-6;
                    C2 = -0.00830552;
                    C1 = 4.06441684;
                    C0 = -433.0575;
                }
                else if (rbw < 199.0)
                {
                    /* 167 kHz */
                    C3 = 3.46E-6;
                    C2 = -0.00583519;
                    C1 = 3.5810213;
                    C0 = -442.84715285;
                }
                else
                {
                    /* 200 & 250 kHz */
                    C3 = -6.061E-5;
                    C2 = 0.08090909;
                    C1 = -35.29134199;
                    C0 = 5333.29870130;
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else if (cfsrmode >= PSD_SR150)
            {
                if ( cfgcoiltype == PSD_TRM_COIL)
                {
                    if (rbw < 165.0)
                    {
                        /* 143 kHz */
                        C3 = 9.98E-6;
                        C2 = -0.01118016;
                        C1 = 4.25799951;
                        C0 = -233.24603188;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 8.07E-6;
                        C2 = -0.01027463;
                        C1 = 4.46159439;
                        C0 = -289.71980676;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = -7.02E-6;
                        C2 = 0.00441525;
                        C1 = 0.09569367;
                        C0 = 132.14384446;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = 6.75E-6;
                        C2 = -0.00949293;
                        C1 = 5.09402847;
                        C0 = -467.40855419;
                    }
                }
                else
                {
                    if ( rbw < 165.0 )
                    {
                        /* 143 kHz */
                        C3 = 7.82E-6;
                        C2 = -0.00901284;
                        C1 = 3.52354646;
                        C0 = -155.70703039;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 9.21E-6;
                        C2 = -0.01120297;
                        C1 = 4.64407505;
                        C0 = -295.58784282;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = 8.23E-6;
                        C2 = -0.01134063;
                        C1 = 5.34788329;
                        C0 = -434.64863484;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = -1.109E-5;
                        C2 = 0.01012568;
                        C1 = -2.04777385;
                        C0 = 394.10526316;
                    }
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else
            {
                *maxXres = 512;
            }
        }
        else if (cffield == B0_15000)
        {
            /* YMSmr11373 - Enabling FOV-XRES curves for HDe2 */
            if (cfsrmode <= PSD_SR50)
            {
                if (rbw < 82.0)
                {
                    /* 62.5 kHz */
                    C3=4.5E-6;
                    C2=-0.005542313;
                    C1=2.341416765;
                    C0=-21.599422606;
                }
                else if (rbw < 99.0)
                {
                    /* 83.3 & 90.9 kHz */
                    C3=4.273E-6;
                    C2=-0.005944335;
                    C1=2.927946604;
                    C0=-89.641141672;
                }
                else if (rbw < 124.0)
                {
                    /* 100 & 111 kHz */
                    C3=7.98E-6;
                    C2=-0.010103897;
                    C1=4.629226091;
                    C0=-287.759151192;
                }
                else
                {
                    /* 125 kHz */
                    C3=1.3252E-5;
                    C2=-0.017275253;
                    C1=8.024706826;
                    C0=-769.123242891;
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else if (cfsrmode == PSD_SR77)
            {
                if (rbw < 82.0)
                {
                    /* 62.5 kHz */
                    C3 = 4.195E-6;
                    C2 = -0.004704995;
                    C1 = 1.815355766;
                    C0 = 87.752707839;
                }
                else if (rbw < 99.0)
                {
                    /* 83.3 & 90.9 kHz */
                    C3 = 5.248E-6;
                    C2 = -0.00639543;
                    C1 = 2.709562789;
                    C0 = 30.418040247;
                }
                else if (rbw < 124.0)
                {
                    /* 100 & 111 kHz */
                    C3 = 6.225E-6;
                    C2 = -0.008094923;
                    C1 = 3.666891237;
                    C0 = -70.335269822;
                }
                else
                {
                    /* 125 kHz */
                    C3 = 1.074E-6;
                    C2 = -0.003314989;
                    C1 = 2.548652073;
                    C0 = 41.135299483;
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else if (cfsrmode == PSD_SR100)
            {
                /* SVBranch GEHmr04241 Dual Echo support ART */
                if (silent)
                {
                    /* ART moderate mode: SR50 */
                    if (silentlevel == SILENT_HIGH)
                    {
                        if (rbw < 82.0)
                        {
                            /* 62.5 kHz */
                            C3 = 0.000004108;
                            C2 = -0.005043592;
                            C1 = 2.137453929;
                            C0 = 6.757092376;
                        }
                        else if (rbw < 99.0)
                        {
                            /* 83.3 & 90.9 kHz */
                            C3 = 0.000007942;
                            C2 = -0.009311719;
                            C1 = 3.861766351;
                            C0 = -160.306879158;
                        }
                        else if (rbw < 124.0)
                        {
                            /* 100 & 111 kHz */
                            C3 = 0.000009825;
                            C2 = -0.011659388;
                            C1 = 4.954846344;
                            C0 = -286.144908752;
                        }
                        else
                        {
                            /* 125 kHz */
                            C3 = 0.000011798;
                            C2 = -0.014880913;
                            C1 = 6.736978897;
                            C0 = -537.763904338;
                        }
                        *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                    } /* end of ART moderate mode */
                    /* ART HIGH mode: SR 16.5 */
                    else if (silentlevel == SILENT_LOW)
                    {
                        if (rbw < 82.0)
                        {
                            /* 62.5 kHz */
                            C3 = 0.000007104;
                            C2 = -0.009293782;
                            C1 = 4.518740855;
                            C0 = -483.532920719;
                            *minFOV = 230.0;
                        }
                        else if (rbw < 99.0)
                        {
                            /* 83.3 & 90.9 kHz */
                            C3 = 0.000015360;
                            C2 = -0.020696009;
                            C1 = 9.999340743;
                            C0 = -1365.991351915;
                            *minFOV = 280.0;
                        }
                        else if (rbw < 124.0)
                        {
                            /* 100 & 111 kHz */
                            C3 = 0.000008256;
                            C2 = -0.014770382;
                            C1 = 9.180211558;
                            C0 = -1551.296181662;
                            *minFOV = 320.0;
                        }
                        else
                        {
                            /* 125 kHz */
                            C3 = 0.000022533;
                            C2 = -0.033006993;
                            C1 = 17.761383058;
                            C0 = -3082.904429317;
                            *minFOV = 380.0;
                        }

                        *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                    } /* end of ART high mode */
                    else
                    {
                        *maxXres = 512;
                    }
                } /* end of silent mode */
                else
                {
                    if (rbw < 82.0)
                    {
                        /* 62.5 kHz */
                        C3 = 5.526E-6;
                        C2 = -0.005720843;
                        C1 = 1.981757605;
                        C0 = 103.783720266;
                    }
                    else if (rbw < 99.0)
                    {
                        /* 83.3 & 90.9 kHz */
                        C3 = 6.990E-6;
                        C2 = -0.007664404;
                        C1 = 2.860351324;
                        C0 = 72.736147265;
                    }
                    else if (rbw < 124.0)
                    {
                        /* 100 & 111 kHz */
                        C3 = 7.328E-6;
                        C2 = -0.008599081;
                        C1 = 3.471464356;
                        C0 = 35.797192397;
                    }
                    else
                    {
                        /* 125 kHz */
                        C3 = 7.874E-6;
                        C2 = -0.010189746;
                        C1 = 4.568136214;
                        C0 = -69.329330569;
                    }
                    *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                }
            }
            else if (cfsrmode == PSD_SR120)
            {
                if (cfgcoiltype == PSD_XRMW_COIL)
                {
                    if (firstModeFlag)
                    {
                        /* XRMBw, TE 2.7ms, TE2 5.3ms */
                        if (rbw < 40.0)
                        {
                            /* 31.25kHZ multi-TR mode */
                            C5 = 3.391E-11;
                            C4 = -5.54E-8;
                            C3 = 3.734E-5;
                            C2 = -1.356E-2;
                            C1 = 2.788;
                            C0 = -4.217;
                        }
                        else if (rbw < 49.0)
                        {
                            /* 41.0kHZ multi-TR mode */
                            C5 = 4.33E-11;
                            C4 = -7.848E-8;
                            C3 = 5.73E-5;
                            C2 = -2.143E-2;
                            C1 = 4.327;
                            C0 = -66.64;
                        }
                        else if (rbw < 61.0)
                        {
                        /* 50.0kHZ multi-TR mode */
                            C5 = 5.368E-11;
                            C4 = -9.749E-8;
                            C3 = 7.113E-5;
                            C2 = -2.663E-2;
                            C1 = 5.435;
                            C0 = -126.6;
                        }
                        else if (rbw < 82.0)
                        {
                            /* 62.5kHZ bipolar fit*/
                            C5 = 1.096E-10;
                            C4 = -1.927E-7;
                            C3 = 1.335E-4;
                            C2 = -4.575E-2;
                            C1 = 7.892;
                            C0 = -221.4;
                        }
                        else if (rbw < 89.0)
                        {
                        /* 83.33kHZ bipolar fit*/
                            C5 = 7.065E-11;
                            C4 = -1.42E-7;
                            C3 = 1.14E-4;
                            C2 = -4.6E-2;
                            C1 = 9.469;
                            C0 = -363.5;
                        }
                        else if (rbw < 99.0)
                        {
                            /* 90.91kHZ bipolar fit*/
                            C5 = 1.4565E-10;
                            C4 = -2.624E-7;
                            C3 = 1.899E-4;
                            C2 = -6.959E-2;
                            C1 = 13.18;
                            C0 = -579;
                        }
                        else if (rbw < 110.0)
                        {
                            /* 100.0kHZ bipolar fit*/
                            C5 = 2.884E-11;
                            C4 = -7.819E-8;
                            C3 = 7.968E-5;
                            C2 = -3.92E-2;
                            C1 = 9.593;
                            C0 = -429.7;
                        }
                        else if (rbw < 124.0)
                        {
                            /* 111.11kHz bipolar fit*/
                            C5 = 3.663E-12;
                            C4 = -2.145E-8;
                            C3 = 3.441E-5;
                            C2 = -2.353E-2;
                            C1 = 7.494;
                            C0 = -339;
                        }
                        else
                        {
                            /* 125.0kHz bipolar fit*/
                            C5 = -3.328E-10;
                            C4 = 5.74E-7;
                            C3 = -3.772E-4;
                            C2 = 1.143E-1;
                            C1 = -14.47;
                            C0 = 1003;
                        }
                    }    
                    else 
                    {
                        /* XRMBw, TE 2.7ms, TE2 5.3ms */
                        if (rbw < 40.0)
                        {
                            /* 31.25kHZ multi-TR mode */
                            C5 = -8.342E-11;
                            C4 = 1.095E-7;
                            C3 = -4.831E-5;
                            C2 = 6.727E-3;
                            C1 = 6.323E-1;
                            C0 = 51.53;
                        }
                        else if (rbw < 49.0)
                        {
                            /* 41.0kHZ multi-TR mode */
                            C5 = 9.858E-11;
                            C4 = -1.622E-7;
                            C3 = 1.048E-4;
                            C2 = -3.417E-2;
                            C1 = 6.006;
                            C0 = -175.4;
                        }
                        else if (rbw < 61.0)
                        {
                        /* 50.0kHZ multi-TR mode */
                            C5 = 6.78E-11;
                            C4 = -1.154E-7;
                            C3 = 7.928E-5;
                            C2 = -2.839E-2;
                            C1 = 5.699;
                            C0 = -172.7;
                        }
                        else if (rbw < 82.0)
                        {
                            /* 62.5kHZ bipolar fit*/
                            C5 = 5.402E-11;
                            C4 = -1.061E-7;
                            C3 = 8.377E-5;
                            C2 = -3.333E-2;
                            C1 = 6.78;
                            C0 = -236.6;
                        }
                        else if (rbw < 89.0)
                        {
                        /* 83.33kHZ bipolar fit*/
                            C5 = 1.139E-10;
                            C4 = -2.007E-7;
                            C3 = 1.44E-4;
                            C2 = -5.373E-2;
                            C1 = 10.77;
                            C0 = -508.6;
                        }
                        else if (rbw < 99.0)
                        {
                            /* 90.91kHZ bipolar fit*/
                            C5 = 1.771E-10;
                            C4 = -2.985E-7;
                            C3 = 2.025E-4;
                            C2 = -7.104E-2;
                            C1 = 13.48;
                            C0 = -678.2;
                        }
                        else if (rbw < 110.0)
                        {
                            /* 100.0kHZ bipolar fit*/
                            C5 = 2.644E-10;
                            C4 = -4.511E-7;
                            C3 = 3.059E-4;
                            C2 = -1.053E-1;
                            C1 = 19.22;
                            C0 = -1051;
                        }
                        else if (rbw < 124.0)
                        {
                            /* 111.11kHz bipolar fit*/
                            C5 = 3.374E-10;
                            C4 = -5.909E-7;
                            C3 = 4.092E-4;
                            C2 = -1.424E-1;
                            C1 = 25.9;
                            C0 = -1517;
                        }
                        else
                        {
                            /* 125.0kHz bipolar fit*/
                            C5 = 3.336E-10;
                            C4 = -6.172E-7;
                            C3 =  4.521E-4;
                            C2 = -1.664E-1;
                            C1 = 31.9;
                            C0 = -2059;
                        }
                    }
                    
                     *maxXres = C5*fov*fov*fov*fov*fov + C4*fov*fov*fov*fov + 
                                   C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                }
                else
                {
                    if (rbw < 82.0)
                    {
                        /* 62.5 kHz */
                        C3 = 4.786E-6;
                        C2 = -0.004952348;
                        C1 = 1.7282292979;
                        C0 = 134.49612677;
                    }
                    else if (rbw < 99.0)
                    {
                        /* 83.3 & 90.9 kHz */
                        C3 = 6.393E-6;
                        C2 = -0.006910716;
                        C1 = 2.55231274;
                        C0 = 118.97422442;
                    }
                    else if (rbw < 124.0)
                    {
                        /* 100 & 111 kHz */
                        C3 = 6.824E-6;
                        C2 = -0.007754601;
                        C1 = 3.047530084;
                        C0 = 108.513166953;
                    }
                    else
                    {
                        /* 125 kHz */
                        C3 = 1.0553E-5;
                        C2 = -0.012450495;
                        C1 = 5.064544904;
                        C0 = -71.31251896;
                    }
                    *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                }
            }
            else if (cfsrmode >= PSD_SR150)
            {
                if( cfgcoiltype == PSD_TRM_COIL)
                {
                    if (rbw < 82.0)
                    {
                        /* 62.5 kHz */
                        C3 = 3.831E-6;
                        C2 = -0.0037676;
                        C1 = 1.277004065;
                        C0 = 192.594325486;
                    }
                    else if (rbw < 99.0)
                    {
                        /* 83.3 & 90.9 kHz */
                        C3 = 5.96E-6;
                        C2 = -0.005981465;
                        C1 = 2.077849303;
                        C0 = 196.446487443;
                    }
                    else if (rbw < 124.0)
                    {
                        /* 100 & 111 kHz */
                        C3 = 8.083E-6;
                        C2 = -0.008233042;
                        C1 = 2.906134;
                        C0 = 171.162066586;
                    }
                    else
                    {
                        /* 125 kHz */
                        C3 = 1.1493E-5;
                        C2 = -0.0121234;
                        C1 = 4.432619185;
                        C0 = 83.331376962;
                    }
                }
                else
                {
                    if (rbw < 82.0)
                    {
                        /* 62.5 kHz */
                        C3 = 3.131E-6;
                        C2 = -0.00327955;
                        C1 = 1.176116536;
                        C0 = 199.625703252;
                    }
                    else if (rbw < 99.0)
                    {
                        /* 83.3, 90.9 kHz */
                        C3 = 4.696E-6;
                        C2 = -0.005067656;
                        C1 = 1.882034207;
                        C0 = 209.575300293;
                    }
                    else if (rbw < 124.0)
                    {
                        /* 100 & 111 kHz */
                        C3 = 6.16E-6;
                        C2 = -0.006755727;
                        C1 = 2.56144506;
                        C0 = 196.246785485;
                    }
                    else
                    {
                        /* 125 kHz */
                        C3 = 8.531E-6;
                        C2 = -0.009685147;
                        C1 = 3.808895124;
                        C0 = 133.78370608;
                    }
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else
            {
                *maxXres = 512;
            }
        }
        else
        {
            *maxXres = 512;
        }
    }
    else if ( PSD_SR200 == cfsrmode )
    {
        if (firstModeFlag)
        {
            /* First dB/dt Control Mode */
            if ( B0_30000 == cffield )
            {
                if (axialBipolarVibrantDeFlag)
                {
                    /* XRMB, TE 1.3ms, TE2 2.5ms MRIhc38426 */
                    /* only for axial bipolar acquisition of vibrantDE */
                    if (rbw < 165.0)
                    {
                        /* 31.3, 62.5, 83.3, 90.9, 100, 111, 125, 143 kHz */
                        C3 = 1.673E-5;
                        C2 = -0.01992343;
                        C1 = 7.96552641;
                        C0 = -787.80854701;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 1.338E-5;
                        C2 = -0.0177347;
                        C1 = 7.95650212;
                        C0 = -879.41638682;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = -1.187E-5;
                        C2 = 0.01027348;
                        C1 = -1.83684211;
                        C0 = 210.16718266;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = -3.225E-5;
                        C2 = 0.04155012;
                        C1 = -16.83395493;
                        C0 = 2513.90955711;
                    }
                }
                else
                {
                    /* XRMB, TE 1.5ms, TE2 2.8ms MRIhc38426 */
                    if (rbw < 165.0)
                    {
                        /* 31.3, 62.5, 83.3, 90.9, 100, 111, 125, 143 kHz */
                        C3 = 1.19453E-5;
                        C2 = -0.0147155;
                        C1 = 6.13595;
                        C0 = -530.707;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 7.9624E-6;
                        C2 = -0.011644;
                        C1 = 5.7544;
                        C0 = -568.909;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = 3.78615E-6;
                        C2 = -0.00793248;
                        C1 = 5.15499;
                        C0 = -609.765;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = 1.20519E-5;
                        C2 = -0.0172484;
                        C1 = 9.28237;
                        C0 = -1284.58;
                    }
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else if ( B0_15000 == cffield )
            {
                /* XRMB, TE 2.7ms, TE2 5.3ms MRIhc39347 */
                if (rbw < 82.0)
                {
                    /* 62.5kHZ */
                    C5 = 1.7959E-10;
                    C4 = -2.97477E-7;
                    C3 = 1.91741E-4;
                    C2 = -6.01567E-2;
                    C1 = 9.28271;
                    C0 = -2.3608E+2;
                }
                else if (rbw < 89.0)
                {
                    /* 83.33kHZ */
                    C5 = 7.3415E-11;
                    C4 = -1.52635E-7;
                    C3 = 1.23659E-4;
                    C2 = -4.88886E-2;
                    C1 = 9.54582;
                    C0 = -3.02519E+2;
                }
                else if (rbw < 99.0)
                {
                    /* 90.91kHZ */
                    C5 = 8.6213E-11;
                    C4 = -1.69915E-7;
                    C3 = 1.33644E-4;
                    C2 = -5.24984E-2;
                    C1 = 1.04053E+1;
                    C0 = -3.59332E+2;
                }
                else if (rbw < 110.0)
                {
                    /* 100.0kHZ */
                    C5 = 8.86561E-12;
                    C4 = -5.3644E-8;
                    C3 = 6.94647E-5;
                    C2 = -3.71759E-2;
                    C1 = 9.13126;
                    C0 = -3.34088E+2;
                }
                else if (rbw < 124.0)
                {
                    /* 111.11kHz */
                    C5 = 9.49128E-12;
                    C4 = -3.94572E-8;
                    C3 = 5.27872E-5;
                    C2 = -3.12642E-2;
                    C1 = 8.64578;
                    C0 = -3.33633E+2;
                }
                else
                {
                    /* 125.0kHz */
                    C5 = 2.05469E-10;
                    C4 = -3.16426E-7;
                    C3 = 2.00663E-4;
                    C2 = -6.9051E-2;
                    C1 = 1.3622E+1;
                    C0 = -5.9041E+2;
                }

                *maxXres = C5*fov*fov*fov*fov*fov + C4*fov*fov*fov*fov + C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }

            *minFOV = (float)FOV_MIN;

        } 
        else 
        {
            /* Normal dB/dt Mode */
            if ( B0_30000 == cffield )
            {
                if (axialBipolarVibrantDeFlag)
                {
                    /* XRMB, TE 1.3ms, TE2 2.5ms MRIhc38426 */
                    /* only for axial bipolar acquisition of vibrantDE */
                    if (rbw < 165.0)
                    {
                        /* 31.3, 62.5, 83.3, 90.9, 100, 111, 125, 143 kHz */
                        C3 = 1.62607E-5;
                        C2 = -2.10354E-2;
                        C1 = 9.1822;
                        C0 = -1.08112E+3;
                        *minFOV = 240.0;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 1.49792E-5;
                        C2 = -2.08121E-2;
                        C1 = 9.88879;
                        C0 = -1.29365E+3;
                        *minFOV = 260.0;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = -4.80508E-6;
                        C2 = 2.06616E-3;
                        C1 = 1.75727;
                        C0 = -4.36015E+2;
                        *minFOV = 290.0;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = 1.08932E-6;
                        C2 = -3.52798E-3;
                        C1 = 3.86995;
                        C0 = -8.23555E+2;
                        *minFOV = 340.0;
                    }
                }
                else
                {
                    /* XRMB, TE 1.5ms, TE2 2.8ms MRIhc38426 */
                    if (rbw < 165.0)
                    {
                        /* 31.3, 62.5, 83.3, 90.9, 100, 111, 125, 143 kHz */
                        C3 = 8.39014E-6;
                        C2 = -1.17085E-2;
                        C1 = 5.59286;
                        C0 = -5.91226E+2;
                        *minFOV = 200.0;
                    }
                    else if (rbw < 198.0)
                    {
                        /* 167 kHz */
                        C3 = 3.70043E-6;
                        C2 = -7.29718E-3;
                        C1 = 4.61181;
                        C0 = -5.74484E+2;
                        *minFOV = 220.0;
                    }
                    else if (rbw < 248.0)
                    {
                        /* 200 kHz */
                        C3 = -1.15987E-6;
                        C2 = -2.19939E-3;
                        C1 = 3.31128;
                        C0 = -5.49411E+2;
                        *minFOV = 250.0;
                    }
                    else
                    {
                        /* 250 kHz */
                        C3 = 2.56434E-6;
                        C2 = -6.35278E-3;
                        C1 = 5.39863;
                        C0 = -9.96002E+2;
                        *minFOV = 300.0;
                    }
                }

                *maxXres = C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;

            }
            else if ( B0_15000 == cffield )
            {
                /* XRMB, TE 2.7ms, TE2 5.3ms MRIhc39347 */
                if (rbw < 82.0)
                {
                    /* 62.5kHZ */
                    C4 = -3.81699E-8;
                    C3 = 5.23823E-5;
                    C2 = -2.65831E-2;
                    C1 = 5.99389;
                    C0 = -1.75384E+2;
                }
                else if (rbw < 89.0)
                {
                    /* 83.33kHZ */
                    C4 = -4.12757E-8;
                    C3 = 6.00987E-5;
                    C2 = -3.28422E-2;
                    C1 = 8.1375;
                    C0 = -3.39952E+2;
                }
                else if (rbw < 99.0)
                {
                    /* 90.91kHZ */
                    C4 = -3.43211E-8;
                    C3 = 5.29144E-5;
                    C2 = -3.07527E-2;
                    C1 = 8.14341;
                    C0 = -3.58867E+2;
                }
                else if (rbw < 110.0)
                {
                    /* 100.0kHZ */
                    C4 = -4.00688E-8;
                    C3 = 5.98939E-5;
                    C2 = -3.43095E-2;
                    C1 = 9.13833;
                    C0 = -4.43013E+2;
                }
                else if (rbw < 124.0)
                {
                    /* 111.11kHz */
                    C4 = -4.13325E-8;
                    C3 = 6.29777E-5;
                    C2 = -3.70439E-2;
                    C1 = 1.0218E+1;
                    C0 = -5.5128E+2;
                }
                else
                {
                    /* 125.0kHz */
                    C4 = -6.44057E-8;
                    C3 = 9.55591E-5;
                    C2 = -5.4139E-2;
                    C1 = 1.42871E+1;
                    C0 = -8.8142E+2;
                }

                *maxXres = C4*fov*fov*fov*fov + C3*fov*fov*fov + C2*fov*fov + C1*fov + C0;
                *minFOV = (float)FOV_MIN;
            }
        }
    }

    if (medalAutoTeFlag)
    {
        /* Automatically handled in AutoTE code */
        *maxXres = 1024;
        *minFOV = (float)FOV_MIN;
    }

    return SUCCESS;
}

/*  isRefRegionValid
 *
 *  Description:
 *  Check if all reference lines in the rectangular region defined by y_lower,y_upper,
 *  z_lower and z_upper are within cal region (when ARC is on) or partial ky/kz/kr
 *  region (when ARC is off).
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *  (O) TRUE if all lines in the rectangular region are sampled, FALSE otherwise
 *  (I) const int y_lower - Y lower bound of rectangular region
 *  (I) const int y_upper - Y upper bound of rectangular region
 *  (I) const int z_lower - Z lower bound of rectangular region
 *  (I) const int z_upper - Z upper bound of rectangular region
 *  (I) const int zy_views - Number of views (fully sampled for ARC)
 *  (I) const int zy_slices - Number of slices (fully sampled for ARC)
 *  (I) const float fn - Fractional NEX (pfky)
 *  (I) const int pfky_total_unaccel - Fractional NEX min view number to skip
 *  (I) const int pfkz_fraction - Partial kz
 *  (I) const int pfkz_total_unaccel - Partial kz min slice number to skip
 *  (I) const float pfkr_fraction - Fraction of encodes to keep
 *  (I) const float yFov - FOV in phase direction in mm (opfov*nop*opphasefov)
 *  (I) const float zFov - FOV in slice direction in mm (ethick)
 *  (I) const int phaseres - Number of phases (unaccelerated for ARC)
 *  (I) const int equant - Number of slices (unaccelerated for ARC)
 *  (I) const int arc_flag - Set if ARC is enabled
 *  (I) const CAL_PARAM calRegion - Structure containing the calibration
 *        region related info such as shape, borders, center location, etc.
 *
 */
STATUS
isRefRegionValid(const int y_lower,
                 const int y_upper,
                 const int z_lower,
                 const int z_upper,
                 const int zy_views,
                 const int zy_slices,
                 const float fn,
                 const int pfky_total_unaccel,
                 const float pfkz_fraction,
                 const int pfkz_total_unaccel,
                 const float pfkr_fraction,
                 const float yFov,
                 const float zFov,
                 const int phaseres,
                 const int equant,
                 const int arc_flag,
                 const CAL_PARAM calRegion)
{
    float sq_normdist_ky = 0.0;
    int view = 0;
    int slice = 0;
    float dist_ky = 0.0;
    float dist_kz = 0.0;
    int cal_data = 0;
    int pfky_flag = (fn < 1.0);
    int pfkz_flag = (pfkz_fraction < 1.0);
    int pfkr_flag = (pfkr_fraction < 1.0);
    int pfkrIN = 1;
    int pfkyIN = 1;
    int pfkzIN = 1;

    /* pfkr parameters */
    float delta_ky = 1.0/yFov;  /* inverse mm */
    float delta_kz = 1.0/zFov;  /* inverse mm also */
    float origin_y = (float)(phaseres-1)/2.0 - 0.01;
    float origin_z = (float)(equant-1)/2.0 - 0.01;
    float kr_fraction = sqrt(pfkr_fraction*4.0/PI);
    float max_dist_ky = 0.505*kr_fraction*delta_ky*(float)(phaseres-1);
    float max_dist_kz = 0.505*kr_fraction*delta_kz*(float)(equant-1);
    float sq_max_dist_ky = max_dist_ky * max_dist_ky;
    float sq_max_dist_kz = max_dist_kz * max_dist_kz;

    for (view = y_lower; view <= y_upper; view++)
    {
        if (pfkr_flag)
        {
            dist_ky = delta_ky * ((float)(view) - origin_y);
            sq_normdist_ky = dist_ky*dist_ky / sq_max_dist_ky;
        }

        for (slice = z_lower; slice <= z_upper; slice++)
        {
            if (pfkr_flag)
            {
                dist_kz = delta_kz*((float)(slice) - origin_z);
                pfkrIN = ((sq_normdist_ky + (dist_kz*dist_kz) / sq_max_dist_kz) <= 1.0);
            }
            else
            {
                pfkrIN = 1;
            }

            pfkzIN = (pfkz_flag) ? (slice < pfkz_total_unaccel) : 1;
            pfkyIN = (pfky_flag) ? (view < pfky_total_unaccel) : 1;

            if (!(pfkrIN && pfkyIN && pfkzIN))
            {
                return FALSE;
            }

            if (arc_flag)
            {
                cal_data = calibration_voxel(view, slice, calRegion);
                if (!cal_data)
                {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

#endif /* HOST_TGT */

/* ------------------------ Target only functions ------------------------ */
#ifdef MGD_TGT

/* Target side only local includes */
#include "tricks_common.h"

/*
 * Temporary array for buffered conversion of TRICK ZY order table.
 * Use this buffer instead of a malloc'ed buffer to avoid memory 
 * fragmentation on VxWorks.
 *
 * Based on performance testing of epic_loadcvs(), values >= 1 kB had
 * similar performance.  Selected 16 kB to be conservative.
 */
static TRICKS_ZY_ORDER reconZyOrder[16384/sizeof(TRICKS_ZY_ORDER)];

/**
 * writes files for communicate region and view ordering for recon
 *
 * @param[in] regionSchedule - schedule of tricks regions that will be played out
 * @param[in] regionScheduleLength - total number of regions that will be acquired.
 * @param[in] maskRegions - number of mask regions that will be acquired
 * @param[in] zyExport - view-slice order for each region
 * @param[in] zyExportLength - number of elements in zyExport
 * @return status of function (SUCCESS or FAILURE)
 */
STATUS
tricksWriteReconFiles( const int * regionSchedule,
                       const int regionScheduleLength,
                       const int maskRegions,
                       const ZY_EXPORT * zyExport,
                       const int zyExportLength)
{
    int n = 0;
    int filled = 0;
    FILE *fp = NULL;
    const char * funcName = "trickWriteReconFiles";
#ifndef SIM
    const char * scheduleFile = "./ec-tricks-schedule";
    const char * reconZyOrderFile = "./Sorted_arr_ZYSORT";
#else
    const char * scheduleFile = "/usr/g/bin/ec-tricks-schedule";
    const char * reconZyOrderFile = "/usr/g/bin/Sorted_arr_ZYSORT";
#endif

    /* 
     * Use a statically allocated buffer for writing on the AGP side
     * to avoid malloc memory fragmentation
     */
    int bufferSize = sizeof(reconZyOrder) / sizeof(reconZyOrder[0]);
    memset(reconZyOrder, 0, sizeof(reconZyOrder));

    /* Write trick region schedule */
    fp = fopen(scheduleFile, "w");
    if( NULL == fp )
    {
        printf("%s: open file %s for reading failed!\n", funcName, scheduleFile);
        return FAILURE;
    }
    fprintf(fp, "%d\n", maskRegions);
    fprintf(fp, "%d\n", regionScheduleLength);
    for( n = 0; n < regionScheduleLength; ++n )
    {
        fprintf(fp, "%d\n", regionSchedule[n] );
    }
    fclose(fp);
    fp = NULL;

    /* 
     * Write encode order to file for Tricks recon to sort data.
     * Copy necessary data into a TRICKS_ZY_ORDER and write to disk.
     */
    fp = fopen(reconZyOrderFile, "wb");
    if( NULL == fp )
    {
        printf("%s: open file %s for reading failed!\n", funcName, reconZyOrderFile);
        return FAILURE;
    }

    filled = 0;
    for( n = 0; n < zyExportLength; ++n )
    {
        reconZyOrder[filled].view = zyExport[n].view;
        reconZyOrder[filled].slice = zyExport[n].slice;
        ++filled;

        if( filled >= bufferSize || ((n + 1) >= zyExportLength) )
        {
            /* Buffer is full or we are done.  Write to disk */
            int written = fwrite(reconZyOrder, sizeof(TRICKS_ZY_ORDER), filled, fp);
            if( written != filled )
            {
                printf("%s: only able to write %d of %d entries to %s!\n", funcName, 
                       n - filled + written, zyExportLength, scheduleFile);
                fclose(fp);
                return FAILURE;
            }
            filled = 0;
        }
    }
    fclose(fp);

    return SUCCESS;
}

/*  arcGetDabEncode
 *
 *  Description:
 *    Get the DAB phase or slice number for the specified fully-sampled
 *    view or slice encode accounting for BAM packing, if enabled.
 *
 *  Parameters:
 *  (I: for input parameters, O: for output parameters)
 *
 *  (O) INT return variable - Actual phase/slice encode
 *  (I) const INT dabEncode - phase/slice encode sent with DAB packet (zero based)
 *  (I) const INT packBamFlag - True if phase/slice BAM packing is used
 *  (I) const INT *remapTable - remapping table for phase/slice (zero based)
 *
 *   NOTE: remapTable is only used if packBamFlag is true
 */
INT
arcGetDabEncode(const INT encode, const INT packBamFlag, const INT *remapTable)
{
    INT dabEncode = encode;

    if (packBamFlag)
    {
        dabEncode = remapTable[encode];
    }

    return dabEncode;
}

#endif /* MGD_TGT */

