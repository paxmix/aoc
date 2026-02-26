use crate::Answer;

#[derive(Default)]
pub struct Day2;

impl Answer for Day2 {
    fn part_1(&self, input: &str) -> String {
        sum_invalid_ids(input, |id| {
            let length = int_len(id);
            length.is_multiple_of(2) && !is_valid_factor(id, 2, length)
        })
        .to_string()
    }

    fn part_2(&self, input: &str) -> String {
        sum_invalid_ids(input, |id| !is_valid(id)).to_string()
    }
}

fn sum_invalid_ids<F>(input: &str, is_invalid: F) -> u64
where
    F: Fn(u64) -> bool,
{
    let mut sum = 0;
    for pair in input.split(',') {
        let (low, high) = pair.split_once('-').unwrap();
        let low = low.parse::<u64>().unwrap();
        let high = high.parse::<u64>().unwrap();

        for id in low..=high {
            if is_invalid(id) {
                sum += id;
            }
        }
    }
    sum
}

fn is_valid_factor(mut id: u64, factor: usize, length: usize) -> bool {
    let pow_10 = 10u64.pow((length / factor) as u32);
    let base = id % pow_10;
    id /= pow_10;
    while id > 0 {
        if base != id % pow_10 {
            return true;
        }
        id /= pow_10;
    }

    false
}

fn is_valid(id: u64) -> bool {
    let length = int_len(id);
    for factor in 2..=length {
        if length.is_multiple_of(factor) && !is_valid_factor(id, factor, length) {
            return false;
        }
    }
    true
}

fn int_len(mut num: u64) -> usize {
    let mut length = 0;
    while num > 0 {
        length += 1;
        num /= 10;
    }
    length
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_2::Day2};

    const TEST: &str = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

    #[test]
    fn test_part_1() {
        let day = Day2;
        assert_eq!(day.part_1(TEST), "1227775554");
    }
    #[test]
    fn test_part_2() {
        let day = Day2;
        assert_eq!(day.part_2(TEST), "4174379265");
    }
}
