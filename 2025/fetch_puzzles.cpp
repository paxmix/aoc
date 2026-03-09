#include <curl/curl.h>
#include <filesystem>
#include <fstream>
#include <iostream>

constexpr std::string_view DOTENV = ".env";
constexpr std::string_view PUZZLE_DIR = "puzzles";
constexpr int NUMS_DAY = 12;
constexpr int STATUS_OK = 200;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    auto out = static_cast<std::ofstream *>(userp);
    size_t total = size * nmemb;
    out->write(static_cast<char *>(contents), total);
    return *out ? total : 0;
}

void load_dotenv()
{
    std::ifstream file(DOTENV.data());
    if (!file.is_open()) {
        std::cerr << "Warning: .env file not found\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        setenv(key.c_str(), value.c_str(), 1);
    }
}

class Curl {
  public:
    Curl()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        handle = curl_easy_init();
    }
    ~Curl()
    {
        if (handle) curl_easy_cleanup(handle);
        curl_global_cleanup();
    }
    CURL *get() { return handle; }

  private:
    CURL *handle{};
};

bool fetch_and_save(CURL *curl, int day)
{
    const char *session = std::getenv("AOC_SESSION");
    if (!session || std::string(session).empty()) {
        std::cerr << "AOC_SESSION not set in environment\n";
        return false;
    }

    std::string url = "https://adventofcode.com/2025/day/" + std::to_string(day) + "/input";

    std::filesystem::path filepath = std::filesystem::path(PUZZLE_DIR) / ("day_" + std::to_string(day) + ".txt");

    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << "\n";
        return false;
    }

    std::string cookie = "session=" + std::string(session);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl error: " << curl_easy_strerror(res) << "\n";
        return false;
    }

    long status{};
    if (CURLcode info_res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status); info_res != CURLE_OK) {
        std::cerr << "curl getting error\n";
        return -1;
    }
    if (status != STATUS_OK) {
        std::cerr << "HTTP error: " << status << "\n";
        return false;
    }

    return true;
}

int main()
{
    load_dotenv();

    std::filesystem::create_directories(PUZZLE_DIR);

    Curl curl;
    if (!curl.get()) {
        std::cerr << "curl init failed\n";
        return 1;
    }

    for (int day = 1; day <= NUMS_DAY; ++day) {
        std::cout << "Downloading day " << day << "...\n";
        if (!fetch_and_save(curl.get(), day)) std::cerr << "Failed day " << day << "\n";
    }
}
