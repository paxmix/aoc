use crate::Answer;

#[derive(Default)]
pub struct Day7;

impl Answer for Day7 {
    // for test file and puzzle file, there are no '^' at the start or the end of each line
    // so there is no bound checking when splitting
    // also, there are always a blank line between each split.

    fn part_1(&self, input: &str) -> String {
        let mut lines = input.lines();
        let first = lines.next().unwrap();
        let mut beam_at = vec![false; first.len()];
        let mut split_count = 0;
        beam_at[first.find('S').unwrap()] = true;

        for line in lines
            .enumerate()
            .filter_map(|(i, l)| (!i.is_multiple_of(2)).then_some(l))
        {
            for (col, cell) in line.char_indices() {
                if cell == '^' && beam_at[col] {
                    beam_at[col] = false;
                    split_count += 1;
                    beam_at[col - 1] = true;
                    beam_at[col + 1] = true;
                }
            }
        }

        split_count.to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let mut lines = input.split('\n');
        let first = lines.next().unwrap();
        let s_index = first.find('S').unwrap();
        let mut timelines: Vec<u64> = vec![1; first.len()];

        for line in lines
            .rev()
            .enumerate()
            .filter_map(|(i, l)| (!i.is_multiple_of(2)).then_some(l))
        {
            for (i, c) in line.char_indices() {
                if c == '^' {
                    timelines[i] = timelines[i - 1] + timelines[i + 1];
                }
            }
        }

        timelines[s_index].to_string()
    }
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_7::Day7};

    const TEST: &str = r".......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............";
    #[test]
    fn test_part_1() {
        let day = Day7;
        assert_eq!(day.part_1(TEST), "21");
    }
    #[test]
    fn test_part_2() {
        let day = Day7;
        assert_eq!(day.part_2(TEST), "40");
    }
}
