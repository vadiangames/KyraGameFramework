#ifndef KYRAGAMEFRAMEWORK_THREADING_TASK_HPP
#define KYRAGAMEFRAMEWORK_THREADING_TASK_HPP

#include <KyraGameFramework/Threading/DLL.hpp>
#include <atomic>
#include <functional>

namespace kyra {
	namespace threading {
		class Thread;
		class KYRA_THREADING_API Task {
	
			std::atomic<bool> m_IsFinished;
			std::function<void()> m_Function;
		
			public:
			Task();
			explicit Task(std::function<void()> func);
			~Task();
	
			void init();
	
			bool isFinished() const;
		
			static void runFunc(Task* task);
		};
	}
}

#endif