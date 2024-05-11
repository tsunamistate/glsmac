#pragma once

#include <cstddef>

namespace task {
namespace game {

class InstancedSprite;

class Sprite {
public:
	InstancedSprite* instanced_sprite = nullptr;
	size_t next_instance_id = 1;
};

}
}
