#include "engine_master.hpp"

#include "inputs_manager.hpp"
#include "application.hpp"
#include "physic_manager.hpp"
#include "render_manager.hpp"
#include "sound_manager.hpp"
#include "debug.hpp"
#include "graph.hpp"
#include "time.hpp"

namespace Core::Engine
{
	EngineMaster::EngineMaster()
	{
		Core::Debug::Log::info("Creating the Engine");

		Core::Input::InputManager::addButton("Edit Toggle", GLFW_KEY_C);
		Core::Application::setCursor(editMode || Graph::getCursorState());

		Engine::SoundManager::init();
	}

	EngineMaster::~EngineMaster()
	{
		Core::Debug::Log::info("Destroying the Engine");

		// Kill managers
		Graph::kill();
		Physics::PhysicManager::kill();
		LowRenderer::RenderManager::kill();
		SoundManager::kill();
	}

	void EngineMaster::toggleEditMode()
	{
		editMode = !editMode;

		Core::Application::setCursor(editMode || Graph::getCursorState());
	}

	void EngineMaster::update()
	{
		EngineMaster* EM = instance();

		if (Core::Input::InputManager::getButtonDown("Edit Toggle"))
			EM->toggleEditMode();

		Graph::draw();

		if (EM->editMode)
			Graph::drawImGui();
		else 
			Graph::update();

		Graph::clean();
	}
}	