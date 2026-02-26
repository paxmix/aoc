mod solutions;
use std::fs;

use dotenv::dotenv;
use reqwest::Client;

use crate::solutions::year_2025::{NUM_OF_DAYS, get_answer};

const PUZZLE_DIR: &str = "puzzles/year_2025";
pub async fn download_puzzles() -> std::io::Result<()> {
    fs::create_dir_all(PUZZLE_DIR)?;
    dotenv().ok();
    let client = Client::new();

    for day in 1..=NUM_OF_DAYS {
        let puzzle = fetch_puzzle(day, &client).await;
        fs::write(format!("{PUZZLE_DIR}/day_{day}.txt"), puzzle)?;
    }

    Ok(())
}

async fn fetch_puzzle(day: usize, client: &Client) -> String {
    let url = format!("https://adventofcode.com/2025/day/{}/input", day);
    let session_token = std::env::var("AOC_SESSION").expect("AOC_SESSION not set in .env file");

    client
        .get(&url)
        .header("Cookie", format!("session={}", session_token))
        .send()
        .await
        .expect("Failed to fetch input")
        .text()
        .await
        .expect("Failed to read response")
}

fn get_input(path: &str) -> std::io::Result<String> {
    let contents = std::fs::read_to_string(path)?;
    Ok(contents.trim().to_string())
}

pub fn run(day: usize, part: usize) -> Option<()> {
    if !(1..=NUM_OF_DAYS).contains(&day) {
        return None;
    }

    let solution = get_answer(day)?;
    let path = format!("puzzles/year_2025/day_{day}.txt");
    let input = get_input(&path).ok()?;

    let result = match part {
        1 => solution.part_1(&input),
        2 => solution.part_2(&input),
        _ => return None,
    };

    println!("Day {day} part {part} answer is {result}.");
    Some(())
}

pub trait Answer {
    fn part_1(&self, input: &str) -> String;
    fn part_2(&self, input: &str) -> String;
}

pub type DayCtor = fn() -> Box<dyn Answer>;
