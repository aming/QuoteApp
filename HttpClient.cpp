#include "HttpClient.h"
#include <cstring>

HttpClient::HttpClient() {
  curl_global_init(CURL_GLOBAL_ALL);
}

HttpClient::~HttpClient() {
  curl_global_cleanup();
}

void HttpClient::start() {
  wr_error = 0;
  wr_index = 0;

  /* First step, init curl */
  session = curl_easy_init();
  if (!session) {
    printf("couldn't init curl\n");
  } else {
    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, write_data );
    curl_easy_setopt(session, CURLOPT_WRITEDATA, this);
  }

  wr_buf = new char[MAX_BUF];
}

void HttpClient::stop() {
  curl_easy_cleanup(session);
  delete[] wr_buf;
}


/*
 * Write data callback function (called within the context of 
 * curl_easy_perform.
 */
size_t HttpClient::write_data( void *buffer, size_t size, size_t nmemb, HttpClient *context)
{
  int segsize = size * nmemb;

  /* Check to see if this data exceeds the size of our buffer. If so, 
   * set the user-defined context value and return 0 to indicate a
   * problem to curl.
   */
  if ( context->wr_index + segsize > context->MAX_BUF ) {
    return 0;
  }

  /* Copy the data from the curl buffer into our buffer */
  memcpy( (void *)&(context->wr_buf)[context->wr_index], buffer, (size_t)segsize );

  /* Update the write index */
  context->wr_index += segsize;

  /* Null terminate the buffer */
  context->wr_buf[context->wr_index] = 0;

  /* Return the number of bytes received, indicating to curl that all is okay */
  return segsize;
}

std::string HttpClient::downloadString(std::string url) {
  /* Tell curl the URL of the file we're going to retrieve */
  curl_easy_setopt(session, CURLOPT_URL, url.c_str() );
  std::string returnStr = "";

  /* Allow curl to perform the action */
  curl_code = curl_easy_perform(session);

  long http_code = 0;
  curl_easy_getinfo (session, CURLINFO_RESPONSE_CODE, &http_code);
  if (http_code == 200 && curl_code != CURLE_ABORTED_BY_CALLBACK)
  {
    //Succeeded
    returnStr = wr_buf;
  }
  else
  {
    //Failed
    printf( "Code = %ld (write_error = %d)\n", http_code, wr_error );
  }
  wr_index = 0;
  wr_buf[0] = 0;

  return returnStr;
}
