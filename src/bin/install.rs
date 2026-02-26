use aoc::download_puzzles;

#[tokio::main]
async fn main() {
    match download_puzzles().await {
        Ok(()) => {}
        Err(err) => eprintln!("Error caught: {err}"),
    }
}
