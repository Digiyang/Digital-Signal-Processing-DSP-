mod waveforms;

fn main() {
    let input_signal = waveforms::get_input_signal();
    let mean = calc_mean(&input_signal);
    println!("Mean: {}", mean);
}

fn calc_mean(input_signal: &[f64]) -> f64 {
    let sum: f64 = input_signal.iter().sum();
    sum / input_signal.len() as f64
}
