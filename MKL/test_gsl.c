/*example.c*/

#include <stdio.h>            

#include <gsl/gsl_sf.h>        // header: GSL special functions



int main(int argc, char const *argv[])

{

      // inputs for special functions

        double x[5] = {1.,2.,3.,4.,5.};

          // calculate zero-order Bessel function at given points

            for (int i = 0; i < 5; ++i){

                        printf("J0(%.3f) = %.3f\n", x[i],
                                gsl_sf_bessel_J0(x[i]));

                            }

                return 0;

}
