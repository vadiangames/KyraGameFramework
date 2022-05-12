#ifndef KYRAGAMEFRAMEWORK_ANIMATION_POSITIONANIMATION_HPP
#define KYRAGAMEFRAMEWORK_ANIMATION_POSITIONANIMATION_HPP

#include <KyraGameFramework/Animation/IAnimation.hpp>

namespace kyra {
		
	template<class T>
	class PositionAnimation : public IAnimation {
		
		std::shared_ptr<T> m_Target;
		kyra::math::Vector3<float> m_From;
		kyra::math::Vector3<float> m_To;
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
		
		void set( const kyra::math::Vector3<float>& from, const kyra::math::Vector3<float>& to, float runtime, bool loop) {
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
				kyra::math::Vector3<float> targetPosition = m_From + ((m_To - m_From) * ( m_Time / m_Runtime));
				m_Target->setPosition( targetPosition );
			}
		}
		
	};
	
}

#endif