#ifndef KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATEOWNER_HPP
#define KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATEOWNER_HPP

#include <vector>
#include <KyraGameFramework/GameFramework/GameState.hpp>

namespace kyra {

	class GameStateOwner {

		std::vector<GameState::Ptr> m_States;

		public:
		GameStateOwner() {}
		virtual ~GameStateOwner() {}
		
		virtual void onStateChange(GameState::Ptr oldState, GameState::Ptr newState) = 0;
	
		void push(GameState::Ptr state) {
			if(!m_States.empty()) {
				m_States.back()->pause();
			}
			m_States.push_back(state);
		}
		
		void set(GameState::Ptr state) {
			if(!m_States.empty()) {
				onStateChange(m_States.back(), state);
				m_States.pop_back();
			} else {
				onStateChange(GameState::Ptr(nullptr), state);
			}
			m_States.push_back(state);
		}
		
		void pop(){
			if(!m_States.empty()) {
				m_States.pop_back();
			}
			if(!m_States.empty()) {
				m_States.back()->resume();
			}
		}
		
		bool hasActiveState() {
			return m_States.size() > 0;
		}
		
		GameState::Ptr getActive() { 
			return m_States.back(); 
		}
		
		std::vector<GameState::Ptr> getAllActive() { 
			return m_States; 
		}
	
	};


}

#endif