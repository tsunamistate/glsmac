#pragma once

#include "base/Task.h"

#include "util/Timer.h"

namespace ui::object {
class Surface;
}

namespace task {
namespace intro {

class Theme;

CLASS( Intro, base::Task )
	void Start() override;
	void Stop() override;
	void Iterate() override;

protected:
	Theme* m_theme;
	::ui::object::Surface* m_logo = nullptr;
	util::Timer m_timer;

};

}
}
