use crate::Answer;

#[derive(Default)]
pub struct Day6;

impl Answer for Day6 {
    fn part_1(&self, input: &str) -> String {
        let mut lines = input.lines();
        let ops: Vec<&str> = lines.next_back().unwrap().split_whitespace().collect();
        let mut result: Vec<u64> = ops
            .iter()
            .map(|op| if *op == "*" { 1 } else { 0 })
            .collect();

        for line in lines {
            for ((res, op), col) in result.iter_mut().zip(&ops).zip(line.split_whitespace()) {
                let val = col.parse::<u64>().unwrap();
                match *op {
                    "*" => *res *= val,
                    "+" => *res += val,
                    _ => {}
                }
            }
        }

        result.iter().sum::<u64>().to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let problems = parse_input_part_two(input);
        problems.iter().sum::<u64>().to_string()
    }
}
#[derive(PartialEq, Debug)]
enum Op {
    Add,
    Mul,
}
fn parse_input_part_two(input: &str) -> Vec<u64> {
    let mut result = vec![];

    let mut lines = input.lines().rev();
    let mut operators = vec![];

    //IMPORTANT: All operators are always left-aligned in their columns
    let operator_line = lines.next().unwrap().chars();
    let mut line_length = 0;
    for (idx, char) in operator_line.enumerate() {
        if !char.is_whitespace() {
            match char {
                '+' => operators.push((idx, Op::Add)),
                '*' => operators.push((idx, Op::Mul)),
                _ => panic!("Unexpected operation character"),
            }
        }
        line_length += 1;
    }
    line_length += 1;

    let mut numbers: Vec<u64> = vec![0; line_length];

    for line in lines.rev() {
        for (idx, char) in line.chars().enumerate() {
            let active_number = numbers.get_mut(idx).unwrap();
            if char.is_ascii_digit() {
                *active_number = *active_number * 10 + char.to_digit(10).unwrap() as u64
            }
        }
    }

    for (i, (idx, operator)) in operators.iter().enumerate() {
        let next_operator_index = match operators.get(i + 1) {
            Some(next_operator) => next_operator.0,
            None => line_length,
        };
        match operator {
            Op::Add => {
                result.push(numbers[*idx..next_operator_index].iter().sum());
            }
            Op::Mul => {
                let numbers = &numbers[*idx..next_operator_index];
                let mut acc = 1;
                for number in numbers {
                    // All fields without numbers are zero in my parsing
                    // There are no "true" zeros in the input
                    if *number != 0 {
                        acc *= number
                    }
                }

                result.push(acc);
            }
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_6::Day6};

    const TEST: &str = r"
123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +  ";
    #[test]
    fn test_part_1() {
        let day = Day6;
        assert_eq!(day.part_1(TEST), "4277556");
    }
    #[test]
    fn test_part_2() {
        let day = Day6;
        assert_eq!(day.part_2(TEST), "3263827");
    }
}
