#include <KyraGameFramework/Threading/Task.hpp>

namespace kyra {
	namespace threading {
		
		KYRA_THREADING_API Task::Task() : m_IsFinished(true) {
			
		}
	
		KYRA_THREADING_API Task::Task(std::function<void()> func) : m_IsFinished(true), m_Function(func) {
			
		}
	
		KYRA_THREADING_API Task::~Task() {

		}
	
		void KYRA_THREADING_API Task::init() {
			m_IsFinished = false;
		}
	
		bool KYRA_THREADING_API Task::isFinished() const {
			return m_IsFinished;
		}
		
		void KYRA_THREADING_API Task::runFunc(Task* task) {
			task->m_IsFinished = false;
			task->m_Function();
			task->m_IsFinished = true;
		}
	}
}