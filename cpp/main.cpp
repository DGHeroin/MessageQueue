#include <iostream>
using namespace std;

#include <list>
#include <condition_variable>
#include <assert.h>

template<typename T>
class MessageQueue
{
public:
	MessageQueue() : m_mutex(), m_condvar(), m_queue()
	{}
	~MessageQueue(){}

	void Put(const T& task){
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push_back(task);
		}
		m_condvar.notify_one();
	}

	T Take(){
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condvar.wait(lock, [this]{return !m_queue.empty();});
		assert(m_queue && "block queue is null");
		T front(m_queue.front() );
		m_queue.pop_front();

		return front;
	}
	size_t Size(){
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.size();
	}
private:
	std::mutex m_mutex;
	std::list<T> m_queue;
	std::condition_variable m_condvar;
};

#include <thread>
int main(int argc, char const *argv[])
{
	cout << "Hello World!" << endl;
	MessageQueue<char> mq;

	auto th1 = new thread([](MessageQueue<char>*ptr){
		while(1) {
			char val = ptr->Take();
			cout << val << endl;
		}
	}, &mq);

	auto th2 = new thread([](MessageQueue<char>*ptr){
		while(1) {
			char val;
			scanf("%c", &val);
			cout << "get a enter" << val << endl;
			ptr->Put(val);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}, &mq);

	th1->join();
	th2->join();




	return 0;
}
