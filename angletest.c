#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define gr (sqrt(5)-1)/2
#define M_PI 3.14159265358979323846


int main_test_goldenratioangle ()
{
	float golden_ratio_angle;
    float phi;
    FILE *angle;
    int i;

    golden_ratio_angle = 0;
    angle  = fopen("scanner_angle.txt","w");

    for (i=0; i<6*192; i++)
    {
        golden_ratio_angle += gr;
        golden_ratio_angle -= floor(golden_ratio_angle);
        /*phi = fmod(golden_ratio_angle,1.0) * 2.0 * M_PI;*/
        phi = golden_ratio_angle  * 2.0 * M_PI;
        fprintf(angle, "%04d, %*.10f ,%*.10f\n",i, 15, golden_ratio_angle, 15, phi);
    }
    fclose(angle);
	return 0;
}
