
#include <KyraGameFramework/GameFramework/GameState.hpp>
#include <KyraGameFramework/GameFramework/Game.hpp>
#include <KyraGameFramework/UserInterface.hpp>


class MyGameState : public kyra::GameState {
	
	kyra::ui::Context m_Context;
	
	kyra::ui::Button::Ptr m_Button;
	
	kyra::ITexture::Ptr m_ImageButtonTexture;
	kyra::ui::ImageButton::Ptr m_ImageButton;
	
	kyra::ui::EditBox::Ptr m_EditBox;
	
	kyra::ui::Label::Ptr m_ButtonLabel;
	kyra::ui::Label::Ptr m_ImageButtonLabel;
	kyra::ui::Label::Ptr m_EditBoxLabel;
	
	public:
	MyGameState() {}
	~MyGameState() {}
	
	virtual void init(kyra::IRenderDevice::Ptr renderDevice) {
		
		kyra::IFont::Ptr font = kyra::IFont::Ptr(new kyra::Font());
		font->loadFromFile("Antonio-Regular.ttf", 14);
		
		kyra::ITexture::Ptr imageButtonTexture = renderDevice->createTexture("Button.png");
			
		m_Button = kyra::ui::Button::create(font, "Hello World", renderDevice);
		m_Button->setSize( kyra::math::Vector2<float>(100,25) );
		m_Button->setPosition( kyra::math::Vector3<float>(150,0,0));
		m_Button->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));
		m_Button->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		m_ImageButton = kyra::ui::ImageButton::create(font, "Hello World 2", imageButtonTexture, renderDevice);
		m_ImageButton->setPosition( kyra::math::Vector3<float>(150,30,0));
		
		m_ButtonLabel = kyra::ui::Label::create(font, "A simple button: ", renderDevice);
		m_ButtonLabel->setPosition( kyra::math::Vector3<float>(0,0,0) );
		
		m_ImageButtonLabel = kyra::ui::Label::create(font, "An image button: ", renderDevice);
		m_ImageButtonLabel->setPosition( kyra::math::Vector3<float>(0,30,0) );
		
		
		m_EditBox = kyra::ui::EditBox::create(font, "Hello World", renderDevice);
		m_EditBox->setPosition(kyra::math::Vector3<float>(100,60,0));
		m_EditBox->setSize(kyra::math::Vector2<float>(150,25));
		m_EditBox->setColor(kyra::math::Vector4<float>(0.4,0.4,0.4,1));
		
		
		m_EditBoxLabel = kyra::ui::Label::create(font, "EditBox: ", renderDevice);
		m_EditBoxLabel->setPosition( kyra::math::Vector3<float>(0,60,0) );
		
		
		m_Context.add(m_Button);
		m_Context.add(m_ButtonLabel);
		m_Context.add(m_ImageButton);
		m_Context.add(m_ImageButtonLabel);
		m_Context.add(m_EditBoxLabel);
		m_Context.add(m_EditBox);
		
		renderDevice->getWindow().addListener(&m_Context);
	}
	
	virtual void draw(kyra::IRenderDevice& device) final {
		for(auto& widget : m_Context) {
			device.draw(widget);
		}
	}
	
};

int main(int argc, char** argv) {
	
	kyra::WindowSettings settings;
	settings.width = 800;
	settings.height = 600;
	settings.title = L"Kyra::UserInterface::Widgets";
	
	kyra::Game().run(settings, kyra::GameState::Ptr(new MyGameState()) );
	
	return 0;
}