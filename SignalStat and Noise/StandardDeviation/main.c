#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGNAL_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIGNAL_LENGTH];
double calc_mean(double *sig_src_arr, int sig_length);
double calc_variance(double *sig_src_arr, double sig_mean, int sig_length);
double calc_standard_deviation(double variance);

int main() {
  double mean = calc_mean(InputSignal_f32_1kHz_15kHz, SIGNAL_LENGTH);
  double variance =
      calc_variance(InputSignal_f32_1kHz_15kHz, mean, SIGNAL_LENGTH);
  double standard_deviation = calc_standard_deviation(variance);

  printf("Mean               = %f\nVariance           = "
         "%f\nStandard_deviation = %f\n",
         mean, variance, standard_deviation);

  return 0;
}

double calc_mean(double *sig_src_arr, int sig_length) {
  double _mean = 0.0;
  for (int i = 0; i < sig_length; i++) {
    _mean += sig_src_arr[i];
  }
  _mean /= (double)sig_length;
  return _mean;
}

double calc_variance(double *sig_src_arr, double sig_mean, int sig_length) {
  double _variance = 0.0;

  for (int i = 0; i < sig_length; i++) {
    _variance += pow((sig_src_arr[i] - sig_mean), 2);
  }
  _variance /= (double)sig_length;

  return _variance;
}

double calc_standard_deviation(double variance) { return sqrt(variance); }