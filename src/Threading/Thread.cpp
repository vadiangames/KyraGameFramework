#include <KyraGameFramework/Threading/Thread.hpp>

namespace kyra {
	
	namespace threading {
		
		KYRA_THREADING_API Thread::Thread() : m_Task(nullptr) {

		}

		KYRA_THREADING_API Thread::~Thread() {
			/// Check if the thread runs in the background, we have to join it if it runs
			if(m_Thread.joinable()) {
				m_Thread.join();
			}
		}
			
		void KYRA_THREADING_API Thread::run(Task& task) {
			/// Initialise the task und run it
			m_Task = &task;
			m_Task->init();
			m_Thread = std::thread(Task::runFunc,m_Task);
		}
			
		void KYRA_THREADING_API Thread::wait() {
			/// Wait for the end of the task
			if(m_Thread.joinable()) {
				m_Thread.join();
			}
		}
			
		/// Returns true if the task if finished or if there was no task to run
		bool KYRA_THREADING_API Thread::isFinished() {
			if(m_Task) {
				return m_Task->isFinished();
			}
			return true;
		}
				
	}
}
