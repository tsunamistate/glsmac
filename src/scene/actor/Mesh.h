#pragma once

#include "Actor.h"

#include "../mesh/Mesh.h"
#include "types/Color.h"
#include "types/Texture.h"

namespace scene {
namespace actor {

CLASS( Mesh, Actor )
	Mesh( const std::string &name, const mesh::Mesh *mesh );
	~Mesh();
	const mesh::Mesh *GetMesh() const;
	void SetTexture( const types::Texture* texture );
	const types::Texture* GetTexture();
protected:
	const mesh::Mesh *m_mesh;

	const types::Texture* m_texture = nullptr;
	const bool m_is_texture_tiled = false;
};

} /* namespace scene */
} /* namespace actor */