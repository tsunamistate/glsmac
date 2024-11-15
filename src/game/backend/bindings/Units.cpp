#include "Binding.h"

#include "gse/callable/Native.h"
#include "gse/Exception.h"
#include "gse/type/Object.h"
#include "gse/type/Array.h"
#include "gse/type/String.h"
#include "gse/type/Int.h"
#include "gse/type/Float.h"
#include "gse/type/Undefined.h"
#include "game/backend/Game.h"
#include "game/backend/slot/Slot.h"
#include "game/backend/unit/UnitManager.h"
#include "game/backend/unit/MoraleSet.h"
#include "game/backend/unit/StaticDef.h"
#include "game/backend/unit/SpriteRender.h"
#include "game/backend/unit/Unit.h"
#include "game/backend/event/DefineMorales.h"
#include "game/backend/event/DefineUnit.h"
#include "game/backend/event/SpawnUnit.h"
#include "game/backend/event/DespawnUnit.h"
#include "Bindings.h"

namespace game {
namespace backend {
namespace bindings {

const unit::morale_t GetMorale( GSE_CALLABLE, const int64_t& morale ) {
	if ( morale < unit::MORALE_MIN || morale > unit::MORALE_MAX ) {
		GSE_ERROR( gse::EC.INVALID_CALL, "Invalid morale value: " + std::to_string( morale ) + " (should be between " + std::to_string( unit::MORALE_MIN ) + " and " + std::to_string( unit::MORALE_MAX ) + ", inclusive)" );
	}
	return (unit::morale_t)morale;
}

const unit::health_t GetHealth( GSE_CALLABLE, const float health ) {
	if ( health < unit::Unit::MINIMUM_HEALTH_TO_KEEP || health > unit::StaticDef::HEALTH_MAX ) {
		GSE_ERROR( gse::EC.INVALID_CALL, "Invalid health value: " + std::to_string( health ) + " (should be between " + std::to_string( unit::Unit::MINIMUM_HEALTH_TO_KEEP ) + " and " + std::to_string( unit::StaticDef::HEALTH_MAX ) + ", inclusive)" );
	}
	if ( health == 0 ) {
		GSE_ERROR( gse::EC.INVALID_CALL, "Invalid health value: " + std::to_string( health ) + " (you can't spawn a dead unit)" );
	}
	return (unit::health_t)health;
}

BINDING_IMPL( units ) {
	const gse::type::object_properties_t properties = {
		{
			"define_morales",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 2 );
				N_GETVALUE( id, 0, String );
				N_GETVALUE( arr, 1, Array );
				const uint8_t expected_count = unit::MORALE_MAX - unit::MORALE_MIN + 1;
				if ( arr.size() != expected_count ) {
					GSE_ERROR( gse::EC.INVALID_CALL, "Morale set must have exactly " + std::to_string( expected_count ) + " values (found " + std::to_string( arr.size() ) + ")");
				}
				unit::MoraleSet::morale_values_t values = {};
				for ( const auto& v : arr ) {
					if ( v.Get()->type != gse::type::Type::T_OBJECT ) {
						GSE_ERROR( gse::EC.INVALID_CALL, "Morale set elements must be objects");
					}
					const auto* obj = (gse::type::Object*)v.Get();
					N_GETPROP( name, obj->value, "name", String );
					values.push_back( unit::Morale{ name } );
				}
				auto* game = GAME;
				return game->AddEvent( new event::DefineMorales( game->GetSlotNum(), new unit::MoraleSet( id, values ) ) );
			} )
		},
		{
			"define",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 2 );
				N_GETVALUE( id, 0, String );
				N_GETVALUE( unit_def, 1, Object );
				N_GETPROP( name, unit_def, "name", String );
				N_GETPROP( morale, unit_def, "morale", String );
				N_GETPROP( unit_type, unit_def, "type", String );
				if ( unit_type == "static" ) {
					N_GETPROP( movement_type_str, unit_def, "movement_type", String );
					unit::movement_type_t movement_type;
					if ( movement_type_str == "land" ) {
						movement_type = unit::MT_LAND;
					}
					else if ( movement_type_str == "water" ) {
						movement_type = unit::MT_WATER;
					}
					else if ( movement_type_str == "air" ) {
						movement_type = unit::MT_AIR;
					}
					else if ( movement_type_str == "immovable" ) {
						movement_type = unit::MT_IMMOVABLE;
					}
					else {
						GSE_ERROR( gse::EC.INVALID_CALL, "Invalid movement type: " + movement_type_str + ". Specify one of: land water air immovable");
					}
					N_GETPROP( movement_per_turn, unit_def, "movement_per_turn", Int );
					N_GETPROP( render_def, unit_def, "render", Object );
					N_GETPROP( render_type, render_def, "type", String );
					if ( render_type == "sprite" ) {
						N_GETPROP( sprite_file, render_def, "file", String );
						N_GETPROP( sprite_x, render_def, "x", Int );
						N_GETPROP( sprite_y, render_def, "y", Int );
						N_GETPROP( sprite_w, render_def, "w", Int );
						N_GETPROP( sprite_h, render_def, "h", Int );
						N_GETPROP( sprite_cx, render_def, "cx", Int );
						N_GETPROP( sprite_cy, render_def, "cy", Int );
						N_GETPROP_OPT_INT( sprite_morale_based_xshift, render_def, "morale_based_xshift" );
						auto* game = GAME;
						const auto* moraleset = game->GetUM()->GetMoraleSet( morale );
						if ( !moraleset ) {
							GSE_ERROR( gse::EC.INVALID_CALL, "Morale type '" + morale + "' is not defined");
						}
						auto* def = new unit::StaticDef(
							id,
							moraleset,
							name,
							movement_type,
							movement_per_turn,
							new unit::SpriteRender(
								sprite_file,
								sprite_x,
								sprite_y,
								sprite_w,
								sprite_h,
								sprite_cx,
								sprite_cy,
								sprite_morale_based_xshift
							)
						);
						return game->AddEvent( new event::DefineUnit( game->GetSlotNum(), def ) );
					}
					else {
						GSE_ERROR( gse::EC.GAME_ERROR, "Unsupported render type: " + render_type );
					}
				}
				else {
					GSE_ERROR( gse::EC.GAME_ERROR, "Unsupported unit type: " + unit_type );
				}
			})
		},
		{
			"spawn",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 5 );
				N_GETVALUE( def_name, 0, String );
				N_GETVALUE_UNWRAP( owner, 1, slot::Slot );
				N_GETVALUE_UNWRAP( tile, 2, map::tile::Tile );
				N_GETVALUE( morale, 3, Int );
				N_GETVALUE( health, 4, Float );
				auto* game = GAME;
				return game->AddEvent( new event::SpawnUnit(
					game->GetSlotNum(),
					def_name,
					owner->GetIndex(),
					tile->coord.x,
					tile->coord.y,
					GetMorale( ctx, call_si, morale ),
					GetHealth( ctx, call_si, health )
				) );
			})
		},
		{
			"despawn",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 1 );
				N_GETVALUE_UNWRAP( unit, 0, unit::Unit );
				auto* game = GAME;
				return game->AddEvent( new event::DespawnUnit( game->GetSlotNum(), unit->m_id ) );
			})
		},
	};
	return VALUE( gse::type::Object, properties );
}

}
}
}
