#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_LISTBOX_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_LISTBOX_HPP

#include <vector>
#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/UserInterface/Button.hpp>
#include <KyraGameFramework/UserInterface/VerticalLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/RenderDeviceGL/RectangleShape.hpp>

namespace kyra {
	namespace ui {
		
		class ListBox : public Widget {
			
			VerticalLayout::Ptr m_VerticalLayout;
			IRenderDevice::Ptr  m_RenderDevice;
			IRectangleShape::Ptr m_RectangleShape;
			
			IFont::Ptr m_Font;
			float m_RowHeight;
			
			ListBox(IFont::Ptr font, IRenderDevice::Ptr renderDevice) : Widget(renderDevice), m_RowHeight(20.0f) {
				m_VerticalLayout = VerticalLayout::create(renderDevice);
				m_RenderDevice = renderDevice;
				m_Font = font;
				m_RectangleShape = kyra::IRectangleShape::Ptr( new kyra::RectangleShape() );
				m_RectangleShape->create(*renderDevice);
				m_RectangleShape->setSize( kyra::math::Vector2<float>(100.0f,100.0f) );
				m_RectangleShape->setPosition( kyra::math::Vector3<float>(0.f,0.f,0.0f));
				m_RectangleShape->setColor( kyra::math::Vector4<float>(1.0f,1.0f,0.0f,0.5f));
			}
			
			public:
			
			~ListBox() {
				
			}
			
			typedef std::shared_ptr<ListBox> Ptr;
			
			static Ptr create(IFont::Ptr font, IRenderDevice::Ptr renderDevice) {
				return Ptr(new ListBox(font, renderDevice));
			}
			
			void setPosition(const math::Vector3<float>& vec) final {
				m_RectangleShape->setPosition(vec);
				m_VerticalLayout->setPosition(vec);
			}
			
			void setSize(const math::Vector2<float>& vec) final {
				m_RectangleShape->setSize(vec);
				m_VerticalLayout->setSize( math::Vector2<float>(vec.get(0), m_VerticalLayout->getSize().get(1)) );
			}
			
			math::Vector2<float> getSize() const final {
				return math::Vector2<float>();
			}
			
			bool contains(const math::Vector2<float>& vec) const final {
				return false;
			}
			
			bool hasChildElements() const {
				return false;
			}
			
			Widget::Ptr getHoveredChild(const math::Vector2<float>& vec) final {
				return Widget::Ptr(nullptr);
			}
			
			
			void setRowHeight(float height) {
				m_RowHeight = height;
				m_VerticalLayout->setSize( kyra::math::Vector2<float>(m_VerticalLayout->getSize().get(0), m_RowHeight * (float)(m_VerticalLayout->getChildCount())));
			}
			
			void add(int id, const std::string& text) {
				Button::Ptr button = Button::create(m_Font, text, m_RenderDevice);
				button->setColor( math::Vector4<float>(0.3f,0.3f,1.0f,0.5f));
				m_VerticalLayout->add(button);
			   	m_VerticalLayout->setSize( kyra::math::Vector2<float>(m_VerticalLayout->getSize().get(0), m_RowHeight * (float)(m_VerticalLayout->getChildCount())));
			}
			
			void add(Widget::Ptr widget) {
				m_VerticalLayout->add(widget);
			}
			
			void draw(IRenderDevice& renderDevice) final {
				renderDevice.draw(m_RectangleShape);
				renderDevice.draw(m_VerticalLayout);
			}			
			
		};
	}
}

#endif