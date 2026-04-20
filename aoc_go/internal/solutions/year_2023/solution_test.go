package year2023

import (
	"testing"

	"github.paxmix.aoc/internal/utils"
)

func TestSolutions(t *testing.T) {
	tests := []struct {
		name       string
		solution   utils.Solution
		exP1       string
		expectedP1 string
		exP2       string
		expectedP2 string
	}{
		{
			name:       "Day 01",
			solution:   Day01{},
			exP1:       D1P1,
			expectedP1: "142",
			exP2:       D1P2,
			expectedP2: "281",
		},
		{
			name:       "Day 02",
			solution:   Day02{},
			exP1:       D2,
			expectedP1: "8",
			exP2:       D2,
			expectedP2: "2286",
		},
		{
			name:       "Day 03",
			solution:   Day03{},
			exP1:       D3,
			expectedP1: "4361",
			exP2:       D3,
			expectedP2: "467835",
		},
		{
			name:       "Day 04",
			solution:   Day04{},
			exP1:       D4,
			expectedP1: "13",
			exP2:       D4,
			expectedP2: "30",
		},
		{
			name:       "Day 05",
			solution:   Day05{},
			exP1:       D5,
			expectedP1: "35",
			exP2:       D5,
			expectedP2: "46",
		},
		{
			name:       "Day 06",
			solution:   Day06{},
			exP1:       D6,
			expectedP1: "288",
			exP2:       D6,
			expectedP2: "71503",
		},
		{
			name:       "Day 07",
			solution:   Day07{},
			exP1:       D7,
			expectedP1: "6440",
			exP2:       D7,
			expectedP2: "5905",
		},
		{
			name:       "Day 08",
			solution:   Day08{},
			exP1:       D8P1,
			expectedP1: "2",
			exP2:       D8P2,
			expectedP2: "6",
		},
		{
			name:       "Day 09",
			solution:   Day09{},
			exP1:       D9,
			expectedP1: "114",
			exP2:       D9,
			expectedP2: "2",
		},
		{
			name:       "Day 10",
			solution:   Day10{},
			exP1:       D10P1,
			expectedP1: "8",
			exP2:       D10P2,
			expectedP2: "4",
		},
		{
			name:       "Day 11",
			solution:   Day11{},
			exP1:       D11,
			expectedP1: "374",
			exP2:       D11,
			expectedP2: "82000210",
		},
		{
			name:       "Day 12",
			solution:   Day12{},
			exP1:       D12,
			expectedP1: "21",
			exP2:       D12,
			expectedP2: "525152",
		},
		{
			name:       "Day 13",
			solution:   Day13{},
			exP1:       D13,
			expectedP1: "405",
			exP2:       D13,
			expectedP2: "400",
		},
		{
			name:       "Day 14",
			solution:   Day14{},
			exP1:       D14,
			expectedP1: "136",
			exP2:       D14,
			expectedP2: "64",
		},
		{
			name:       "Day 15",
			solution:   Day15{},
			exP1:       D15,
			expectedP1: "1320",
			exP2:       D15,
			expectedP2: "145",
		},
		{
			name:       "Day 16",
			solution:   Day16{},
			exP1:       D16,
			expectedP1: "46",
			exP2:       D16,
			expectedP2: "51",
		},
		{
			name:       "Day 17",
			solution:   Day17{},
			exP1:       D17,
			expectedP1: "102",
			exP2:       D17,
			expectedP2: "94",
		},
		{
			name:       "Day 18",
			solution:   Day18{},
			exP1:       D18,
			expectedP1: "62",
			exP2:       D18,
			expectedP2: "952408144115",
		},
		{
			name:       "Day 19",
			solution:   Day19{},
			exP1:       D19,
			expectedP1: "19114",
			exP2:       D19,
			expectedP2: "",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got1 := tt.solution.Part1(tt.exP1); got1 != tt.expectedP1 {
				t.Errorf("%s Part 1: got %s, want %s", tt.name, got1, tt.expectedP1)
			}

			if got2 := tt.solution.Part2(tt.exP2); got2 != tt.expectedP2 {
				t.Errorf("%s Part 2: got %s, want %s", tt.name, got2, tt.expectedP2)
			}
		})
	}
}
