#ifndef KYRAGAMEFRAMEWORK_THREADING_THREAD_HPP
#define KYRAGAMEFRAMEWORK_THREADING_THREAD_HPP

#include <KyraGameFramework/Threading/Task.hpp>

namespace kyra {
	
	namespace threading {
		
		/// A thread is used to run parallell tasks
		class Thread {
			
			std::thread m_Thread;	/// The operating system thread to run the task
			Task* m_Task;			/// The task to run
			
			public:
			Thread() : m_Task(nullptr) {

			}

			~Thread() {
				/// Check if the thread runs in the background, we have to join it if it runs
				if(m_Thread.joinable()) {
					m_Thread.join();
				}
			}
			
			void run(Task& task) {
				/// Initialise the task und run it
				m_Task = &task;
				m_Task->init();
				m_Thread = std::thread(Task::runFunc,m_Task);
			}
			
			void wait() {
				/// Wait for the end of the task
				if(m_Thread.joinable()) {
					m_Thread.join();
				}
			}
			
			/// Returns true if the task if finished or if there was no task to run
			bool isFinished() {
				if(m_Task) {
					return m_Task->isFinished();
				}
				return true;
			}
			
		};

	}
}

#endif