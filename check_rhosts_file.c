#include <stdio.h>
#include <psc.h>

int main(void)
{
  if (-1 == check_rhosts_file()) {
    printf("Unable to modify .rhosts file for sdc. Please fix manually\n");
  };
}
