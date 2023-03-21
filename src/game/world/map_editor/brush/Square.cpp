#include "Square.h"

#include "game/world/map/Tile.h"
#include "game/world/World.h"

namespace game {
namespace world {
namespace map_editor {
namespace brush {

Square::Square( World* world, const MapEditor::brush_type_t type, const uint16_t width )
	: Brush( world, type )
	, m_width( width )
{
	//
}
	
const MapEditor::tiles_t Square::Draw( map::Tile* center_tile ) {
	const auto* map = m_world->GetMap()->GetTilesPtr();
	MapEditor::tiles_t tiles = {};
	tiles.reserve( m_width * m_width );
	// order is important, start with sides and move towards center for greatest effect
	// TODO: shuffle
	for ( int y = -m_width ; y <= m_width ; y++ ) {
		for ( int x = -m_width ; x <= m_width ; x ++ ) {
			if ( ( y & 1 ) != ( x & 1 ) ) {
				continue;
			}
			
			if ( x == 0 && y == 0 ) {
				continue; // center tile will be added last
			}
			if ( abs( x ) + abs( y ) > m_width ) {
				continue; // draw diagonal square instead of full square
			}
			
			if ( center_tile->coord.x >= x && center_tile->coord.y >= y ) {
				tiles.push_back( map->At( center_tile->coord.x - x, center_tile->coord.y - y ) );
			}
			if ( center_tile->coord.x <= map->GetWidth() - x - 1 && center_tile->coord.y <= map->GetHeight() - y - 1 ) {
				tiles.push_back( map->At( center_tile->coord.x + x, center_tile->coord.y + y ) );
			}
			if ( center_tile->coord.x >= x && center_tile->coord.y <= map->GetHeight() - 1 ) {
				tiles.push_back( map->At( center_tile->coord.x - x, center_tile->coord.y + y ) );
			}
			if ( center_tile->coord.x <= map->GetWidth() - x - 1 && center_tile->coord.y >= y ) {
				tiles.push_back( map->At( center_tile->coord.x + x, center_tile->coord.y - y ) );
			}
		}
	}
	tiles.push_back( center_tile );
	return tiles;
}

}
}
}
}