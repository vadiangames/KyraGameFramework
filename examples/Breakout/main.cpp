
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class BreakoutGame : public kyra::SystemEventListener {
	
	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	kyra::Program	m_SpriteShader;
	kyra::Program	m_ParticleShader;
	kyra::Program	m_PostProcessingShader;
	
	kyra::Texture   m_Background;
	kyra::Texture   m_AwesomeFace;
	kyra::Texture   m_Block;
	kyra::Texture   m_Block_Solid;
	kyra::Texture   m_Paddle;
	kyra::Texture   m_Particle;
	kyra::Texture   m_PowerUp_Speed;
	kyra::Texture   m_PowerUp_Sticky;
	kyra::Texture   m_PowerUp_Increase;
	kyra::Texture   m_PowerUp_Confuse;
	kyra::Texture   m_PowerUp_Chaos;
	kyra::Texture   m_PowerUp_PassThrough;
	
	public:
	BreakoutGame() {
		
	}
	
	~BreakoutGame() {
	
	}
	
	void init(kyra::RenderDeviceGL& renderDevice) {
		//Load Shaders
		m_SpriteShader.linkFromFile("./Shaders/Sprite.vs", "./Shaders/Sprite.fs");
		m_ParticleShader.linkFromFile("./Shaders/Particle.vs", "./Shaders/Particle.fs");
		m_PostProcessingShader.linkFromFile("./Shaders/PostProcessing.vs","./Shaders/PostProcessing.fs");
	
		//ConfigureShaders
		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.f, 0.0f);
		m_SpriteShader.setInteger("sprite",0);
		m_SpriteShader.setMatrix4("projection", projection);
		m_ParticleShader.setInteger("sprite",0);
		m_ParticleShader.setMatrix4("projection", projection);
				
		//Load Textures
		//TODO: This file fails to load with an error
		m_Background.loadFromFile("./Textures/background.jpg");
		m_AwesomeFace.loadFromFile("./Textures/awesomeface.png");
		//TODO: This file fails to load with an error
		//m_Block.loadFromFile("./Textures/block.png");
		//TODO: This file fails to load with an error
		//m_Block_Solid.loadFromFile("./Textures/block_solid.png");
		m_Paddle.loadFromFile("./Textures/paddle.png");
		m_Particle.loadFromFile("./Textures/particle.png");
		m_PowerUp_Speed.loadFromFile("./Textures/powerup_speed.png");
		m_PowerUp_Sticky.loadFromFile("./Textures/powerup_sticky.png");
		m_PowerUp_Increase.loadFromFile("./Textures/powerup_increase.png");
		m_PowerUp_Confuse.loadFromFile("./Textures/powerup_confuse.png");
		m_PowerUp_Chaos.loadFromFile("./Textures/powerup_chaos.png");
		m_PowerUp_PassThrough.loadFromFile("./Textures/powerup_passthrough.png");
	}
	
	virtual void onClose() {
		m_Window.close();
	}
	
	void run() {
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"Breakout";
		
		if(m_Window.create(windowSettings)) {
			m_Window.addListener(this);
			if(m_Renderer.create(m_Window)) {
				if(kyra::GLExtensionLoader::init() == false) {
					return;
				}
				init(m_Renderer);
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
					m_Renderer.display();
				}
			} else {
				std::cout << "[ERROR] Can not create renderer" << std::endl;
			}
		} else {
			std::cout << "[ERROR] Can not create window" << std::endl;
		}
	}

	
};

int main(int argc, char** argv) {
	
	BreakoutGame().run();
	return 0;
}