#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGNAL_LENGTH 320
#define IMPULSE_RESPONSE_LENGTH 29
extern double InputSignal_f32_1kHz_15kHz[SIGNAL_LENGTH];
extern double Impulse_response[IMPULSE_RESPONSE_LENGTH];

/* ----------------------------------------------------------------------
** Convolution Algorithm
** x[n] * h[n] = y[n]
** 320 + 29 - 1 = 348 samples
** y[i] = Sum(M-1, j=0) x[i-j] * h[j]
** The index, i, determines the number of samples in the output signal
** The index, j, determines the number of samples in the impulse response
** ------------------------------------------------------------------- */

double convolution(double *in_sig_arr, double *out_sig_arr, double *imp_sig_arr,
                   int in_sig_length, int imp_sig_length);

int main() {
  double out_sig[SIGNAL_LENGTH + IMPULSE_RESPONSE_LENGTH - 1];
  convolution(InputSignal_f32_1kHz_15kHz, out_sig, Impulse_response,
              SIGNAL_LENGTH, IMPULSE_RESPONSE_LENGTH);

  // Open the file for writing
  FILE *in_sig_fptr, *imp_sig_fptr, *out_sig_fptr;

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

  // write impulse response to a file to visulize in gnuplot
  imp_sig_fptr = fopen("imp_sig.dat", "w");
  if (imp_sig_fptr == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  for (int i = 0; i < IMPULSE_RESPONSE_LENGTH; i++) {
    fprintf(imp_sig_fptr, "%f\n", Impulse_response[i]);
  }
  fclose(imp_sig_fptr);

  // write output signal to visualize in gnuplot
  out_sig_fptr = fopen("out_sig.dat", "w");
  if (out_sig_fptr == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  for (int i = 0; i < SIGNAL_LENGTH + IMPULSE_RESPONSE_LENGTH - 1; i++) {
    fprintf(out_sig_fptr, "%f\n", out_sig[i]);
  }

  fclose(out_sig_fptr);

  return 0;
}

double convolution(double *in_sig_arr, double *out_sig_arr, double *imp_sig_arr,
                   int in_sig_length, int imp_sig_length) {
  int i, j;

  for (i = 0; i < in_sig_length + imp_sig_length - 1; i++) {
    out_sig_arr[i] = 0;
    for (j = 0; j < imp_sig_length; j++) {
      if ((i - j) >= 0 && (i - j) < in_sig_length) {
        out_sig_arr[i] += in_sig_arr[i - j] * imp_sig_arr[j];
      }
    }
  }

  return 0;
}
