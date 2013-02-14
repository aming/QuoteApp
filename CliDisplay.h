#ifndef CLI_DISPLAY_H
#define CLI_DISPLAY_H

#include "Quoter.h"
#include <boost/thread.hpp>
#include <list>

class CliDisplay {
 public:
  CliDisplay(std::list<Quoter*> quoter);
  ~CliDisplay();
  void Start();
  void Stop();
  void SetQuoteInterval(int interval);
 private:
  void WorkingThread();

  boost::thread m_workerThread;
  std::list<Quoter*> m_quoterList;
  boost::posix_time::seconds m_sleepTime;
  bool m_start;
};

#endif //CLI_DISPLAY_H
