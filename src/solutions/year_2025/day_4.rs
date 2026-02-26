use crate::Answer;

#[derive(Default)]
pub struct Day4;

impl Answer for Day4 {
    fn part_1(&self, input: &str) -> String {
        let mut grid = get_grid(input);
        let h = grid.len();
        let w = grid[0].len();

        get_rolls(&mut grid, h, w, |_| {}).to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let mut grid = get_grid(input);
        let h = grid.len();
        let w = grid[0].len();
        let mut sum = 0;

        loop {
            let accessible_rolls = get_rolls(&mut grid, h, w, |roll| *roll = b'.');
            if accessible_rolls == 0 {
                break;
            }
            sum += accessible_rolls
        }
        sum.to_string()
    }
}

const DIRS: [(isize, isize); 8] = [
    (-1, -1),
    (-1, 0),
    (-1, 1),
    (0, -1),
    (0, 1),
    (1, -1),
    (1, 0),
    (1, 1),
];

fn get_rolls<F>(grid: &mut [Vec<u8>], h: usize, w: usize, mut remove_rolls: F) -> u32
where
    F: FnMut(&mut u8),
{
    let mut count = 0;
    for i in 0..h {
        for j in 0..w {
            if grid[i][j] == b'@' && neighbors(grid, i, j, h, w) < 4 {
                count += 1;
                remove_rolls(&mut grid[i][j]);
            }
        }
    }
    count
}

fn neighbors(grid: &[Vec<u8>], i: usize, j: usize, h: usize, w: usize) -> u8 {
    let mut count = 0;
    for (di, dj) in DIRS {
        let ni = i as isize + di;
        let nj = j as isize + dj;
        if ni >= 0
            && nj >= 0
            && ni < h as isize
            && nj < w as isize
            && grid[ni as usize][nj as usize] == b'@'
        {
            count += 1;
        }
    }
    count
}

fn get_grid(input: &str) -> Vec<Vec<u8>> {
    input.lines().map(|line| line.as_bytes().to_vec()).collect()
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_4::Day4};

    const TEST: &str = r"..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.";

    #[test]
    fn test_part_1() {
        let day = Day4;
        assert_eq!(day.part_1(TEST), "13");
    }
    #[test]
    fn test_part_2() {
        let day = Day4;
        assert_eq!(day.part_2(TEST), "43");
    }
}
