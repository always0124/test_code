test:
	g++ -std=c++11 -o test test.cpp  -I third_lib/curl/include -I third_lib/curlpp/include -L third_lib/curl/lib -L third_lib/curlpp/lib -lcurlpp -lcurl
