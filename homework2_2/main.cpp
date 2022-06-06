#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;

condition_variable condition_;
mutex mutex_;
bool flag = false;

void Ping(int ping_pong_count)
{
  unique_lock<mutex> lock(mutex_);
  for(int i = 0; i < ping_pong_count; ++i)
  {
    condition_.wait(lock,[]{ return flag ? true : false;});
    cout<<"Ping";
    flag = !flag;
    condition_.notify_one();
   }
}

void Pong(int ping_pong_count)
{
  unique_lock<mutex> lock(mutex_);
  for(int i = 0; i < ping_pong_count; ++i)
  {
    condition_.wait(lock,[]{ return !flag ? true : false;});
    cout << "Pong";
    flag = !flag;
    condition_.notify_one();
  }
}

int main()
{
  int ping_pong_count = 6;
  thread thread_1(Ping, ping_pong_count);
  thread thread_2(Pong, ping_pong_count);
  thread_1.join();
  thread_2.join();

  return 0;
}
