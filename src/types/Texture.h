#pragma once

#include "base/Base.h"

#include <string>

#include "base/ObjectLink.h"
#include "Color.h"

namespace types {

CLASS( Texture, base::Base )
	Texture( const std::string& name, const size_t width, const size_t height );
	virtual ~Texture();
	
	const std::string m_name;
	size_t m_width = 0;
	size_t m_height = 0;
	float m_aspect_ratio = 0;
	unsigned char m_bpp = 0;
	unsigned char *m_bitmap = nullptr;
	size_t m_bitmap_size = 0;
	
	bool m_is_tiled = false;

	base::ObjectLink *m_graphics_object = nullptr;
	
	void Resize( const size_t width, const size_t height );
	
	void SetPixel( const size_t x, const size_t y, const Color::rgba_t& rgba );
	void SetPixel( const size_t x, const size_t y, const Color& color );
	void Rectangle( const size_t x1, const size_t y1, const size_t x2, const size_t y2, const Color color );
	
	enum add_mode_t {
		AM_COPY, // copy every pixel from dest to source
		AM_MERGE, // copy every non-transparent pixel from dest to source
	};
	
	typedef uint8_t rotate_t;
	static const rotate_t ROTATE_0 = 0;
	static const rotate_t ROTATE_90 = 1;
	static const rotate_t ROTATE_180 = 2;
	static const rotate_t ROTATE_270 = 3;
	/**
	 * 
	 * @param source - source Texture object
	 * @param mode - method of how (and when) pixels from source are applied to dest, see add_mode_t
	 * @param x1 - source image part left boundary
	 * @param y1 - source image part top boundary
	 * @param x2 - source image part right boundary
	 * @param y2 - source image part bottom boundary
	 * @param dest_x - (optional) where to start copying to (x coordinate), default 0 (at beginning)
	 * @param dest_y - (optional) where to start copying to (y coordinate), default 0 (at beginning)
	 * @param rotate - (optional) apply as rotated or not, default 0 ( not rotated ). see rotate_t
	 */
	void AddFrom( const types::Texture* source, const add_mode_t mode, const size_t x1, const size_t y1, const size_t x2, const size_t y2, const size_t dest_x = 0, const size_t dest_y = 0, const rotate_t rotate = 0 );
	
	void Rotate();
	void FlipV();
	//void FlipH(); // TODO
	void SetAlpha(const float alpha);
	void SetContrast(const float contrast);
};

} /* namespace types */
