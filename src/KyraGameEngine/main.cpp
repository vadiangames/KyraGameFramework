
#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/PluginSystem.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/Core/Log.hpp>

#include <nlohmann/json.hpp>

#include <fstream>

namespace KyraGameEngine {
	const std::string ConfigurationFile = "WindowSettings.json";
}

class KyraGameEngineApp : public kyra::SystemEventListener {
	
	kyra::Window m_Window;
	kyra::Plugin<kyra::IRenderDevice> m_RenderDeviceDLL;
	
	void loadConfig(const std::filesystem::path& path, kyra::WindowSettings& windowSettings) {
		
	}
	
	void saveConfig(const std::filesystem::path& path, const kyra::WindowSettings& windowSettings) {
		
	}
		
	public:
	KyraGameEngineApp() {}
	~KyraGameEngineApp() {}
	
	virtual void onClose() final {
		m_Window.close();
	}
	
	void run() {
		
		kyra::WindowSettings windowSettings;
		
		/*** LOAD CONFIGURATION FILE ***/ 
		
		//Check if WindowSettings.json exists
		if(std::filesystem::exists(std::filesystem::path(KyraGameEngine::ConfigurationFile))) {
			nlohmann::json windowSettingsJson;
			std::ifstream windowSettingsFile(KyraGameEngine::ConfigurationFile);
			windowSettingsFile >> windowSettingsJson;
			windowSettingsFile.close();
			
			windowSettings.width = windowSettingsJson["Window.Width"].get<int>();
			windowSettings.height = windowSettingsJson["Window.Height"].get<int>();
			windowSettings.title  = windowSettingsJson["Window.Title"].get<std::wstring>();		
		} else {
			windowSettings.width = 800;
			windowSettings.height = 600;
			windowSettings.title = L"KyraGameEngine";
		
			nlohmann::json windowSettingsJson;
			windowSettingsJson["Window.Width"] = windowSettings.width;
			windowSettingsJson["Window.Height"] = windowSettings.height;
			windowSettingsJson["Window.Title"] = L"KyraGameEngine";
			
			std::ofstream windowSettingsFile(KyraGameEngine::ConfigurationFile);
			windowSettingsFile << windowSettingsJson;
			windowSettingsFile.close();
		}
		
		/*** END LOAD CONFIGURATION-FILE ***/
		
	
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			kyra::PluginSystem pluginSystem;
			m_RenderDeviceDLL = pluginSystem.load<kyra::IRenderDevice>("libKyraRenderDeviceGL.dll");
			if(!m_RenderDeviceDLL.isLoaded()) {
				return;
			}
			
			kyra::IRenderDevice::Ptr renderDevice = m_RenderDeviceDLL.getInstance(); 
			renderDevice->create(m_Window);
			
			while(m_Window.isOpen()) {
				m_Window.processEvents();
				renderDevice->clear();
				renderDevice->display();
			}

		}
	}
	
};


int main(int argc, char** argv) {
	
	KyraGameEngineApp().run();
	
	
	return 0;
}