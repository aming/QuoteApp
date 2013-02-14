#include "Quoter.h"
using namespace std;
const string URL="http://www.aastocks.com/eng/DataService/getlivestock.asp?stock_id=";

void Quoter::Start() {
  m_client.start();
}

void Quoter::Stop() {
  m_client.stop();
}

void Quoter::AddQuote(string symb) {
  LOCK(m_quoteList) {
    m_quoteList.push_back(symb);
  }
}

void Quoter::DelQuote(string symb) {
  LOCK(m_quoteList) {
    vector<string>::iterator it;
    for (it = m_quoteList.begin(); it != m_quoteList.end(); it++) {
      if (*it == symb) break;
    }
    if (it != m_quoteList.end()) {
      m_quoteList.erase(it);
    }
  }
}

list<QuoteData> Quoter::GetQuote() {
  string resultStr = "";
  list<QuoteData> dataLst;
  int index = 0;
  LOCK(m_quoteList) {
    for (vector<string>::iterator it=m_quoteList.begin(); it<m_quoteList.end(); it++) {
      dataLst.push_back(GetQuote(*it));
    }
  }
  return dataLst;
}

QuoteData Quoter::GetQuote(string symb) {
  string targetUrl = URL+symb;
  string resultStr = m_client.downloadString(targetUrl).c_str();
  while (resultStr == "")
  {
    //printf("quote: failed\n");
    m_client.stop();
    m_client.start();
    resultStr = m_client.downloadString(targetUrl).c_str();
  }
  return QuoteData::Parse(symb, resultStr); 
}

