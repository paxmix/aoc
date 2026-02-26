use std::time::Instant;

use aoc::run;

fn main() {
    let start = Instant::now();
    let day = 8;
    let part = 2;

    match run(day, part) {
        Some(()) => {}
        None => println!("Invalid parameters"),
    };

    println!("Took {:?}", start.elapsed());
}
