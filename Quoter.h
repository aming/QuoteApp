#ifndef QUOTER_H
#define QUOTER_H

#include <string>
#include <vector>
#include <list>
#include "Locker.hpp"
#include "HttpClient.h"
#include "QuoteData.h"

class Quoter
{
 public:
  void Start();
  void Stop();
  QuoteData GetQuote(std::string symb);
  std::list<QuoteData> GetQuote();
  void AddQuote(std::string symb);
  void DelQuote(std::string symb);

 private:
  HttpClient m_client;
  synchronized<std::vector<std::string> > m_quoteList;
};

#endif // QUOTER_H

