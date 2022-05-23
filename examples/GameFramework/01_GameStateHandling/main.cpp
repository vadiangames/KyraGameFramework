
#include <KyraGameFramework/GameFramework/GameState.hpp>
#include <KyraGameFramework/GameFramework/Game.hpp>
#include <iostream>

class MyGameState1;
class MyGameState2 : public kyra::GameState {
	
	public:
	MyGameState2() {}
	~MyGameState2() {}

	virtual void update(double dt, kyra::GameStateOwner* owner);
	
	virtual void draw(kyra::IRenderDevice& renderDevice) final {
		
	}

	
};

class MyGameState1 : public kyra::GameState {
	
	public:
	MyGameState1() {}
	~MyGameState1() {}
	
	virtual void update(double dt, kyra::GameStateOwner* owner) {
		std::cout << "MyGameState1::update" << std::endl; 
		owner->set( kyra::GameState::Ptr(new MyGameState2()));
	}
	
	virtual void draw(kyra::IRenderDevice& renderDevice) final {
		
	}
		
};

void MyGameState2::update(double dt, kyra::GameStateOwner* owner) {
	std::cout << "MyGameState2::update" << std::endl; 
	owner->set( kyra::GameState::Ptr(new MyGameState1()));
}

class MyGame : public kyra::Game {
	
	public:
	MyGame() {}
	~MyGame() {}
	
};

int main(int argc, char** argv) {
	
	kyra::WindowSettings settings;
		settings.width = 1024;
		settings.height = 768;
		settings.title = L"01_GameStateHandling";
		
	MyGame().run(settings, kyra::GameState::Ptr(new MyGameState1()));
	
	return 0;
}