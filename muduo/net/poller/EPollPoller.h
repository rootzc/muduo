// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_POLLER_EPOLLPOLLER_H
#define MUDUO_NET_POLLER_EPOLLPOLLER_H

#include <muduo/net/Poller.h>

#include <vector>

struct epoll_event;

namespace muduo
{
namespace net
{

///
/// IO Multiplexing with epoll(4).
///
class EPollPoller : public Poller
{
 public:
  EPollPoller(EventLoop* loop);
  virtual ~EPollPoller();

  virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels);
  virtual void updateChannel(Channel* channel);
  virtual void removeChannel(Channel* channel);

 private:
	 //�¼��������г���
  static const int kInitEventListSize = 16;
	//
  static const char* operationToString(int op);
	//�����¼������Ѵ����¼����channels
  void fillActiveChannels(int numEvents,
                          ChannelList* activeChannels) const;
  //�����¼�
  void update(int operation, Channel* channel);

  typedef std::vector<struct epoll_event> EventList;

  //epfd
  int epollfd_;
  //�¼�����
  EventList events_;
};

}
}
#endif  // MUDUO_NET_POLLER_EPOLLPOLLER_H
