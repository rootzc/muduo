#ifndef MUDUO_BASE_LOGFILE_H
#define MUDUO_BASE_LOGFILE_H

#include <muduo/base/Mutex.h>
#include <muduo/base/Types.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace muduo
{

namespace FileUtil
{
class AppendFile;
}
//��־�ļ�
class LogFile : boost::noncopyable
{
 public:
  LogFile(const string& basename,
          size_t rollSize,
          bool threadSafe = true,
          int flushInterval = 3,
          int checkEveryN = 1024);
  ~LogFile();

  void append(const char* logline, int len);
  void flush();//ˢ��
  bool rollFile();

 private:
  void append_unlocked(const char* logline, int len);

  static string getLogFileName(const string& basename, time_t* now);

  const string basename_;
  const size_t rollSize_;
  const int flushInterval_;
  const int checkEveryN_;

  int count_;
	//�����������߳��µ�
  boost::scoped_ptr<MutexLock> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;//��һ��ˢ�µ����ڣ�
  time_t lastFlush_;//�ϴ�ˢ��
  boost::scoped_ptr<FileUtil::AppendFile> file_;//��־�ļ�

  const static int kRollPerSeconds_ = 60*60*24;
};

}
#endif  // MUDUO_BASE_LOGFILE_H
