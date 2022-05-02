
#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>

#include <KyraGameFramework/Math/Vector3.hpp>


//https://learnopengl.com/Getting-started/Camera

namespace kyra {
	
	class Camera {
		
		float m_Yaw;
		float m_Pitch;
		float m_Speed;
		float m_Sensitivy;
		float m_Zoom;
		
		kyra::Vector3<float> m_Position;
		kyra::Vector3<float> m_Front;
		kyra::Vector3<float> m_Up;
		kyra::Vector3<float> m_Right;
		kyra::Vector3<float> m_WorldUp;
		
		void updateVectors() {
			/*glm::vec3 front;
			front.x = cos(glm::radians(m_Yaw) * cos(glm::radians(m_Pitch)));
			front.y = sin(glm::radians(m_Pitch));
			front.z = sin(glm::radians(m_Yaw) * cos(glm::radians(m_Pitch)));
			m_Front = glm::normalize(m_Front);
			m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
			m_Up = glm::normalize(glm::cross(m_Right, m_Front));*/
		}
		
		
		public:
		Camera() {
			m_Yaw = -90.0f;
			m_Pitch = 0.0f;
			m_Speed = 2.5f;
			m_Sensitivy = 0.1f;
			m_Zoom = 45.0f;
			updateVectors();
		}
		
		~Camera() {
			
		}
		
		//glm::mat4 getViewMatrix() {
			//return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		//}
		
		void update(float dt) {
			
		}
	
	};

}

class MyApplication : public kyra::SystemEventListener {
	
	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	virtual void onClose() {
		m_Window.close();
	}
	
	void run() {
		
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Camera Example";
		
		if(!m_Window.create(windowSettings)) {
			return;
		}
		
		m_Window.addListener(this);
		
		if(!m_Renderer.create(m_Window)) {
			return;
		}
		
		while(m_Window.isOpen()) {
			m_Window.processEvents();
			m_Renderer.clear();
			m_Renderer.display();
		}
		
	}
	
};


int main(int argc, char** argv) {
	
	MyApplication().run();
	
	return 0;
}