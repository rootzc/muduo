// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CONDITION_H
#define MUDUO_BASE_CONDITION_H

#include <muduo/base/Mutex.h>

#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace muduo
{
//条件变量
class Condition : boost::noncopyable
{
 public:
  explicit Condition(MutexLock& mutex)
    : mutex_(mutex)
  {
	  //初始化条件变量
    MCHECK(pthread_cond_init(&pcond_, NULL));
  }

  ~Condition()
  {
	  //销毁条件变量
    MCHECK(pthread_cond_destroy(&pcond_));
  }

  void wait()
  {
	//创建条件变量对象
    MutexLock::UnassignGuard ug(mutex_);
	//
    MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  // returns true if time out, false otherwise.
  bool waitForSeconds(double seconds);

  //发送一次消息
  void notify()
  {
    MCHECK(pthread_cond_signal(&pcond_));
  }
	//广播唤醒全部
  void notifyAll()
  {
    MCHECK(pthread_cond_broadcast(&pcond_));
  }

 private:
	 //互斥锁
  MutexLock& mutex_;
  //条件变量
  pthread_cond_t pcond_;
};

}
#endif  // MUDUO_BASE_CONDITION_H
