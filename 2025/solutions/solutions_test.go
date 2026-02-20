package solutions

import (
	"testing"

	"aoc/2025/solutions/testutil"
)

func TestDay1(t *testing.T) {
	testutil.Run(t, Day1{}, tests[1], "3", "6")
}

func TestDay2(t *testing.T) {
	testutil.Run(t, Day2{}, tests[2], "1227775554", "4174379265")
}

func TestDay3(t *testing.T) {
	testutil.Run(t, Day3{}, tests[3], "357", "3121910778619")
}

func TestDay4(t *testing.T) {
	testutil.Run(t, Day4{}, tests[4], "13", "43")
}

func TestDay5(t *testing.T) {
	testutil.Run(t, Day5{}, tests[5], "3", "14")
}

func TestDay6(t *testing.T) {
	testutil.Run(t, Day6{}, tests[6], "4277556", "3263827")
}

var tests []string = []string{
	"",
	`L68
L30
R48
L5
R60
L55
L1
L99
R14
L82`,
	"11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124",
	`987654321111111
811111111111119
234234234234278
818181911112111`,
	`..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.`,
	`3-5
10-14
16-20
12-18

1
5
8
11
17
32`,
	`123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  `,
}
