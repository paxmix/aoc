use crate::Answer;

#[derive(Default)]
pub struct Day1;

impl Answer for Day1 {
    fn part_1(&self, input: &str) -> String {
        let mut dial = 50;
        let mut pwd = 0;
        for line in input.lines() {
            let mut chars = line.chars();
            let dir = chars.next().unwrap();
            let val: i32 = chars.as_str().parse().expect("invalid number");
            match dir {
                'R' => dial += val,
                'L' => dial -= val,
                _ => {}
            }
            dial = dial.rem_euclid(100);
            if dial == 0 {
                pwd += 1;
            }
        }
        pwd.to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let mut dial = 50;
        let mut pwd = 0;
        for line in input.lines() {
            let mut chars = line.chars();
            let dir = chars.next().unwrap();
            let val: i32 = chars.as_str().parse().expect("invalid number");
            let prev = dial;
            match dir {
                'R' => dial += val,
                'L' => dial -= val,
                _ => {}
            }
            match dial {
                n if n < 0 => {
                    pwd -= dial / 100 - 1;
                    if prev == 0 {
                        pwd -= 1;
                    }
                }
                n if n >= 100 => pwd += dial / 100,
                0 => pwd += 1,
                _ => {}
            }
            dial = dial.rem_euclid(100);
        }
        pwd.to_string()
    }
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_1::Day1};
    const TEST: &str = r"L68
L30
R48
L5
R60
L55
L1
L99
R14
L82";

    #[test]
    fn test_part_1() {
        let day = Day1;
        assert_eq!(day.part_1(TEST), "3");
    }

    #[test]
    fn test_part_2() {
        let day = Day1;
        assert_eq!(day.part_2(TEST), "6");
    }
}
