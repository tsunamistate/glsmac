#pragma once

// top level game object
// passed to scripts and everywhere, contains global state

#include "common/Common.h"
#include "gse/Bindings.h"
#include "gse/Wrappable.h"

#include "gse/GSE.h"
#include "gse/type/Object.h"

namespace ui {
class UI;
}

namespace task::main {
class Main;
}

namespace game::backend {
class State;
}

CLASS3( GLSMAC, common::Class, gse::Bindings, gse::Wrappable )
	GLSMAC();
	~GLSMAC();

	void Iterate();

	WRAPDEFS_PTR( GLSMAC )

private:
	gse::GSE* m_gse = nullptr;
	gse::context::GlobalContext* m_ctx = nullptr;

	std::vector< gse::Value > m_main_callables = {};

	ui::UI* m_ui = nullptr;

	// steps
	void S_Init( GSE_CALLABLE, const std::optional< std::string >& path );
	void S_Intro( GSE_CALLABLE );
	void S_MainMenu( GSE_CALLABLE );
	void S_Game( GSE_CALLABLE );

	void ShowLoader( GSE_CALLABLE, const std::string& text );
	void LoaderText( GSE_CALLABLE, const std::string& text );
	void HideLoader( GSE_CALLABLE );

	game::backend::State* m_state = nullptr;
	bool m_is_game_running = false;

	void DeinitGameState( GSE_CALLABLE );
	void InitGameState( GSE_CALLABLE );
	void RandomizeSettings( GSE_CALLABLE );

	void AddSinglePlayerSlot();
	void StartGame( GSE_CALLABLE );

private:
	friend class task::main::Main;
	void RunMain();

private:
	friend class gse::GSE;
	void AddToContext( gse::context::Context* ctx, gse::ExecutionPointer& ep ) override;

};
