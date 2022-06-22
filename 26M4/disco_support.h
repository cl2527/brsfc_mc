/*
 * Copyright (c) 2014 by General Electric Company. All Rights Reserved.
 */

/**
 * \file disco_support.h
 *
 * This is the header file for DISCO support routines.
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

#ifndef disco_support_h
#define disco_support_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

STATUS writeVsc3DConfig( int num_regions, int num_mask_regions, int total_acq_regions,
                         int *views_per_region, int *region_schedule,
                         int *phase_done_schedule,
                         int num_phases, int mask_phase_flag, int acq_outerregion_first_flag, int reverse_first_region_flag, int combo_mode, const int peakPhaseIndex, const int kacq_uid );

STATUS generate_region_schedule( int num_regions, int num_sub_regions, int num_phases,
                                 int mask_phase_flag, int acq_outerregion_first_flag, int reverse_first_region_flag,
                                 int *number_mask_regions, int *total_acquired_regions,
                                 int *region_schedule, const int length_region_schedule, const int peakPhaseIndex, int *regions_per_phase );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
