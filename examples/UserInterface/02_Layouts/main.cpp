
#include <KyraGameFramework/GameFramework/GameState.hpp>
#include <KyraGameFramework/GameFramework/Game.hpp>
#include <KyraGameFramework/UserInterface.hpp>


class MyGameState : public kyra::GameState {
	
	kyra::ui::Context m_Context;
	
	kyra::ui::Button::Ptr m_Button1;
	kyra::ui::Button::Ptr m_Button2;
	kyra::ui::Button::Ptr m_Button3;
	
	kyra::ui::Button::Ptr m_Button4;
	kyra::ui::Button::Ptr m_Button5;
	kyra::ui::Button::Ptr m_Button6;
	
	
	kyra::ui::VerticalLayout::Ptr m_VerticalLayout;
	
	kyra::ui::HorizontalLayout::Ptr m_HorizontalLayout;
	
	public:
	MyGameState() {}
	~MyGameState() {}
	
	virtual void init(kyra::IRenderDevice::Ptr renderDevice) {
		
		kyra::IFont::Ptr font = kyra::IFont::Ptr(new kyra::Font());
		font->loadFromFile("Antonio-Regular.ttf", 14);
		
		m_VerticalLayout = kyra::ui::VerticalLayout::create(renderDevice);
		m_HorizontalLayout = kyra::ui::HorizontalLayout::create(renderDevice);
		
		m_Button1 = kyra::ui::Button::create(font, "Hello World", renderDevice);
		m_Button1->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));
		m_Button1->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button1->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button1->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button1->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		m_Button2 = kyra::ui::Button::create(font, "Button2", renderDevice);
		m_Button2->setColor(kyra::math::Vector4<float>(0.1,0.3,0.5,1));
		m_Button2->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button2->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button2->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button2->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		m_Button3 = kyra::ui::Button::create(font, "Button3", renderDevice);
		m_Button3->setColor(kyra::math::Vector4<float>(0.4,0.3,0.2,1));
		m_Button3->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button3->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button3->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button3->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );


		m_Button4 = kyra::ui::Button::create(font, "Button4", renderDevice);
		m_Button4->setColor(kyra::math::Vector4<float>(0.5,0.2,0.1,1));
		m_Button4->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button4->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button4->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button4->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		m_Button5 = kyra::ui::Button::create(font, "Button5", renderDevice);
		m_Button5->setColor(kyra::math::Vector4<float>(0.1,0.3,0.4,1));
		m_Button5->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button5->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button5->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button5->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		m_Button6 = kyra::ui::Button::create(font, "Button6", renderDevice);
		m_Button6->setColor(kyra::math::Vector4<float>(0.4,0.3,0.3,1));
		m_Button6->bind(kyra::ui::WidgetEvent::ON_HOVER, [&](){m_Button6->setColor(kyra::math::Vector4<float>(0.75,0.5,0.75,1));} );
		m_Button6->bind(kyra::ui::WidgetEvent::ON_LEAVE, [&](){m_Button6->setColor(kyra::math::Vector4<float>(0.5,0.2,0.5,1));} );
		
		
		m_VerticalLayout->setSize(kyra::math::Vector2<float>(100,100));
		m_VerticalLayout->setPosition(kyra::math::Vector3<float>(10,10,0));
		m_VerticalLayout->add(m_Button1);
		m_VerticalLayout->add(m_Button2);
		m_VerticalLayout->add(m_Button3);
		
		
		m_HorizontalLayout->setSize(kyra::math::Vector2<float>(300,100));
		m_HorizontalLayout->setPosition(kyra::math::Vector3<float>(100,10,0));
		m_HorizontalLayout->add(m_Button4);
		m_HorizontalLayout->add(m_Button5);
		m_HorizontalLayout->add(m_Button6);
		
		
		
		m_Context.add(m_VerticalLayout);
		m_Context.add(m_HorizontalLayout);
		
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
	settings.title = L"Kyra::UserInterface::Layouts";
	
	kyra::Game().run(settings, kyra::GameState::Ptr(new MyGameState()) );
	
	return 0;
}