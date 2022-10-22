#ifndef CORE_INPUT_H_
#define CORE_INPUT_H_

#include <glm/vec2.hpp>

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

class Input {
public:
	static bool isKeyPressed(KeyCode key);

	static bool isMouseButtonPressed(MouseCode button);
	static glm::vec2 getMousePosition();
	static float getMouseX();
	static float getMouseY();
};

#endif // !CORE_INPUT_H_