#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <curl/curl.h>

class HttpClient
{
 public:
  HttpClient();
  ~HttpClient();
  void start();
  void stop();
  std::string downloadString(std::string path);
 private:
  static size_t write_data( void *buffer, size_t size, size_t nmemb, HttpClient *context);

  const static int MAX_BUF = 10240;

  CURL* session;
  CURLcode curl_code;
  int  wr_error;
  int  wr_index;
  char* wr_buf;
};

#endif // HTTP_CLIENT_H

