/* -------------------------------------------------------------------
** Running Sum Algorithm
** -------------------------------------------------------------------
** y[i] = y[i-1] + x[i]
** ------------------------------------------------------------------- */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGNAL_LENGTH 320
#define IMPULSE_RESPONSE_LENGTH 29

extern double InputSignal_f32_1kHz_15kHz[SIGNAL_LENGTH];
double out_sig[SIGNAL_LENGTH];
double running_sum(double *in_sig_arr, double *out_sig_arr, int out_sig_length);

int main() {

  running_sum(InputSignal_f32_1kHz_15kHz, out_sig, SIGNAL_LENGTH);

  FILE *in_sig_fptr, *out_sig_fptr;

  // write input signal to a file to visulize in gnuplot
  in_sig_fptr = fopen("in_sig.dat", "w");
  if (in_sig_fptr == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  for (int i = 0; i < SIGNAL_LENGTH; i++) {
    fprintf(in_sig_fptr, "%f\n", InputSignal_f32_1kHz_15kHz[i]);
  }
  fclose(in_sig_fptr);

  // write output signal to visualize in gnuplot
  out_sig_fptr = fopen("out_sig.dat", "w");
  if (out_sig_fptr == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  for (int i = 0; i < SIGNAL_LENGTH; i++) {
    fprintf(out_sig_fptr, "%f\n", out_sig[i]);
  }

  fclose(out_sig_fptr);

  return 0;
}

double running_sum(double *in_sig_arr, double *out_sig_arr,
                   int out_sig_length) {
  int i;

  out_sig_arr[0] = in_sig_arr[0];

  for (i = 1; i < out_sig_length; i++) {
    out_sig_arr[i] = out_sig_arr[i - 1] + in_sig_arr[i];
  }

  return 0;
}
