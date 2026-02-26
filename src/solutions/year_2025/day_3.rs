use crate::Answer;

#[derive(Default)]
pub struct Day3;

impl Answer for Day3 {
    fn part_1(&self, input: &str) -> String {
        max_joltage_sum(input, 2).to_string()
    }

    fn part_2(&self, input: &str) -> String {
        max_joltage_sum(input, 12).to_string()
    }
}

fn max_joltage_sum(input: &str, length: usize) -> u64 {
    input
        .lines()
        .map(|bank| {
            let bytes = bank.as_bytes();
            let mut max_joltage = Vec::with_capacity(length);

            for (i, &b) in bytes.iter().enumerate() {
                let remaining = bytes.len() - i;
                while !max_joltage.is_empty()
                    && max_joltage.last().unwrap() < &b
                    && max_joltage.len() + remaining > length
                {
                    max_joltage.pop();
                }
                if max_joltage.len() < length {
                    max_joltage.push(b);
                }
            }
            max_joltage
                .iter()
                .fold(0, |n, &d| n * 10 + (d - b'0') as u64)
        })
        .sum()
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_3::Day3};

    const TEST: &str = r"987654321111111
811111111111119
234234234234278
818181911112111";

    #[test]
    fn test_part_1() {
        let day = Day3;
        assert_eq!(day.part_1(TEST), "357");
    }
    #[test]
    fn test_part_2() {
        let day = Day3;
        assert_eq!(day.part_2(TEST), "3121910778619");
    }
}
