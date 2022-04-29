#ifndef KYRAGAMEFRAMEWORK_ANIMATION_POSITIONANIMATION_HPP
#define KYRAGAMEFRAMEWORK_ANIMATION_POSITIONANIMATION_HPP

#include <KyraGameFramework/Animation/IAnimation.hpp>

namespace kyra {
		
	template<class T>
	class PositionAnimation : public IAnimation {
		
		std::shared_ptr<T> m_Target;
		glm::vec3 m_From;
		glm::vec3 m_To;
		float m_Runtime;
		bool m_Loop;
		bool m_IsRunning;
		float m_Time;
		
		public:
		PositionAnimation() : m_Target(nullptr), m_IsRunning(false) {}
		~PositionAnimation() {}
		
		void setTarget(std::shared_ptr<T> target) {
			m_Target = target;
		}
		
		void set( const glm::vec3& from, const glm::vec3& to, float runtime, bool loop) {
			m_From = from;
			m_To = to;
			m_Runtime = runtime;
			m_Time = 0;
			m_Loop = loop;
		}
		
		void start() {
			m_IsRunning = true;
		}
		
		void stop() {
			m_IsRunning = false;
		}
		
		void update(float dt) {
			if(m_IsRunning && m_Target) {
				m_Time += dt;
				if(m_Time > m_Runtime) {
					if(m_Loop) {
						m_Time -= m_Runtime;
					} else {
						m_IsRunning = false;
						m_Target->setPosition(m_To);
						return;
					}
				}
				glm::vec3 difference = (m_To - m_From);
				glm::vec3 targetPosition = m_From + ((m_To - m_From) * ( m_Time / m_Runtime));
				m_Target->setPosition( targetPosition );
			}
		}
		
	};
	
}

#endif