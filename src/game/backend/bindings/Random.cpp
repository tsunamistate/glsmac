#include "game/backend/Game.h"
#include "game/backend/State.h"
#include "Bindings.h"
#include "gse/callable/Native.h"
#include "gse/type/Object.h"
#include "gse/type/Int.h"
#include "gse/type/Float.h"
#include "gse/type/Undefined.h"
#include "util/random/Random.h"

#include "Binding.h"

namespace game {
namespace backend {
namespace bindings {

BINDING_IMPL( random ) {
	const gse::type::object_properties_t properties = {
		{
			"get_int",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 2 );
				N_GETVALUE( min, 0, Int );
				N_GETVALUE( max, 1, Int );
				if ( max < min ) {
					GSE_ERROR( gse::EC.INVALID_CALL, "Maximum value is smaller than minimum ( " + std::to_string( max ) + " < " + std::to_string( min ) + " )" );
				}
				if ( !GAME->GetState()->IsMaster() ) {
					GSE_ERROR( gse::EC.INVALID_CALL, "Only master is allowed to generate random values" );
				}
				return VALUE( gse::type::Int, GAME->GetRandom()->GetInt64( min, max ) );
			})
		},
		{
			"get_float",
			NATIVE_CALL( this ) {
				N_EXPECT_ARGS( 2 );
				N_GETVALUE( min, 0, Float );
				N_GETVALUE( max, 1, Float );
				if ( max < min ) {
					GSE_ERROR( gse::EC.INVALID_CALL, "Maximum value is smaller than minimum ( " + std::to_string( max ) + " < " + std::to_string( min ) + " )" );
				}
				if ( !GAME->GetState()->IsMaster() ) {
					GSE_ERROR( gse::EC.INVALID_CALL, "Only master is allowed to generate random values" );
				}
				return VALUE( gse::type::Float, GAME->GetRandom()->GetFloat( min, max ) );
			})
		},
	};
	return VALUE( gse::type::Object, properties );
}

}
}
}
