#include <boost/thread.hpp>

#ifndef LOCKER_HPP
#define LOCKER_HPP

#define LOCK(x) for (_locker _lock(x); _lock._run(); _lock._stop())
#define TRY_LOCK(x) for (_locker _lock(x, 0); _lock._run(); _lock._stop())

template <class T>
class synchronized : public T, public boost::mutex {
 public :
  synchronized<T>() : T(), boost::mutex() {}
};

class _locker {
 public:
  _locker(boost::mutex& m) : m_(m) { m_.lock(); run_ = true; }
  _locker(boost::mutex& m, int) : m_(m) { run_ = m_.try_lock(); }
  ~_locker() { m_.unlock(); }
  bool _run() { return run_; }
  void _stop() { run_ = false; }
 private:
  boost::mutex&   m_;
  bool            run_;
};

#endif //LOCKER_HPP
