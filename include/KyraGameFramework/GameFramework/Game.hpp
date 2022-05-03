#ifndef KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAME_HPP
#define KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAME_HPP

#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>

#include <KyraGameFramework/GameFramework/GameState.hpp>

#include <iostream>
#include <chrono>
#include <thread>

namespace kyra {

	class Game : public SystemEventListener {
		
		kyra::Window m_Window;
		kyra::IRenderDevice::Ptr m_RenderDevice;
		
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
		
		public:
		Game() {}
		virtual ~Game() {}
	
		virtual void onClose() override {
			m_Window.close();
		}
		
		bool run(const kyra::WindowSettings& settings, GameState::Ptr rootState) {
				
				//Create window
				std::cout << "Create window" << std::endl;
				if(!m_Window.create(settings)) {
					return false;
				}
				m_Window.addListener(this);
				
				//Create Renderer
				m_RenderDevice = kyra::IRenderDevice::Ptr(new RenderDeviceGL());
				if(!m_RenderDevice->create(m_Window)) {
					return false;
				}
				
				rootState->init(m_RenderDevice);
				
				//Main Loop
				
				std::chrono::duration<double> frameTime = std::chrono::duration<double>( 1.f / 60.f);
				m_Start = std::chrono::high_resolution_clock::now();
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_RenderDevice->clear();
						m_RenderDevice->draw(rootState);
					m_RenderDevice->display();
					m_End = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double> duration(m_End-m_Start);
					m_Start = std::chrono::high_resolution_clock::now();
					rootState->update( duration.count() );
					if( duration < frameTime) {
						std::this_thread::sleep_for(frameTime - duration);
					}
				}
				return true;
		}
		
	};


}

#endif