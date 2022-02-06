/*
    Copyright 2021 natinusala
	Copyright 2021 XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <borealis/core/application.hpp>
#include <borealis/core/logger.hpp>
#include <borealis/platforms/glfw/glfw_input.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace brls
{

#define GLFW_GAMEPAD_BUTTON_NONE SIZE_MAX
#define GLFW_GAMEPAD_BUTTON_MAX 15
#define GLFW_GAMEPAD_AXIS_MAX 4

// LT and RT do not exist here because they are axes
static const size_t GLFW_BUTTONS_MAPPING[GLFW_GAMEPAD_BUTTON_MAX] = {
    BUTTON_A, // GLFW_GAMEPAD_BUTTON_A
    BUTTON_B, // GLFW_GAMEPAD_BUTTON_B
    BUTTON_X, // GLFW_GAMEPAD_BUTTON_X
    BUTTON_Y, // GLFW_GAMEPAD_BUTTON_Y
    BUTTON_LB, // GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
    BUTTON_RB, // GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
    BUTTON_BACK, // GLFW_GAMEPAD_BUTTON_BACK
    BUTTON_START, // GLFW_GAMEPAD_BUTTON_START
    BUTTON_GUIDE, // GLFW_GAMEPAD_BUTTON_GUIDE
    BUTTON_LSB, // GLFW_GAMEPAD_BUTTON_LEFT_THUMB
    BUTTON_RSB, // GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
    BUTTON_UP, // GLFW_GAMEPAD_BUTTON_DPAD_UP
    BUTTON_RIGHT, // GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
    BUTTON_DOWN, // GLFW_GAMEPAD_BUTTON_DPAD_DOWN
    BUTTON_LEFT, // GLFW_GAMEPAD_BUTTON_DPAD_LEFT
};

static const size_t GLFW_GAMEPAD_TO_KEYBOARD[GLFW_GAMEPAD_BUTTON_MAX] = {
    GLFW_KEY_ENTER, // GLFW_GAMEPAD_BUTTON_A
    GLFW_KEY_BACKSPACE, // GLFW_GAMEPAD_BUTTON_B
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_X
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_Y
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_LEFT_BUMPER
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
    GLFW_KEY_F1, // GLFW_GAMEPAD_BUTTON_BACK
    GLFW_KEY_ESCAPE, // GLFW_GAMEPAD_BUTTON_START
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_GUIDE
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_LEFT_THUMB
    GLFW_GAMEPAD_BUTTON_NONE, // GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
    GLFW_KEY_UP, // GLFW_GAMEPAD_BUTTON_DPAD_UP
    GLFW_KEY_RIGHT, // GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
    GLFW_KEY_DOWN, // GLFW_GAMEPAD_BUTTON_DPAD_DOWN
    GLFW_KEY_LEFT, // GLFW_GAMEPAD_BUTTON_DPAD_LEFT
};

static const size_t GLFW_AXIS_MAPPING[GLFW_GAMEPAD_AXIS_MAX] = {
    LEFT_X,
    LEFT_Y,
    RIGHT_X,
    RIGHT_Y,
};

static short controllersCount = 0;

static void glfwJoystickCallback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        Logger::info("glfw: joystick {} connected", jid);

        if (glfwJoystickIsGamepad(jid)) {
            Logger::info("glfw: joystick {} is gamepad: \"{}\"", jid, glfwGetGamepadName(jid));
        }

        controllersCount++;
    }
    else if (event == GLFW_DISCONNECTED)
    {
        Logger::info("glfw: joystick {} disconnected", jid);

        controllersCount--;
    }
}

void GLFWInputManager::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GLFWInputManager* self = (GLFWInputManager*)Application::getPlatform()->getInputManager();
    KeyState state;
    state.key = (BrlsKeyboardScancode)key;
    state.mods = mods;
    state.pressed = action != GLFW_RELEASE;
    const char* key_name = glfwGetKeyName(key, scancode);
    if (key_name != NULL)
        Logger::debug("Key: {} / Code: {}", key_name, key);
    else
        Logger::debug("Key: NULL / Code: {}", key);
    self->getKeyboardKeyStateChanged()->fire(state);
}

void GLFWInputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    GLFWInputManager* self = (GLFWInputManager*)Application::getPlatform()->getInputManager();
    self->scrollOffset.x += xoffset * 10;
    self->scrollOffset.y += yoffset * 10;
    self->getMouseScrollOffsetChanged()->fire(Point(xoffset, yoffset));
}

void GLFWInputManager::cursorCallback(GLFWwindow* window, double x, double y)
{
    GLFWInputManager* self = (GLFWInputManager*)Application::getPlatform()->getInputManager();
    if (self->pointerLocked) {
        int width, height;
        glfwGetWindowSize(self->window, &width, &height);
        
        int hWidth = width / 2;
        int hHeight = height / 2;
        
        Point localPointerOffset;
        
        localPointerOffset.x = (x - hWidth);// / Application::windowScale;
        localPointerOffset.y = (y - hHeight);// / Application::windowScale;
        
        self->pointerOffsetBuffer.x += (x - hWidth);// / Application::windowScale;
        self->pointerOffsetBuffer.y += (y - hHeight);// / Application::windowScale;
        
        self->getMouseCusorOffsetChanged()->fire(localPointerOffset);
        glfwSetCursorPos(self->window, hWidth, hHeight);
    }
}

GLFWInputManager::GLFWInputManager(GLFWwindow* window)
    : window(window)
{
    glfwSetJoystickCallback(glfwJoystickCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetKeyCallback(window, keyboardCallback);

    for (int i = 0; i < GAMEPADS_MAX; i++) {
        if (glfwJoystickIsGamepad(i))
        {
            Logger::info("glfw: joystick {} connected", i);
            Logger::info("glfw: joystick {} is gamepad: \"{}\"", i, glfwGetGamepadName(i));
        }
    }
    
    Application::getRunLoopEvent()->subscribe([this, window]() {
        scrollOffset.x  = 0;
        scrollOffset.y  = 0;
        pointerOffset.x = 0;
        pointerOffset.y = 0;
    });
}

short GLFWInputManager::getControllersConnectedCount()
{
    return controllersCount;
}

void GLFWInputManager::updateUnifiedControllerState(ControllerState* state)
{
    for (size_t i = 0; i < _BUTTON_MAX; i++)
        state->buttons[i] = false;

    for (size_t i = 0; i < _AXES_MAX; i++)
        state->axes[i] = 0;

    for (int i = 0; i < GAMEPADS_MAX; i++) {
        ControllerState localState;
        updateControllerState(&localState, i);

        for (size_t i = 0; i < _BUTTON_MAX; i++)
            state->buttons[i] |= localState.buttons[i];

        for (size_t i = 0; i < _AXES_MAX; i++) {
            state->axes[i] += localState.axes[i];

            if (state->axes[i] < -1) state->axes[i] = -1;
            else if (state->axes[i] > 1) state->axes[i] = 1;
        }
    }
}

void GLFWInputManager::updateControllerState(ControllerState* state, int controller)
{
    // Get gamepad state
    GLFWgamepadstate glfwState = {};
    glfwGetGamepadState(controller, &glfwState);

    for (size_t i = 0; i < GLFW_GAMEPAD_BUTTON_MAX; i++)
    {
        // Add keyboard keys on top of gamepad buttons
//        size_t key;// = GLFW_GAMEPAD_TO_KEYBOARD[i];

//        if (key != GLFW_GAMEPAD_BUTTON_NONE)
//            glfwState.buttons[i] |= glfwGetKey(this->window, key);

        // Translate GLFW gamepad to borealis controller
        size_t brlsButton          = GLFW_BUTTONS_MAPPING[i];
        state->buttons[brlsButton] = (bool)glfwState.buttons[i];
    }

    state->buttons[BUTTON_LT] = glfwState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > 0.1f;
    state->buttons[BUTTON_RT] = glfwState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > 0.1f;

    state->buttons[BUTTON_NAV_UP]    = glfwState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.5f || state->buttons[BUTTON_UP];
    state->buttons[BUTTON_NAV_RIGHT] = glfwState.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.5f || state->buttons[BUTTON_RIGHT];
    state->buttons[BUTTON_NAV_DOWN]  = glfwState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.5f || state->buttons[BUTTON_DOWN];
    state->buttons[BUTTON_NAV_LEFT]  = glfwState.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.5f || state->buttons[BUTTON_LEFT];

    state->buttons[BUTTON_NAV_UP]    |= glfwGetKey(this->window, GLFW_KEY_UP);
    state->buttons[BUTTON_NAV_RIGHT] |= glfwGetKey(this->window, GLFW_KEY_RIGHT);
    state->buttons[BUTTON_NAV_DOWN]  |= glfwGetKey(this->window, GLFW_KEY_DOWN);
    state->buttons[BUTTON_NAV_LEFT]  |= glfwGetKey(this->window, GLFW_KEY_LEFT);

    for (size_t i = 0; i < GLFW_GAMEPAD_AXIS_MAX; i++)
    {
        state->axes[GLFW_AXIS_MAPPING[i]] = glfwState.axes[i];
    }
}

bool GLFWInputManager::getKeyboardKeyState(BrlsKeyboardScancode key)
{
    return glfwGetKey(this->window, key);
}

bool sameSign(int a, int b)
{
    if (a == 0 || b == 0)
        return true;
    return (a >= 0) ^ (b < 0);
}

void GLFWInputManager::updateTouchStates(std::vector<RawTouchState>* states)
{
    // Uncomment to enable touch simulation by mouse
    //    double x, y;
    //    glfwGetCursorPos(this->window, &x, &y);
    //
    //    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    //    {
    //        RawTouchState state;
    //        state.fingerId = 0;
    //        state.pressed = true;
    //        state.position.x = x / Application::windowScale;
    //        state.position.y = y / Application::windowScale;
    //        states->push_back(state);
    //    }
}

void GLFWInputManager::updateMouseStates(RawMouseState* state)
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);

    state->leftButton   = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    state->middleButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    state->rightButton  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    state->position.x   = x / Application::windowScale;
    state->position.y   = y / Application::windowScale;
    state->offset       = pointerOffset;
    state->scroll       = scrollOffset;
    
#ifdef __APPLE__
    state->position = state->position * 2;
#endif
}

void GLFWInputManager::setPointerLock(bool lock) {
    pointerLocked = lock;
    
    int state = lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(window, GLFW_CURSOR, state);
}

void GLFWInputManager::runloopStart()
{
    pointerOffset = pointerOffsetBuffer;
    pointerOffsetBuffer.x = 0;
    pointerOffsetBuffer.y = 0;
}

void GLFWInputManager::sendRumble(unsigned short controller, unsigned short lowFreqMotor, unsigned short highFreqMotor)
{
}

};
