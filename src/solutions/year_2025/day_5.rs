use crate::Answer;
use std::cmp::Ordering;

#[derive(Default)]
pub struct Day5;

impl Answer for Day5 {
    fn part_1(&self, input: &str) -> String {
        let (ranges, values) = input.split_once("\n\n").unwrap();
        let pairs = parse_ranges(ranges);
        let vals = parse_values(values);
        let mut count: usize = 0;
        for val in vals {
            if pairs
                .binary_search_by(|pair| {
                    if val < pair.min {
                        Ordering::Greater
                    } else if val > pair.max {
                        Ordering::Less
                    } else {
                        Ordering::Equal
                    }
                })
                .is_ok()
            {
                count += 1;
            }
        }
        count.to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let (ranges, _) = input.split_once("\n\n").unwrap();
        let pairs = parse_ranges(ranges);
        pairs
            .iter()
            .map(|pair| pair.max - pair.min + 1)
            .sum::<u64>()
            .to_string()
    }
}

fn parse_ranges(ranges: &str) -> Vec<Pair> {
    let lines: Vec<_> = ranges.lines().collect();
    let mut pairs = Vec::with_capacity(lines.len());
    for range in lines {
        let (low, high) = range.split_once('-').unwrap();
        let min = low.parse::<u64>().unwrap();
        let max = high.parse::<u64>().unwrap();
        pairs.push(Pair { min, max });
    }
    pairs.sort();
    let mut merged: Vec<Pair> = Vec::new();
    for pair in pairs {
        match merged.last_mut() {
            None => merged.push(pair),
            Some(last) if pair.min > last.max + 1 => merged.push(pair),
            Some(last) if pair.max > last.max => last.max = pair.max,
            _ => {}
        }
    }
    merged
}

fn parse_values(values: &str) -> Vec<u64> {
    let lines: Vec<_> = values.lines().collect();
    let mut vals = Vec::with_capacity(lines.len());
    for value in lines {
        vals.push(value.parse::<u64>().unwrap());
    }
    vals
}

#[derive(PartialEq, Eq, Clone)]
struct Pair {
    min: u64,
    max: u64,
}
impl Ord for Pair {
    fn cmp(&self, other: &Self) -> Ordering {
        (self.min, self.max).cmp(&(other.min, other.max))
    }
}
impl PartialOrd for Pair {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_5::Day5};

    const TEST: &str = r"3-5
10-14
16-20
12-18

1
5
8
11
17
32";
    #[test]
    fn test_part_1() {
        let day = Day5;
        assert_eq!(day.part_1(TEST), "3");
    }
    #[test]
    fn test_part_2() {
        let day = Day5;
        assert_eq!(day.part_2(TEST), "14");
    }
}
