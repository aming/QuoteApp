#ifndef QUOTEDATA_H
#define QUOTEDATA_H

#include <string>
#include <vector>

class QuoteData
{
 public:
  static QuoteData Parse(std::string symb, std::string rawString);
  std::string ToString();
 private:
  std::string m_symb;
  std::string m_rawStr;
  std::vector<std::string> m_tokens;
};

#endif //QUOTEDATA_H
