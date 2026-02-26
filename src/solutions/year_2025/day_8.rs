use crate::Answer;
use disjoint::DisjointSetVec;
use itertools::Itertools;

pub struct Day8 {
    p1_iter_num: usize,
}

impl Default for Day8 {
    fn default() -> Self {
        Self { p1_iter_num: 1000 }
    }
}

#[derive(Clone)]
struct JBox(u64, u64, u64);
impl From<&str> for JBox {
    fn from(value: &str) -> Self {
        let mut parts = value.split(',').map(|part| part.parse().unwrap());
        JBox(
            parts.next().unwrap(),
            parts.next().unwrap(),
            parts.next().unwrap(),
        )
    }
}

impl Answer for Day8 {
    fn part_1(&self, input: &str) -> String {
        let boxes: Vec<JBox> = input.lines().map(JBox::from).collect();
        let mut dsv: DisjointSetVec<JBox> = DisjointSetVec::from(boxes.clone());

        for (_, i, j) in get_all_distances(&boxes).iter().take(self.p1_iter_num) {
            dsv.join(*i, *j);
        }

        (0..dsv.len())
            .map(|i| dsv.root_of(i))
            .counts()
            .values()
            .sorted_unstable_by(|a, b| b.cmp(a))
            .take(3)
            .product::<usize>()
            .to_string()
    }

    fn part_2(&self, input: &str) -> String {
        let boxes: Vec<JBox> = input.lines().map(JBox::from).collect();
        let mut dsv: DisjointSetVec<JBox> = DisjointSetVec::from(boxes.clone());

        let mut joined: (usize, usize) = (0, 0);
        let mut count = 0;
        for (_, i, j) in get_all_distances(&boxes) {
            if dsv.join(i, j) {
                joined = (i, j);
                count += 1;
                // Stop if all JBoxes are joined in the same circuit
                if count == boxes.len() - 1 {
                    break;
                }
            }
        }
        (boxes[joined.0].0 * boxes[joined.1].0).to_string()
    }
}

fn square_distance(this: &JBox, other: &JBox) -> u64 {
    let dx = this.0.abs_diff(other.0);
    let dy = this.1.abs_diff(other.1);
    let dz = this.2.abs_diff(other.2);
    dx * dx + dy * dy + dz * dz
}

fn get_all_distances(boxes: &[JBox]) -> Vec<(u64, usize, usize)> {
    let n = boxes.len();
    let mut distances: Vec<(u64, usize, usize)> = Vec::with_capacity(n * (n - 1) / 2);
    for i in 0..n {
        for j in i + 1..n {
            let dist = square_distance(&boxes[i], &boxes[j]);
            distances.push((dist, i, j));
        }
    }
    distances.sort_unstable_by_key(|d| d.0);
    distances
}

#[cfg(test)]
mod tests {
    use crate::{Answer, solutions::year_2025::day_8::Day8};

    const TEST: &str = r"162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689";
    const DAY: Day8 = Day8 { p1_iter_num: 10 };
    #[test]
    fn test_part_1() {
        assert_eq!(DAY.part_1(TEST), "40");
    }
    #[test]
    fn test_part_2() {
        assert_eq!(DAY.part_2(TEST), "25272");
    }
}
