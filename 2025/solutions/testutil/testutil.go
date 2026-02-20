// Package testutil store template test func
package testutil

import "testing"

type SolTest interface {
	Part1(string) string
	Part2(string) string
}

func Run(t *testing.T, sol SolTest, input, want1, want2 string) {
	t.Helper()

	t.Run("Part1", func(t *testing.T) {
		got := sol.Part1(input)
		if got != want1 {
			t.Fatalf("got %s, want %s", got, want1)
		}
	})

	t.Run("Part2", func(t *testing.T) {
		got := sol.Part2(input)
		if got != want2 {
			t.Fatalf("got %s, want %s", got, want2)
		}
	})
}
