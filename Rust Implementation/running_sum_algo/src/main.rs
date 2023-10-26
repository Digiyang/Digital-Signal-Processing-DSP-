use std::fs::File;
use std::io::prelude::*;

use waveforms::get_input_signal;

mod waveforms;

fn main() -> Result<(), anyhow::Error> {
    let input_sginal = get_input_signal();
    let mut output_signal = [0.0; waveforms::SIG_LENGTH];

    calc_running_sum(&get_input_signal(), &mut output_signal);

    let mut _input_file = match File::create("input_signal.dat") {
        Ok(mut file) => {
            for value in input_sginal {
                writeln!(file, "{}", value)?;
            }
            println!("Input signal written to file successfully.");
        }
        Err(e) => {
            println!("Error: {}", e);
            return Err(e.into());
        }
    };

    let mut _output_signal_file = match File::create("output_signal.dat") {
        Ok(mut file) => {
            for value in output_signal {
                writeln!(file, "{}", value)?;
            }
            println!("Output signal written to file successfully.");
        }
        Err(e) => {
            println!("Error: {}", e);
            return Err(e.into());
        }
    };

    Ok(())
}

fn calc_running_sum(input_signal: &[f64], output_signal: &mut [f64]) {
    output_signal[0] = input_signal[0];

    for i in 1..output_signal.len() {
        output_signal[i] = output_signal[i - 1] + input_signal[i];
    }
}
