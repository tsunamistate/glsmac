#pragma once

#include "Routine.h"

//#include "../shader_program/World.h"
#include "../shader_program/Orthographic.h"

namespace graphics {
namespace opengl {
namespace routine {

CLASS( World, Routine )
	//World( shader_program::World *shader_program ) : m_shader_program( shader_program ) {};
	World( shader_program::Orthographic *shader_program ) : m_shader_program( shader_program ) {};

	bool SceneBelongs( const scene::Scene *scene ) const;

	void Start();
	void Stop();
	void Iterate();

protected:
	shader_program::Orthographic *m_shader_program;
};

} /* namespace routine */
} /* namespace opengl */
} /* namespace graphics */