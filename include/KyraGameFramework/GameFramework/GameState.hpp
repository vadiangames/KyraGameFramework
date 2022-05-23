#ifndef KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATE_HPP
#define KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATE_HPP

#include <memory>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>


namespace kyra {

	class GameStateOwner;
	class GameState : public IDrawable {

		public:
		GameState() {}
		virtual ~GameState() {}
	
		typedef std::shared_ptr<GameState> Ptr;
		
		virtual void pause() {
			
		}
		
		virtual void resume() {
			
		}
		
		virtual void init(IRenderDevice::Ptr renderDevice) {
			
		}
		
		virtual void update(double dt, GameStateOwner* owner) {
			
		}
	
	};


}

#endif