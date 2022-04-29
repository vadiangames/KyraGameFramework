#ifndef KYRAGAMEFRAMEWORK_ANIMATION_COLORANIMATION_HPP
#define KYRAGAMEFRAMEWORK_ANIMATION_COLORANIMATION_HPP

#include <KyraGameFramework/Animation/IAnimation.hpp>

namespace kyra {
		
	template<class T>
	class ColorAnimation : public IAnimation {
		
		std::shared_ptr<T> m_Target;
		glm::vec4 m_From;
		glm::vec4 m_To;
		float m_Runtime;
		bool m_Loop;
		bool m_IsRunning;
		float m_Time;
		
		public:
		ColorAnimation() : m_Target(nullptr), m_IsRunning(false) {}
		~ColorAnimation() {}
		
		void setTarget(std::shared_ptr<T> target) {
			m_Target = target;
		}
		
		void set( const glm::vec4& from, const glm::vec4& to, float runtime, bool loop) {
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
						m_Target->setColor(m_To);
						return;
					}
				}

				glm::vec4 difference = (m_To - m_From);
				glm::vec4 targetColor = m_From + ((m_To - m_From) * ( m_Time / m_Runtime));
				m_Target->setColor( targetColor );
			}
		}
		
	};
	
}

#endif