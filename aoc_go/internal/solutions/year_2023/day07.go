package year2023

import (
	"slices"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day07 struct{}

func init() {
	utils.Registry[7] = Day07{}
}

func (d Day07) Part1(input string) string {
	return solution07(input, true)
}

func (d Day07) Part2(input string) string {
	return solution07(input, false)
}

func solution07(input string, isPart1 bool) string {
	var hands []hand
	for line := range strings.SplitSeq(input, "\n") {
		// 32T3K 765
		var cards [5]int
		cardsStr, betStr, _ := strings.Cut(line, " ")
		for i := range 5 {
			cards[i] = getCardVal(cardsStr[i], isPart1)
		}
		bet, _ := strconv.Atoi(betStr)
		var handKind handType
		if isPart1 {
			handKind = getHandType(cards)
		} else {
			handKind = getHandJoker(cards)
		}
		hands = append(hands, hand{cards, bet, handKind})
	}
	slices.SortFunc(hands, sortHands)
	var total int
	for rank, hand := range hands {
		total += (rank + 1) * hand.bet
	}
	return strconv.Itoa(total)
}

type hand struct {
	cards [5]int
	bet   int
	kind  handType
}

type handType int

const (
	highCard handType = iota
	pair
	twoPair
	threeOAK
	fullHouse
	fourOAK
	fiveOAk
)

const JOKER = 1

func getCardVal(card byte, isPart1 bool) int {
	var val int
	switch {
	case card >= '2' && card <= '9':
		val = int(card - '0')
	case card == 'T':
		val = 10
	case card == 'J':
		if isPart1 {
			val = 11
		} else {
			val = JOKER
		}
	case card == 'Q':
		val = 12
	case card == 'K':
		val = 13
	case card == 'A':
		val = 14
	}
	return val
}

func sortHands(a, b hand) int {
	if a.kind != b.kind {
		return int(a.kind - b.kind)
	}
	for i := range 5 {
		if a.cards[i] != b.cards[i] {
			return a.cards[i] - b.cards[i]
		}
	}
	return 0
}

func getHandType(cards [5]int) handType {
	counts := make(map[int]int)
	for _, card := range cards {
		counts[card]++
	}
	freqs := make([]int, 0, len(counts))
	for _, count := range counts {
		freqs = append(freqs, count)
	}
	slices.SortFunc(freqs, func(a, b int) int {
		return b - a
	})

	switch {
	case freqs[0] == 5:
		return fiveOAk
	case freqs[0] == 4:
		return fourOAK
	case freqs[0] == 3 && freqs[1] == 2:
		return fullHouse
	case freqs[0] == 3:
		return threeOAK
	case freqs[0] == 2 && freqs[1] == 2:
		return twoPair
	case freqs[0] == 2:
		return pair
	}
	return highCard
}

func getHandJoker(cards [5]int) handType {
	counts := make(map[int]int)
	for _, card := range cards {
		counts[card]++
	}
	freqs := make([]int, 0, len(counts))
	for card, count := range counts {
		if card != JOKER {
			freqs = append(freqs, count)
		}
	}
	if len(freqs) == 0 {
		return fiveOAk
	}

	slices.SortFunc(freqs, func(a, b int) int {
		return b - a
	})
	freqs[0] += counts[JOKER]

	switch {
	case freqs[0] == 5:
		return fiveOAk
	case freqs[0] == 4:
		return fourOAK
	case freqs[0] == 3 && freqs[1] == 2:
		return fullHouse
	case freqs[0] == 3:
		return threeOAK
	case freqs[0] == 2 && freqs[1] == 2:
		return twoPair
	case freqs[0] == 2:
		return pair
	}
	return highCard
}
