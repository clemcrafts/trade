#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <curl/curl.h>
#include <openssl/hmac.h>
#include <nlohmann/json.hpp>

// Helper function to write data received from libcurl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to generate HMAC-SHA256 signature
std::string create_signature(const std::string& secret_key, const std::string& timestamp, const std::string& method, const std::string& request_path, const std::string& body = "") {
    std::vector<unsigned char> key(secret_key.begin(), secret_key.end());
    std::string data = timestamp + method + request_path + body;

    unsigned int len = EVP_MAX_MD_SIZE;
    std::vector<unsigned char> hash(len);

    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(data.c_str()), data.length(),
         hash.data(), &len);

    hash.resize(len);
    return std::string(hash.begin(), hash.end());
}

// Function to perform the API request to buy Bitcoin
void buy_bitcoin(const std::string& api_key, const std::string& passphrase, const std::string& secret_key) {
    std::string timestamp = std::to_string(std::time(nullptr));  // Current Unix timestamp
    std::string method = "POST";
    std::string request_path = "/orders";
    nlohmann::json order = {
        {"type", "market"},
        {"side", "buy"},
        {"product_id", "BTC-USD"},
        {"funds", "10"}
    };

    std::string body = order.dump();
    std::string signature = create_signature(secret_key, timestamp, method, request_path, body);
    
    std::string url = "https://api-public.sandbox.pro.coinbase.com";
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("CB-ACCESS-KEY: " + api_key).c_str());
        headers = curl_slist_append(headers, ("CB-ACCESS-SIGN: " + signature).c_str());
        headers = curl_slist_append(headers, ("CB-ACCESS-TIMESTAMP: " + timestamp).c_str());
        headers = curl_slist_append(headers, ("CB-ACCESS-PASSPHRASE: " + passphrase).c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Response: " << response << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

int main() {
    std::string api_key = "your_api_key";
    std::string passphrase = "your_api_passphrase";
    std::string secret_key = "your_api_secret";

    buy_bitcoin(api_key, passphrase, secret_key);
    return 0;
}