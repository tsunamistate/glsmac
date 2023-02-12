#pragma once

#include "UIContainer.h"

#include "Panel.h"
#include "Label.h"

#include "Surface.h"

namespace ui {
namespace object {

CLASS( Section, UIContainer )

	Section( const std::string& class_name = "" );
		
	void SetTitleText( const std::string& title_text );

	virtual void AddChild( UIObject *object );
	virtual void RemoveChild( UIObject *object );
	
	virtual void Create();
	virtual void Destroy();

protected:
	void ApplyStyle();
	
	std::string m_title_text = "";
	
	Panel* m_frame = nullptr;
		Panel* m_titlebar = nullptr;
			Label* m_titlelabel = nullptr;
		Panel* m_body = nullptr;
	
		// TODO: style attribute scopes/inheritance
	const std::unordered_map< Style::attribute_type_t, Style::attribute_type_t > m_forwarded_style_attributes = {
		{ Style::A_BORDER_WIDTH, Style::A_BORDER_WIDTH },
		{ Style::A_HEADER_TEXTURE_BACK, Style::A_HEADER_TEXTURE_BACK },
		{ Style::A_HEADER_TEXTURE_BORDER_LEFT, Style::A_HEADER_TEXTURE_BORDER_LEFT },
		{ Style::A_HEADER_TEXTURE_BORDER_TOP, Style::A_HEADER_TEXTURE_BORDER_TOP },
		{ Style::A_HEADER_TEXTURE_BORDER_RIGHT, Style::A_HEADER_TEXTURE_BORDER_RIGHT },
		{ Style::A_HEADER_TEXTURE_BORDER_BOTTOM, Style::A_HEADER_TEXTURE_BORDER_BOTTOM },
		{ Style::A_HEADER_FONT, Style::A_HEADER_FONT },
		{ Style::A_HEADER_TEXTCOLOR, Style::A_HEADER_TEXTCOLOR },
		{ Style::A_HEADER_TEXTALIGN, Style::A_HEADER_TEXTALIGN },
		{ Style::A_TEXTURE_BACK, Style::A_TEXTURE_BACK },
		{ Style::A_TEXTURE_BORDER_LEFT, Style::A_TEXTURE_BORDER_LEFT },
		{ Style::A_TEXTURE_BORDER_CORNER_LT, Style::A_TEXTURE_BORDER_CORNER_LT },
		{ Style::A_TEXTURE_BORDER_TOP, Style::A_TEXTURE_BORDER_TOP },
		{ Style::A_TEXTURE_BORDER_CORNER_RT, Style::A_TEXTURE_BORDER_CORNER_RT },
		{ Style::A_TEXTURE_BORDER_RIGHT, Style::A_TEXTURE_BORDER_RIGHT },
		{ Style::A_TEXTURE_BORDER_CORNER_RB, Style::A_TEXTURE_BORDER_CORNER_RB },
		{ Style::A_TEXTURE_BORDER_BOTTOM, Style::A_TEXTURE_BORDER_BOTTOM },
		{ Style::A_TEXTURE_BORDER_CORNER_LB, Style::A_TEXTURE_BORDER_CORNER_LB },
		{ Style::A_HEADER_HEIGHT, Style::A_HEADER_HEIGHT },
	};
	
	const std::unordered_map< Style::attribute_type_t, Style::attribute_type_t > m_forwarded_header_style_attributes = {
		{ Style::A_HEADER_TEXTURE_BACK, Style::A_TEXTURE_BACK },
		{ Style::A_HEADER_TEXTURE_BORDER_LEFT, Style::A_TEXTURE_BORDER_LEFT },
		{ Style::A_HEADER_TEXTURE_BORDER_TOP, Style::A_TEXTURE_BORDER_TOP },
		{ Style::A_HEADER_TEXTURE_BORDER_RIGHT, Style::A_TEXTURE_BORDER_RIGHT },
		{ Style::A_HEADER_TEXTURE_BORDER_BOTTOM, Style::A_TEXTURE_BORDER_BOTTOM },
		{ Style::A_HEADER_FONT, Style::A_HEADER_FONT },
		{ Style::A_HEADER_TEXTCOLOR, Style::A_HEADER_TEXTCOLOR },
		{ Style::A_HEADER_TEXTALIGN, Style::A_HEADER_TEXTALIGN },
		{ Style::A_HEADER_HEIGHT, Style::A_HEIGHT },
	};
	
	const std::unordered_map< Style::attribute_type_t, Style::attribute_type_t > m_forwarded_header_label_style_attributes = {
		{ Style::A_HEADER_FONT, Style::A_FONT },
		{ Style::A_HEADER_TEXTCOLOR, Style::A_TEXTCOLOR },
		{ Style::A_HEADER_TEXTALIGN, Style::A_TEXTALIGN },
	};
};


}
}
