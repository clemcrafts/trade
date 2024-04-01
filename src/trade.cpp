#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <chrono>
#include <openssl/hmac.h>
#include <openssl/sha.h> // Include the header where SHA256_DIGEST_LENGTH is defined

std::string generate_signature(const std::string& secretKey, const std::string& queryString) {
    unsigned char* digest;
    digest = HMAC(EVP_sha256(), secretKey.c_str(), secretKey.length(),
                  reinterpret_cast<const unsigned char*>(queryString.c_str()), queryString.length(), NULL, NULL);    

    char mdString[SHA256_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    return std::string(mdString);
}

int main() {
    std::string apiKey = "Your-Binance-API-Key";
    std::string apiSecret = "Your-Binance-Secret-Key";
    std::string baseUrl = "https://api.binance.com";
    std::string endpoint = "/api/v3/order";
    std::string symbol = "BTCUSDT";
    std::string quantity = "0.001"; // Example quantity
    long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    std::string queryString = "symbol=" + symbol + "&side=BUY&type=MARKET&quantity=" + quantity + "&timestamp=" + std::to_string(timestamp);
    std::string signature = generate_signature(apiSecret, queryString);

    std::cout << "This is the signature: " << signature << std::endl;

    return 0;
}