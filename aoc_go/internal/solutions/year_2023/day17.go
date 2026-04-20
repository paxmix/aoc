package year2023

import (
	"container/heap"
	"encoding/binary"
	"hash/maphash"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day17 struct{}

func init() {
	utils.Registry[17] = Day17{}
}

func (d Day17) Part1(input string) string {
	return solution(input, 1, 3)
}

func (d Day17) Part2(input string) string {
	return solution(input, 4, 10)
}

func solution(input string, minConsecutive, maxConsecutive int) string {
	lines := strings.Split(input, "\n")
	rows := len(lines)
	cols := len(lines[0])
	grid := make([][]int, rows)
	for r := range rows {
		grid[r] = make([]int, cols)
		for c := range cols {
			grid[r][c] = int(lines[r][c] - '0')
		}
	}

	// visited stores [row][col][directionIdx][consecutiveCount]
	visited := make(map[uint64]bool)
	var h maphash.Hash
	seed := maphash.MakeSeed()

	pq := new(priorityQueue)
	heap.Init(pq)

	// Start at (0,0). We can go East (0,1) or South (1,0)
	heap.Push(pq, &state{0, 0, 0, 1, 0, 0})
	heap.Push(pq, &state{0, 0, 1, 0, 0, 0})

	for pq.Len() > 0 {
		curr := heap.Pop(pq).(*state)
		if curr.x == rows-1 && curr.y == cols-1 {
			return strconv.Itoa(curr.heatLoss)
		}
		// Create a unique key for the state
		key := stateHash(&h, seed, curr.x, curr.y, curr.dx, curr.dy, curr.consecutive)
		if visited[key] {
			continue
		}
		visited[key] = true
		// Possible direction: Straight, Left turn, Right turn
		// Try straight first
		if curr.consecutive < maxConsecutive {
			nx, ny := curr.x+curr.dx, curr.y+curr.dy
			if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
				heap.Push(pq, &state{
					x: nx, y: ny, dx: curr.dx, dy: curr.dy,
					consecutive: curr.consecutive + 1,
					heatLoss:    curr.heatLoss + grid[nx][ny],
				})
			}
		}
		// Try turning if have moved straight for minConsecutive
		if curr.consecutive >= minConsecutive {
			turns := [][2]int{
				{curr.dy, -curr.dx}, // Left
				{-curr.dy, curr.dx}, // Right
			}
			for _, d := range turns {
				nx, ny := curr.x+d[0], curr.y+d[1]
				if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
					heap.Push(pq, &state{
						x: nx, y: ny, dx: d[0], dy: d[1],
						consecutive: 1,
						heatLoss:    curr.heatLoss + grid[nx][ny],
					})
				}
			}
		}
	}

	return ""
}

type state struct {
	x, y        int
	dx, dy      int
	consecutive int
	heatLoss    int
}

type priorityQueue []*state

func (pq priorityQueue) Len() int           { return len(pq) }
func (pq priorityQueue) Less(i, j int) bool { return pq[i].heatLoss < pq[j].heatLoss }
func (pq priorityQueue) Swap(i, j int)      { pq[i], pq[j] = pq[j], pq[i] }
func (pq *priorityQueue) Push(x any)        { *pq = append(*pq, x.(*state)) }
func (pq *priorityQueue) Pop() any {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[:n-1]
	return item
}

func stateHash(h *maphash.Hash, seed maphash.Seed, x, y, dx, dy, consecutive int) uint64 {
	h.Reset()
	h.SetSeed(seed)
	// Write the state variables as bytes
	// Using 8-byte buffer for each bit (assuming 64-bit)
	buf := make([]byte, 8)
	vals := []int{x, y, dx, dy, consecutive}
	for _, v := range vals {
		binary.LittleEndian.PutUint64(buf, uint64(v))
		h.Write(buf)
	}
	return h.Sum64()
}
