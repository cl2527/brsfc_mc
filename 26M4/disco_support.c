/*
 * Copyright (c) 2014 by General Electric Company. All Rights Reserved.
 */

/**
 * \file disco_support.c
 *
 * This is the source file for DISCO support routines.
 *
 * @author Dan Rettmann/Kang Wang/Ty Cashen
 * @since 25.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 24 Feb 2014 DWR/KW/TAC
 * HCSDM00264720 Initial version.
 */

#ifdef HOST_TGT
#include "support_decl.h"
#include "efgre3d_support.h"

#else /* for offline */
#include <stdlib.h>
#include <stdio.h>

typedef int STATUS;
#define FAILURE 0
#define SUCCESS 1

#define MAX_NUM_REGIONS 256

#endif /* HOST_TGT */

#include "disco_support.h"

/**
 * writeVsc3DConfig
 *
 * Write view-sharing control file for reconstruction
 *
 *  @param[in]  int num_regions - number of regions in a view-shared phase.
 *  @param[in]  int num_mask_regions - number of regions in mask phase.
 *  @param[in]  int total_acq_regions - total number of regions acquired in the entire schedule.
 *  @param[in]  int* views_per_region - views per region.
 *  @param[in]  int* region_schedule - region schedule that will be played out during acquisition.
 *  @param[out] int* phase_done_schedule - region index for phase done packet.
 *  @param[in]  int num_phases - total number of phases.
 *  @param[in]  int mask_phase_flag - indicates if there is a mask phase as part of num_phases.
 *  @param[in]  int acq_outerregion_first_flag - indicates if outer region is acquired first to start a phase.
 *  @param[in]  int reverse_first_region_flag - indicates if the view-order for the first region is reversed.
 *  @param[in]  int combo_mode - view-sharing direction: backward, forward or nearest neighbor.
 *  @param[in]  int peakPhaseIndex - the phase index for the first non-view-shared phase after view-sharing portion. 1-based.
 *  @param[in]  int kacq_uid - kacq_uid that will be used as part of the name of the file to be written.
 *  @return status of function (SUCCESS or FAILURE)
 */
STATUS writeVsc3DConfig( int num_regions, int num_mask_regions, int total_acq_regions,
                         int *views_per_region, int *region_schedule,
                         int *phase_done_schedule, 
                         int num_phases, int mask_phase_flag, int acq_outerregion_first_flag, int reverse_first_region_flag, int combo_mode, const int peakPhaseIndex, const int kacq_uid)
{
    int i = 0, j = 0, j0 = 1; /* j0 is the index for the first dynamic phase */
    int cur_pos = 0, cur_a = 0;
    int indices[256];
    int region_type = 0; /* 0=A, 1=B1, 2=B2, 3=B3; 4=revEC-B1 when reverse_first_region_flag ON */
    int num = 0, next_a = 0;
    int max_region_index = 0;
    int dist;
    int last_vs_phase_index = 0;
    int num_vs_phases = 0;
    int i_left_limit = 0; /* backward limit for view-sharing */
    int i_right_limit = 0; /* forward limit for view-sharing */
    int num_regions_created = num_mask_regions + (1 == reverse_first_region_flag); /* the last region is reverseEC B1 */

    FILE *fp = NULL;
    char vsc_filename[BUFSIZ] = "vsc3d.cfg";
    char filestring[BUFSIZ];
#ifndef SIM
    char  psddata_path[BUFSIZ] = "/usr/g/psddata/";
#else
    char  psddata_path[BUFSIZ] = "./";
#endif
  
#ifdef HOST_TGT
    /* Write vsc3d.cfg with a unique id to ensure recon is reading right one */
    sprintf(filestring, "%s%s.%d", psddata_path, vsc_filename, kacq_uid);
    if (NULL == (fp = fopen(filestring, "w")))
    {
        epic_error( use_ermes, "Unable to open the file %s",
                    EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                    STRING_ARG, filestring );
        return FAILURE;
    }
#else
    sprintf(filestring, "%s%s", psddata_path, vsc_filename);
    if (NULL == (fp = fopen(filestring, "w")))
    {
        printf("Unable to open the file %s", filestring);
        return FAILURE;
    }
#endif /* HOST_TGT */
    
    if (0 == peakPhaseIndex) /* view-share all phases */
    {
        last_vs_phase_index = num_phases;
    }
    else if (peakPhaseIndex > 0)
    {
        last_vs_phase_index = peakPhaseIndex - 1;
    }
    else
    {
        printf("peakPhaseIndex = %d, and it is less than zero\n", peakPhaseIndex);
        return FAILURE;
    }
    num_vs_phases = last_vs_phase_index - mask_phase_flag;

    fprintf(fp, "GE_VSC 200\n");
    fprintf(fp, "num_regions %d\n", num_regions_created);
    fprintf(fp, "number_points_per_region ");
    for (i = 0; i < num_regions_created; i++)
    {
        fprintf(fp, "%d ", views_per_region[i]);
    }
    fprintf(fp, "\ntotal_acquired_regions %d\n", total_acq_regions);
    fprintf(fp, "region_acquisition_order ");
    for (i = 0; i < total_acq_regions; i++)
    {
        fprintf(fp, "%d ", region_schedule[i]);
    }
    fprintf(fp, "\nnum_phases %d\n", num_phases);
    fprintf(fp, "phase_description_table");

    if (mask_phase_flag)
    {
        fprintf(fp, "\n%d ", num_mask_regions);
        for (i = 0; i < num_mask_regions; i++)
        {
            fprintf(fp, "%d ", i);
        }
        for (i = 0; i < num_mask_regions; i++)
        {
            fprintf(fp, "%f ", 1.0);
        }
        phase_done_schedule[0] = num_mask_regions - 1;
        j0 = 2;
        cur_pos = num_mask_regions;
        i_left_limit = num_mask_regions;
    }
    i_right_limit = i_left_limit + num_regions * num_vs_phases - 1;
    cur_pos += (1 == acq_outerregion_first_flag);

    /********** Write out information for view-shared phase reconstruction **************/
    for (j = j0; j <= last_vs_phase_index; j++)
    {
        /* initialize indices */
        for (i = 0; i < num_mask_regions; i++)
        {
            indices[i]= -1;
        }

        fprintf(fp, "\n%d ", num_mask_regions);

        /* Start with A */
        fprintf(fp, "%d ", cur_pos);
        max_region_index = cur_pos;
        indices[region_schedule[cur_pos]] = 0;
        num = 1;
        cur_a = cur_pos;

        /* int combo_mode = 0 with {0,2,0,VIS,"0=backward, 1=nearest neighbor, 2=forward"}; */
        if (0 == combo_mode)
        {
            /* Search backwards in first */
            i = cur_pos + num_regions - 1;
            if (i > (total_acq_regions - 1)) /* needed when acq_outerregion_first_flag ON */
            {
                i = total_acq_regions - 1;
            }

            while ( (i_left_limit <= i) && (num < num_mask_regions) )
            {
                region_type = region_schedule[i];
                if (reverse_first_region_flag && (region_type == num_mask_regions))
                {
                    region_type = 1;
                }
                if ( -1 == indices[region_type] )
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_type] = 0;
                    num++;
                }
                i--;
            }

            /* Then search forward */
            i = cur_pos + num_regions - 1;
            while ( (i <= i_right_limit) && (num < num_mask_regions) )
            {
                if ( -1 == indices[region_schedule[i]] )
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_schedule[i]] = 0;
                    num++;
                }
                i++;
            }
        }
        else if (1 == combo_mode)
        {
            /* first add all the Bx regions in this phase */
            for (dist = 1; dist <= num_regions - 1; dist++)
            {
                i = cur_pos + dist;
                if ((total_acq_regions > i) && (-1 == indices[region_schedule[i]]))
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_schedule[i]] = 0;
                    num++;
                }
            }

            /* then start nearest neighbor searching */
            dist = 1;
            while ( (total_acq_regions > dist) && (num < num_mask_regions) )
            {
                /* left hand side */
                i = cur_pos - dist;
                region_type = region_schedule[i];
                if (reverse_first_region_flag && (region_type == num_mask_regions))
                {
                    region_type = 1;
                }
                if ((i_left_limit <= i) && (-1 == indices[region_type]))
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_type] = 0;
                    num++;
                }

                /* right hand side, start from Bx region instead of A */
                i = cur_pos + (num_regions - 1) + dist;
                if ((i <= i_right_limit) && (-1 == indices[region_schedule[i]]))
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_schedule[i]] = 0;
                    num++;
                }
                dist++;
            }
        }
        else if (2 == combo_mode)
        {
            /* Search forwards in first */
            i = cur_pos + num_regions - 1;
            while ( (i <= i_right_limit) && (num < num_mask_regions) )
            {
                if ( -1 == indices[region_schedule[i]] )
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_schedule[i]] = 0;
                    num++;
                }
                i++;
            }

            /* Then search backward */
            i = cur_pos + num_regions - 1;
            if (i > (total_acq_regions - 1)) /* needed when acq_outerregion_first_flag ON */
            {
                i = total_acq_regions - 1;
            }
            while ( (i_left_limit <= i) && (num < num_mask_regions) )
            {
                region_type = region_schedule[i];
                if (reverse_first_region_flag && (region_type == num_mask_regions))
                {
                    region_type = 1;
                }
                if ( -1 == indices[region_type] )
                {
                    fprintf(fp, "%d ", i);
                    max_region_index = (max_region_index < i) ? i : max_region_index;
                    indices[region_type] = 0;
                    num++;
                }
                i--;
            }
        }

        next_a = cur_a + num_regions;
 
        /* Jump to next A */
        cur_pos = next_a;

        /* phase weights */
        for (i = 0; i < num_mask_regions; i++)
        {
            fprintf(fp, "%f ", 1.0);
        }

        phase_done_schedule[j-1] = max_region_index;
    }
    fprintf(fp, "\n");

    /* For delayed non-view-shared phases */
    for (j = last_vs_phase_index + 1; j <= num_phases; j++)
    {
        /* initialize indices */
        for (i = 0; i < num_mask_regions; i++)
        {
            indices[i]= -1;
        }

        fprintf(fp, "%d ", num_mask_regions);

        for (i = 0; i < num_mask_regions; i++)
        {
            fprintf(fp, "%d ", i + cur_pos);
            max_region_index = i + cur_pos;
        }
        cur_pos += num_mask_regions;

        /* phase weights */
        for (i = 0; i < num_mask_regions; i++)
        {
            fprintf(fp, "%f ", 1.0);
        }
        fprintf(fp, "\n");

        phase_done_schedule[j-1] = max_region_index;
    }


    fclose(fp);

    return SUCCESS;
}

/**
 * generate_region_schedule
 *
 * Generate region acquisition schedule for a given prescription
 *
 *  @param[in]  int num_regions - number of regions in a view-shared phase (typically 2, meaning A and Bi).
 *  @param[in]  int num_sub_regions - number of sub_regions in the outer region (3 means B1 B2 B3).
 *  @param[in]  int num_phases - total number of phases.
 *  @param[in]  int mask_phase_flag - indicates if there is a mask phase as part of num_phases.
 *  @param[in]  int acq_outerregion_first_flag - indicates if outer region is acquired first to start a phase.
 *  @param[in]  int reverse_first_region_flag - indicates if the view-order for the first region is reversed.
 *  @param[out] int* number_mask_regions - number of regions in mask phase.
 *  @param[out] int* total_acquired_regions - total number of regions acquired in the entire schedule.
 *  @param[out] int* region_schedule - region schedule that will be played out during acquisition.
 *  @param[in]  const int length_region_schedule - max length of the region_schedule array.
 *  @param[in]  int peakPhaseIndex - the phase index for the first non-view-shared phase after view-sharing portion. 1-based.
 *  @param[out] int* regions_per_phase - number of regions acquired per phase.
 *  @return status of function (SUCCESS or FAILURE)
 */
STATUS generate_region_schedule( int num_regions, int num_sub_regions, int num_phases,
                                 int mask_phase_flag, int acq_outerregion_first_flag, int reverse_first_region_flag,
                                 int *number_mask_regions, int *total_acquired_regions,
                                 int *region_schedule, const int length_region_schedule, const int peakPhaseIndex, int *regions_per_phase )
{
    int num_mask_regions = 0;
    int total_acq_regions = 0;

    int i = 0, j = 0, k = 0, k0 = 0; /* k0 is the region index for the first dynamic phase */
    int num_vs_phases = 0;
    int num_delayed_phases = 0; /* delayed non-view-shared phases */

    if (0 == peakPhaseIndex) /* view-share all phases */
    {
        num_vs_phases = num_phases - (1 == mask_phase_flag);
    }
    else if (peakPhaseIndex > 0)
    {
        num_vs_phases = peakPhaseIndex - 1 - (1 == mask_phase_flag); /* peak phase index is 1-based */
    }
    else
    {
        printf("peakPhaseIndex = %d, and it is less than zero\n", peakPhaseIndex);
        return FAILURE;
    }
    if (num_vs_phases < 0)
    {
        printf("num_vs_phases = %d, and it is less than zero\n", num_vs_phases);
        return FAILURE;
    }
    num_delayed_phases = num_phases - (1 == mask_phase_flag) - num_vs_phases;

    /* Initialize region_schedule. */
    for (i = 0; i < length_region_schedule; i++)
    {
        region_schedule[i] = 0;
    }
    /* Initialize regions_per_phase. */
    for (i = 0; i < num_phases; i++)
    {
        regions_per_phase[i] = 0;
    }

    /* Mask regions = sigma n */
    if (2 == num_regions)
    {
        if (num_sub_regions <= 0)
        {
            printf("num_sub_regions = %d, and it is not greater than zero\n", num_sub_regions);
            return FAILURE;
        }
        num_mask_regions = 1 + num_sub_regions; /* A B1 B2 B3 */
    }
    else
    {
        num_mask_regions = num_regions*(num_regions+1)/2;
    }

    if (mask_phase_flag)
    {
        if (0 == peakPhaseIndex) /* view-share all phases */
        {
            total_acq_regions = num_mask_regions + num_regions*(num_phases-1);
        }
        else if (peakPhaseIndex > 0)
        {
            total_acq_regions = num_mask_regions*(num_phases - peakPhaseIndex + 2)  + num_regions*(peakPhaseIndex-2);
        }

        for (i = 0; i < num_mask_regions; i++)
        {
            if (acq_outerregion_first_flag && ((0 == i) || (1 == i)))
            {
                region_schedule[i] = 1 - i;
                if (reverse_first_region_flag && (0 == i))
                {
                    region_schedule[0] = num_mask_regions; /* the reverseEC B1 region is the last region in zy_export, so its region index is num_mask_regions */
                }
            }
            else
            {
                region_schedule[i] = i;
            }
        }
        regions_per_phase[0] = num_mask_regions;
        k  = num_mask_regions;
        k0 = num_mask_regions;
    }
    else
    {
        if (0 == peakPhaseIndex) /* view-share all phases */
        {
            total_acq_regions = num_regions*num_phases;
        }
        else if (peakPhaseIndex > 0)
        {
            total_acq_regions = num_mask_regions*(num_phases - peakPhaseIndex + 1)  + num_regions*(peakPhaseIndex-1);
        }
    }

    /* For view-shared each phase */
    for (j = 0; j < num_vs_phases; j++)
    {
        regions_per_phase[mask_phase_flag + j] = num_regions;
        if (2 == num_regions)
        {
            for (i = 0; i < 2; i++)
            {
                if ((1 == acq_outerregion_first_flag) == ((k-k0) % 2))
                {
                    region_schedule[k] = 0;
                }
                else
                {
                    region_schedule[k] = (((k-k0) / 2) % num_sub_regions) + 1;

                    if ((1 == reverse_first_region_flag) && (0 == j)) /* first dynamic phase and need to reverse view-order */
                    {
                        region_schedule[k] = num_mask_regions;
                    }
                }
                k++;
            }
        }
        else
        {
            for (i = 1; i <= num_regions; i++)
            {
                /* Assumes region i has i subregions, i.e center + first ring -> 2 + second ring -> 3 and so on */
                region_schedule[k] =  region_schedule[i*(i-1)/2 + j%i];
                k++;
            }
        }
    }

    /* For remaining non-view-shared delayed phases */
    for (j = 0; j < num_delayed_phases; j++)
    {
        regions_per_phase[mask_phase_flag + num_vs_phases + j] = num_mask_regions;
        for (i = 0; i < num_mask_regions; i++)
        {
            region_schedule[k] = i;
            k++;
        }
    }

    *number_mask_regions = num_mask_regions;
    *total_acquired_regions = total_acq_regions;

    return SUCCESS;
}


#ifndef HOST_TGT
/* for offline testing...

   can be compiled with:

   gcc -o test_vsc3d disco_support.c -lm -DSIM
*/

int main (int argc, char *argv[])
{
    int num_mask_regions = 0;
    int num_kernel_regions = 0;
    int total_acq_regions = 0;
    int RegionSchedule[MAX_NUM_REGIONS];
    int PhaseDoneSchedule[MAX_NUM_REGIONS];
    int views_per_region[32];
    int i = 0;
 
    if (8 != argc)
    {
        printf("\nUSAGE: test_vsc3d numphases mask_phase_flag numregions num_sub_regions acq_outerregion_first_flag reverse_first_region_flag combo_mode\n\n");
        exit(1);
    }

    int opfphases = atoi(argv[1]);
    int mask_phase_flag = atoi(argv[2]);
    int num_regions = atoi(argv[3]);
    int num_sub_regions = atoi(argv[4]);
    int acq_outerregion_first_flag = atoi(argv[5]);
    int reverse_first_region_flag = atoi(argv[6]);
    int combo_mode = atoi(argv[7]);

    /* int combo_mode = 0 with {0,2,0,VIS,"0=backward, 1=nearest neighbor, 2=forward"}; */
    const char *comboStr[] = {"backward", "nearest neighbor", "forward"};

    int optphases = opfphases;

    printf("num_regions: %d", num_regions);
    if (2 == num_regions)
    {
        printf(", num_sub_regions: %d", num_sub_regions);
    }

    printf(", phases: %d\n", opfphases);
    printf("mask_phase_flag: %d\n", mask_phase_flag);
    printf("acq_outerregion_first_flag: %d\n", acq_outerregion_first_flag);
    printf("reverse_first_region_flag: %d\n", reverse_first_region_flag);
    printf("combo_mode: %s\n", comboStr[combo_mode]);

    /* Filling this in with junk for now... */
    for (i = 0; i < num_mask_regions; i++)
    {
        views_per_region[i] = -1;
    }

    generate_region_schedule( num_regions, num_sub_regions,
                              opfphases, mask_phase_flag, acq_outerregion_first_flag, reverse_first_region_flag,
                              &num_mask_regions, &total_acq_regions,
                              RegionSchedule, MAX_NUM_REGIONS );

    writeVsc3DConfig( num_regions, num_mask_regions, total_acq_regions,
                      views_per_region, RegionSchedule, PhaseDoneSchedule,
                      opfphases, mask_phase_flag, acq_outerregion_first_flag, reverse_first_region_flag, combo_mode );

    printf("Phase Done Schedule:\n");
    for (i=0; i < opfphases; i++)
    {
        printf("%d ", PhaseDoneSchedule[i]);
    }
    printf("\n");
}

#endif /* HOST_TGT */
