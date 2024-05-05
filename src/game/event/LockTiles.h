#pragma once

#include "TileLocksEvent.h"

#include "game/map/Tile.h"

namespace game {
namespace event {

class LockTiles : public TileLocksEvent {
public:
	LockTiles(
		const size_t initiator_slot,
		const map::Tile::tile_positions_t& tile_positions,
		const size_t lock_owner_slot
	);

	const std::string* Validate( Game* game ) const override;
	const gse::Value Apply( game::Game* game ) const override;

private:
	friend class Event;

	static void Serialize( types::Buffer& buf, const LockTiles* event );
	static LockTiles* Unserialize( types::Buffer& buf, const size_t initiator_slot );

private:
	const size_t m_lock_owner_slot;
};

}
}
