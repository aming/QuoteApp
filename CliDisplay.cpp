#include "CliDisplay.h"
#include <curses.h>
using namespace std;

CliDisplay::CliDisplay(list<Quoter*> quoter) :
  m_sleepTime(boost::posix_time::seconds(10)),
  m_quoterList(quoter)
{
  m_start = false;
}

CliDisplay::~CliDisplay() {
  Stop();
}

void CliDisplay::Start() {
  if (!m_start) {
    m_start = true;
    m_workerThread = boost::thread(&CliDisplay::WorkingThread, this);
  }
}

void CliDisplay::Stop() {
  if (m_start) {
    m_start = false;
    m_workerThread.join();
  }
}

void CliDisplay::WorkingThread() {
  while (m_start) {
    for (list<Quoter*>::iterator it = m_quoterList.begin(); it != m_quoterList.end(); it++) {
      list<QuoteData> data = (*it)->GetQuote();
      system("clear");
      for(list<QuoteData>::iterator it = data.begin(); it != data.end(); it++) {
        printf("Quote::%s\n", (*it).ToString().c_str());
      }
    }

    boost::this_thread::sleep(m_sleepTime);
  }
}

void CliDisplay::SetQuoteInterval(int interval) {
  m_sleepTime = boost::posix_time::seconds(interval);
}
