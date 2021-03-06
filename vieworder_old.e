@host
void brs_genviewtab(int nleaves, 
                    int nphases,
                    int slquant,
                    int vieword,
                    int nfolds,
                    int leafskip,
                    int leafgroup,
                    int dofracz,
                    int fracz_fact,
                    int debug,
                    int * fs_slice,
                    int * jumptab,
                    SPIRAL_VIEW *vt)
{
   int i, j, k;
   int t;		/***************  BOXU 2010.02.11   ******/
   int modresult;
   int acqslquant;
   int innerslquant;

   acqslquant = slquant*fracz_fact;
   innerslquant = 2*(int)((float)slquant*(fracz_fact-.5));

   switch (vieword)
   {
       case BRS_PERIPHERAL:
       {
           if (!dofracz)
           {
               for (i = 0; i < nphases; i++) {
                   for (j = 0; j < nleaves; j++) {
                       for (k = 0; k < slquant; k++) {
                           vt[i*nleaves*slquant + j*slquant + k].phase = i;
                           if (k%2 == 0)
                               vt[i*nleaves*slquant + j*slquant + k].slice = (slquant + slquant/2+(k+1)/2 -1)%slquant;
                           else
                               vt[i*nleaves*slquant + j*slquant + k].slice = (slquant + slquant/2-(k+1)/2 -1)%slquant;
                           modresult = j%nfolds;
                           vt[i*nleaves*slquant + j*slquant + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
                       }
                   }
               }
           } else {
               for (i = 0; i < nphases; i++) {
                   for (j = 0; j < nleaves; j++) {
                       for (k = 0; k <= innerslquant; k++) {
                           vt[i*nleaves*acqslquant + j*acqslquant + k].phase = i;
                           if (k%2 == 0)
                               vt[i*nleaves*acqslquant + j*acqslquant + k].slice = (slquant + slquant/2+(k+1)/2 -1)%slquant;
                           else
                               vt[i*nleaves*acqslquant + j*acqslquant + k].slice = (slquant + slquant/2-(k+1)/2 -1)%slquant;
                           modresult = j%nfolds;
                           vt[i*nleaves*acqslquant + j*acqslquant + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
                       }
                       for (k = 1; k < acqslquant - innerslquant; k++) {
                           vt[i*nleaves*acqslquant + j*acqslquant + k+innerslquant].phase = i;
                           vt[i*nleaves*acqslquant + j*acqslquant + k+innerslquant].slice = acqslquant-innerslquant-k-1;
                           modresult = j%nfolds;
                           vt[i*nleaves*acqslquant + j*acqslquant + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
                        }
                    }
                }
           }
       }
	      break;
	
	/******************    BOXU 2010.02.11 **************************/
	/* Change view order to linear */
       case BRS_BO_PERIPHERAL:
       {
           if (!pfkz_flag)
           {
               for (i = 0; i < nphases; i++) {
                   for (j = 0; j < nleaves; j++) {
                       for (k = 0; k < slquant; k++) {
                           vt[i*nleaves*slquant + j*slquant + k].phase = i;
                           vt[i*nleaves*slquant + j*slquant + k].slice = k;
                           modresult = j%nfolds;
                            /* CRT ************************************* Pascal 10/12/10 */
                           if (golden_ratio_flag)
                              vt[i*nleaves*slquant + j*slquant + k].leaf = j;
                           else
                              vt[i*nleaves*slquant + j*slquant + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
                       }
                   }
               }
           }

	   /* USING PFKZ_TOTAL TO GET FRACTIONAL ENCODING */
           else {
               for (i = 0; i < nphases; i++) {
                   for (j = 0; j < nleaves; j++) {
                       for (k = 0; k < pfkz_total; k++) {
                           vt[i*nleaves*pfkz_total + j*pfkz_total + k].phase = i;
                           vt[i*nleaves*pfkz_total + j*pfkz_total + k].slice = slquant-pfkz_total+k;
                           modresult = j%nfolds;
						               /* CRT ************************************* Pascal 10/12/10 */
                           if (golden_ratio_flag)
                              vt[i*nleaves*pfkz_total + j*pfkz_total + k].leaf = j;
                           else
                              vt[i*nleaves*pfkz_total + j*pfkz_total + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
						
            }
					}					   
				}
			}
		}
           break;
	/************************************************/
	
    case BRS_2D:
      {
        for (i = 0; i < nphases; i++) {
          for (k = 0; k < slquant; k++) {
            for (j = 0; j < nleaves; j++) {
              vt[i*nleaves*slquant + k*nleaves + j].phase = i;
              vt[i*nleaves*slquant + k*nleaves + j].slice = k;
              vt[i*nleaves*slquant + k*nleaves + j].leaf = j;
            }
          }
        }
      }
      break;
	
  /******************    BOXU 2010.02.11 **************************/
	/* Change view order to linear with segment. This is for the consistance with pfkz_segment */
       case BRS_BO_LIVER:
	   {
           /* normal linear view order */
           if (!pfkz_flag)   
           {
               for (i = 0; i < nphases; i++) {
                   for (j = 0; j < nleaves; j++) {
                       for (k = 0; k < slquant; k++) {
                           vt[i*nleaves*slquant + j*slquant + k].phase = i;
                           vt[i*nleaves*slquant + j*slquant + k].slice = k;
                           modresult = j%nfolds;
                           if (golden_ratio_flag)
                                vt[i*nleaves*slquant + j*slquant + k].leaf = j;
                           else
                                vt[i*nleaves*slquant + j*slquant + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
                       }
                   }
               }
           }

			/* partial kz with segment */
           else
		   {
				int last_slice = pfkz_total -1;
				for (i = 0; i < nphases; i++)
				{
					for (j = 0; j < nleaves; j++)
					{
						k = 0;
						for (segment_cnt = 0; segment_cnt < pfkz_segments  ; segment_cnt++)
						{
							for (slice_cnt = 0 ; slice_cnt < pfkz_views_per_segment ; slice_cnt++ )
							{
								t = (last_slice-segment_cnt) - pfkz_segments*slice_cnt;
								vt[i*nleaves*pfkz_total + j*pfkz_total + k].phase = i;
								vt[i*nleaves*pfkz_total + j*pfkz_total + k].slice = t;
								modresult = j%nfolds;
                if (golden_ratio_flag)
                  vt[i*nleaves*pfkz_total + j*pfkz_total + k].leaf = j;
                else
								  vt[i*nleaves*pfkz_total + j*pfkz_total + k].leaf = modresult*(nleaves/nfolds) + j/nfolds;
								k = k+1;
							}
						}					   
					}
				}
			}
		}
           break;

/************************************************/

       case BRS_CINE:
       {
           int phase = 0;
           int leaf = 0;
           for (i = 0; i < nphases * acqslquant * nleaves; i++) {
               /*vt[i].slice = i/(nphases*nleaves);*/
               vt[i].slice = acqslquant - 1 - i/(nphases*nleaves);
               vt[i].phase = phase;
               vt[i].leaf = leaf;
               leaf+=leafskip;
               if (leaf >= nleaves) {
                   phase++;
                   leaf = leaf%leafskip;
               }
               if (phase >= nphases) {
                   phase = 0;
                   leaf = (leaf+1)%leafskip;
               }
           }
           for (i = 0; i < leafskip*acqslquant; i++)
           {
               jumptab[i] = i*(nleaves/leafskip)*nphases;
           }
           for (i = leafskip*acqslquant; i < 1024; i++)
           {
               jumptab[i] = -1;
           }
       }
           break;
       case BRS_CORONARY:
       {
           int lg;
           for (i = 0; i < nphases; i++) {
               for (j = 0; j < nleaves; j+=leafgroup) {
                   for (k = 0; k < acqslquant; k++) {
                       for (lg = 0; lg < leafgroup; lg++) {
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].phase = i;
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].slice = acqslquant-1-k;
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].leaf = j + lg;
                       }
                   }
               }
           }
           for (i = 0; i < nleaves/leafgroup; i++)
           {
               jumptab[i] = i*leafgroup*acqslquant*nphases;
           }
           for (i = nleaves/leafgroup; i < 1024; i++)
           {
               jumptab[i] = -1;
           }
           *fs_slice = acqslquant-1;
       }
           break;
       case BRS_CORONARY_SHIFT:
       {
           int lg;
           for (i = 0; i < nphases; i++) {
               for (j = 0; j < nleaves; j+=leafgroup) {
                   for (k = 0; k < acqslquant; k++) {
                       for (lg = 0; lg < leafgroup; lg++) {
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].phase = i;
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].slice = (acqslquant-1-k + j/leafgroup)%acqslquant;
                           vt[i*acqslquant*leafgroup + j*acqslquant*nphases + k*leafgroup + lg].leaf = j + lg;
                       }
                   }
               }
           }
           for (i = 0; i < nleaves/leafgroup; i++)
           {
               jumptab[i] = i*leafgroup*acqslquant*nphases;
           }
           for (i = nleaves/leafgroup; i < 1024; i++)
           {
               jumptab[i] = -1;
           }
           *fs_slice = acqslquant-1;
       }
           break;
       case BRS_PERIPHERAL_REL_PRIME:
       {
           for (i = 0; i < nphases; i++) {
               for (j = 0; j < nleaves; j++) {
                   for (k = 0; k < acqslquant; k++) {
                       vt[i*nleaves*acqslquant + j*acqslquant + k].leaf = (j*leafskip)%nleaves;
                       vt[i*nleaves*acqslquant + j*acqslquant + k].slice= acqslquant-1-k;
                       vt[i*nleaves*acqslquant + j*acqslquant + k].phase = i;
                   }
               }
           }
       }
           break;
       default:
           break;
   }

  if (debug)
  {
    FILE *fp = NULL;
    if (NULL != (fp = fopen("brs_genviewtab.txt", "w"))) {
      for (i = 0; i < nphases*nleaves*acqslquant; i++)
      {
        fprintf(fp, "%06d : phase = %04d, slice = %04d, leaf = %04d\n", 
               i, vt[i].phase, vt[i].slice, vt[i].leaf);
      }
      fclose(fp);
    }
  }
}
