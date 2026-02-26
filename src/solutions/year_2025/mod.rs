mod day_1;
mod day_2;
mod day_3;
mod day_4;
mod day_5;
mod day_6;
mod day_7;
mod day_8;

use crate::{Answer, DayCtor};

pub const NUM_OF_DAYS: usize = 12;
const PROGRESS_DAYS: usize = 8;

const DAYS: [DayCtor; PROGRESS_DAYS] = [
    || Box::new(day_1::Day1),
    || Box::new(day_2::Day2),
    || Box::new(day_3::Day3),
    || Box::new(day_4::Day4),
    || Box::new(day_5::Day5),
    || Box::new(day_6::Day6),
    || Box::new(day_7::Day7),
    || Box::new(day_8::Day8::default()),
];

pub fn get_answer(day: usize) -> Option<Box<dyn Answer>> {
    DAYS.get(day - 1).map(|ctor| ctor())
}
