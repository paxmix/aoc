for i in range(2, 26):
    day = f"{i:02}"
    filename = f"day{day}.go"
    content = f"""package year2023

import "github.paxmix.aoc/internal/utils"

type Day{day} struct{{}}

func init() {{
	utils.Registry[{i}] = Day{day}{{}}
}}

func (d Day{day}) Part1(input string) string {{
	return ""
}}

func (d Day{day}) Part2(input string) string {{
	return ""
}}"""
    with open(filename, "w") as file:
        file.write(content)
