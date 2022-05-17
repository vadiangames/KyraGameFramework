#ifndef KYRAGAMEFRAMEWORK_THREADING_TASK_HPP
#define KYRAGAMEFRAMEWORK_THREADING_TASK_HPP

#include <atomic>
#include <functional>

namespace kyra {
	namespace threading {
		class Task {
	
			std::atomic<bool> m_IsFinished;
			std::function<void()> m_Function;
		
			public:
			Task() : m_IsFinished(true) {
			
			}
	
			Task(std::function<void()> func) : m_IsFinished(true), m_Function(func) {
			
			}
	
			~Task() {

			}
	
			void init() {
				m_IsFinished = false;
			}
	
			bool isFinished() const {
				return m_IsFinished;
			}
		
			static void runFunc(Task* task, Thread* thread) {
				task->m_Function();
				task->m_IsFinished = true;
			}
		};
	}
}

#endif