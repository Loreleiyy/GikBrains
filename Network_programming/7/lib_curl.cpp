
#include <string>


#include "Client.h"

int main(int argc, const char* const argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <URL>" << std::endl;
		return EXIT_FAILURE;
	}
	curl_global_init(CURL_GLOBAL_ALL);
	
	// Получить хэндл cURL.
	Client client(argv[1]);
	
	//if (curl)
	//{
	//	// Сначала задаётся URL, получающий запрос POST.
	//	curl_easy_setopt(curl, CURLOPT_URL,
	//		"http://www.heroeswm.ru/");
	//	// Теперь задаются данные POST запроса.
	//	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
	//	// Выполнить запрос, res будет содержать код возврата.
	//	res = curl_easy_perform(curl);
	//	// Проверить на ошибки.
	//	if (res != CURLE_OK)
	//	{
	//		fprintf(stderr, "curl_easy_perform() failed: %s\n",
	//			curl_easy_strerror(res));
	//	}
	//	// Освобождение ресурсов.
	//	curl_easy_cleanup(curl);
	//}

	client.set_write();
	client.client_work();
	curl_global_cleanup();

	return 0;
}
