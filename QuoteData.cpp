#include "QuoteData.h"
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

QuoteData QuoteData::Parse(string symb, string rawString) {
  QuoteData data;
  data.m_symb = symb;
  size_t pos = rawString.find('\n');
  data.m_rawStr = rawString.substr(0, pos-1);
  char_separator<char> sep("|");
  tokenizer<char_separator<char> > token(data.m_rawStr, sep);
  for (tokenizer<char_separator<char> >::iterator it=token.begin(); it!=token.end(); ++it) {
    pos = it->find('*');
    string quoteStr((*it), pos+1, it->size()-pos);
    data.m_tokens.push_back(quoteStr);
  }
  return data;
}

string QuoteData::ToString() {
  string retStr = m_symb; 
  int i = 0;
  for (vector<string>::iterator it = m_tokens.begin(); it != m_tokens.end(); it++) {
    retStr += " " + *it;
  }
  return retStr;
}
