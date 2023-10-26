mod waveforms;

fn main() {
    let input_signal = waveforms::get_input_signal();
    let mean = calc_mean(&input_signal);
    let variance = calc_variance(&input_signal, mean);
    let deviation = calc_std_deviation(variance);
    println!(
        "\nMean      : {}\nVariance  : {}\nDeviation : {}\n",
        mean, variance, deviation
    );
}

fn calc_mean(input_signal: &[f64]) -> f64 {
    let sum: f64 = input_signal.iter().sum();
    sum / input_signal.len() as f64
}

fn calc_variance(input_signal: &[f64], mean: f64) -> f64 {
    let mut sum: f64 = 0.0;
    for i in input_signal {
        sum += (i - mean).powi(2);
    }
    sum / input_signal.len() as f64
}

fn calc_std_deviation(variance: f64) -> f64 {
    variance.sqrt()
}
