#include <SFML/Graphics.hpp>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

struct product {

}


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
	size_t totalSize = size * nmemb;
	userp->append((char*)contents, totalSize);
	return totalSize;
}

int main(){

	unsigned  width = 500;
	unsigned  height = 800;
	sf::RenderWindow window(sf::VideoMode({width, height}), "Json Data Analitics");
	window.setFramerateLimit(100);






	std::string readBuffer;


	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.hypixel.net/v2/skyblock/bazaar");


		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);


		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);


		CURLcode res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			std::cerr << "Curl error: " << curl_easy_strerror(res) << std::endl;
		} else {
			std::cout << "Успешно скачано " << readBuffer.size() << " байт данных!" << std::endl;
		}

		curl_easy_cleanup(curl);
	}



	try{

		json root = json::parse(readBuffer);

		if (!root.value("success", false)) {
			std::cerr << "API вернул success: false\n";
			return -1;
		}

		if (!root.contains("products")) {
			std::cerr << "В JSON отсутствуют products\n";
			return -1;
		}

		const auto& products = root["products"];

		for (const auto& item : products.items()) {
			std::string product_id


		}



	} catch (const json::parse_error& e) {
		std::cerr << "Ошибка парсинга тяжелого JSON: " << e.what() << '\n';
	}




	while (window.isOpen()) {








		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}








	window.clear();


	window.display();

	}
}
