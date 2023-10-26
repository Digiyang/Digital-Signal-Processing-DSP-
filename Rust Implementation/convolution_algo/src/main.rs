use std::fs::File;
use std::io::prelude::*;

use waveforms::{get_impulse_respnse, get_input_signal};

mod waveforms;

fn main() -> Result<(), anyhow::Error> {
    let input_sig = get_input_signal();
    let impulse_response = get_impulse_respnse();
    let mut output_sig = [0.0; waveforms::SIG_LENGTH + waveforms::IMP_LENGTH - 1];
    calc_convolution(&input_sig, &impulse_response, &mut output_sig);

    let mut _input_file = match File::create("input.dat") {
        Ok(mut file) => {
            for value in input_sig {
                writeln!(file, "{}", value)?;
            }
            println!("Input file created successfully.")
        }
        Err(error) => {
            println!("Error creating file: {}", error);
            return Err(error.into());
        }
    };
    let mut _impulse_file = match File::create("impulse.dat") {
        Ok(mut file) => {
            for value in impulse_response {
                writeln!(file, "{}", value)?;
            }
            println!("Impulse file created successfully.")
        }
        Err(error) => {
            println!("Error creating file: {}", error);
            return Err(error.into());
        }
    };

    let mut _output_file = match File::create("output.dat") {
        Ok(mut file) => {
            for value in output_sig {
                writeln!(file, "{}", value)?;
            }
            println!("Output file created successfully.");
        }
        Err(error) => {
            println!("Error creating file: {}", error);
            return Err(error.into());
        }
    };

    Ok(())
}

fn calc_convolution(input_sig: &[f64], impulse_response: &[f64], output_sig: &mut [f64]) {
    for i in 0..(input_sig.len() + impulse_response.len() - 1) {
        output_sig[i] = 0.0;
        for j in 0..input_sig.len() {
            if (i >= j) && (i - j < impulse_response.len()) {
                output_sig[i] += input_sig[j] * impulse_response[i - j];
            }
        }
    }
}
