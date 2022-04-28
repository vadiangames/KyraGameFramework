#ifndef KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATE_HPP
#define KYRAGAMEFRAMEWORK_GAMEFRAMEWORK_GAMESTATE_HPP

#include <memory>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

namespace kyra {

	class GameState : public IDrawable {

		public:
		GameState() {}
		virtual ~GameState() {}
	
		typedef std::shared_ptr<GameState> Ptr;
		
		virtual void init(IRenderDevice::Ptr renderDevice) {
			
		}
	
	};


}

#endif