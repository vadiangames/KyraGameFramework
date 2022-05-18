#ifndef KYRAGAMEFRAMEWORK_THREADING_THREAD_HPP
#define KYRAGAMEFRAMEWORK_THREADING_THREAD_HPP

#include <KyraGameFramework/Threading/Task.hpp>
#include <thread>

namespace kyra {
	
	namespace threading {
		
		/// A thread is used to run parallell tasks
		class KYRA_THREADING_API Thread {
			
			std::thread m_Thread;	/// The operating system thread to run the task
			Task* m_Task;			/// The task to run
			
			public:
			Thread();

			~Thread();
			
			void run(Task& task);
			
			void wait();
			
			/// Returns true if the task if finished or if there was no task to run
			bool isFinished();
			
		};

	}
}

#endif