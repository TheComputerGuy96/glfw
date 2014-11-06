#include "internal.h"
#include "xkb_unicode.h"

#include <linux/input.h>

// FIXME Remove me when done debugging!
#include <stdio.h>

MirPixelFormat FindValidPixelFormat()
{
    unsigned int pf_size = 32;
    unsigned int valid_formats;
    unsigned int f;

    MirPixelFormat formats[pf_size];
    mir_connection_get_available_surface_formats(_glfw.mir.connection, formats,
                                                 pf_size, &valid_formats);

    for (f = 0; f < valid_formats; f++)
    {
        MirPixelFormat cur_pf = formats[f];

        if (cur_pf == mir_pixel_format_abgr_8888 ||
            cur_pf == mir_pixel_format_xbgr_8888 ||
            cur_pf == mir_pixel_format_argb_8888 ||
            cur_pf == mir_pixel_format_xrgb_8888)
        {
            return cur_pf;
        }
    }

    return mir_pixel_format_invalid;
}

// Taken from wl_init.c
static int toGLFWKeyCode(uint32_t key)
{
    switch (key)
    {
        case KEY_GRAVE:         return GLFW_KEY_GRAVE_ACCENT;
        case KEY_1:             return GLFW_KEY_1;
        case KEY_2:             return GLFW_KEY_2;
        case KEY_3:             return GLFW_KEY_3;
        case KEY_4:             return GLFW_KEY_4;
        case KEY_5:             return GLFW_KEY_5;
        case KEY_6:             return GLFW_KEY_6;
        case KEY_7:             return GLFW_KEY_7;
        case KEY_8:             return GLFW_KEY_8;
        case KEY_9:             return GLFW_KEY_9;
        case KEY_0:             return GLFW_KEY_0;
        case KEY_MINUS:         return GLFW_KEY_MINUS;
        case KEY_EQUAL:         return GLFW_KEY_EQUAL;
        case KEY_Q:             return GLFW_KEY_Q;
        case KEY_W:             return GLFW_KEY_W;
        case KEY_E:             return GLFW_KEY_E;
        case KEY_R:             return GLFW_KEY_R;
        case KEY_T:             return GLFW_KEY_T;
        case KEY_Y:             return GLFW_KEY_Y;
        case KEY_U:             return GLFW_KEY_U;
        case KEY_I:             return GLFW_KEY_I;
        case KEY_O:             return GLFW_KEY_O;
        case KEY_P:             return GLFW_KEY_P;
        case KEY_LEFTBRACE:     return GLFW_KEY_LEFT_BRACKET;
        case KEY_RIGHTBRACE:    return GLFW_KEY_RIGHT_BRACKET;
        case KEY_A:             return GLFW_KEY_A;
        case KEY_S:             return GLFW_KEY_S;
        case KEY_D:             return GLFW_KEY_D;
        case KEY_F:             return GLFW_KEY_F;
        case KEY_G:             return GLFW_KEY_G;
        case KEY_H:             return GLFW_KEY_H;
        case KEY_J:             return GLFW_KEY_J;
        case KEY_K:             return GLFW_KEY_K;
        case KEY_L:             return GLFW_KEY_L;
        case KEY_SEMICOLON:     return GLFW_KEY_SEMICOLON;
        case KEY_APOSTROPHE:    return GLFW_KEY_APOSTROPHE;
        case KEY_Z:             return GLFW_KEY_Z;
        case KEY_X:             return GLFW_KEY_X;
        case KEY_C:             return GLFW_KEY_C;
        case KEY_V:             return GLFW_KEY_V;
        case KEY_B:             return GLFW_KEY_B;
        case KEY_N:             return GLFW_KEY_N;
        case KEY_M:             return GLFW_KEY_M;
        case KEY_COMMA:         return GLFW_KEY_COMMA;
        case KEY_DOT:           return GLFW_KEY_PERIOD;
        case KEY_SLASH:         return GLFW_KEY_SLASH;
        case KEY_BACKSLASH:     return GLFW_KEY_BACKSLASH;
        case KEY_ESC:           return GLFW_KEY_ESCAPE;
        case KEY_TAB:           return GLFW_KEY_TAB;
        case KEY_LEFTSHIFT:     return GLFW_KEY_LEFT_SHIFT;
        case KEY_RIGHTSHIFT:    return GLFW_KEY_RIGHT_SHIFT;
        case KEY_LEFTCTRL:      return GLFW_KEY_LEFT_CONTROL;
        case KEY_RIGHTCTRL:     return GLFW_KEY_RIGHT_CONTROL;
        case KEY_LEFTALT:       return GLFW_KEY_LEFT_ALT;
        case KEY_RIGHTALT:      return GLFW_KEY_RIGHT_ALT;
        case KEY_LEFTMETA:      return GLFW_KEY_LEFT_SUPER;
        case KEY_RIGHTMETA:     return GLFW_KEY_RIGHT_SUPER;
        case KEY_MENU:          return GLFW_KEY_MENU;
        case KEY_NUMLOCK:       return GLFW_KEY_NUM_LOCK;
        case KEY_CAPSLOCK:      return GLFW_KEY_CAPS_LOCK;
        case KEY_PRINT:         return GLFW_KEY_PRINT_SCREEN;
        case KEY_SCROLLLOCK:    return GLFW_KEY_SCROLL_LOCK;
        case KEY_PAUSE:         return GLFW_KEY_PAUSE;
        case KEY_DELETE:        return GLFW_KEY_DELETE;
        case KEY_BACKSPACE:     return GLFW_KEY_BACKSPACE;
        case KEY_ENTER:         return GLFW_KEY_ENTER;
        case KEY_HOME:          return GLFW_KEY_HOME;
        case KEY_END:           return GLFW_KEY_END;
        case KEY_PAGEUP:        return GLFW_KEY_PAGE_UP;
        case KEY_PAGEDOWN:      return GLFW_KEY_PAGE_DOWN;
        case KEY_INSERT:        return GLFW_KEY_INSERT;
        case KEY_LEFT:          return GLFW_KEY_LEFT;
        case KEY_RIGHT:         return GLFW_KEY_RIGHT;
        case KEY_DOWN:          return GLFW_KEY_DOWN;
        case KEY_UP:            return GLFW_KEY_UP;
        case KEY_F1:            return GLFW_KEY_F1;
        case KEY_F2:            return GLFW_KEY_F2;
        case KEY_F3:            return GLFW_KEY_F3;
        case KEY_F4:            return GLFW_KEY_F4;
        case KEY_F5:            return GLFW_KEY_F5;
        case KEY_F6:            return GLFW_KEY_F6;
        case KEY_F7:            return GLFW_KEY_F7;
        case KEY_F8:            return GLFW_KEY_F8;
        case KEY_F9:            return GLFW_KEY_F9;
        case KEY_F10:           return GLFW_KEY_F10;
        case KEY_F11:           return GLFW_KEY_F11;
        case KEY_F12:           return GLFW_KEY_F12;
        case KEY_F13:           return GLFW_KEY_F13;
        case KEY_F14:           return GLFW_KEY_F14;
        case KEY_F15:           return GLFW_KEY_F15;
        case KEY_F16:           return GLFW_KEY_F16;
        case KEY_F17:           return GLFW_KEY_F17;
        case KEY_F18:           return GLFW_KEY_F18;
        case KEY_F19:           return GLFW_KEY_F19;
        case KEY_F20:           return GLFW_KEY_F20;
        case KEY_F21:           return GLFW_KEY_F21;
        case KEY_F22:           return GLFW_KEY_F22;
        case KEY_F23:           return GLFW_KEY_F23;
        case KEY_F24:           return GLFW_KEY_F24;
        case KEY_KPSLASH:       return GLFW_KEY_KP_DIVIDE;
        case KEY_KPDOT:         return GLFW_KEY_KP_MULTIPLY;
        case KEY_KPMINUS:       return GLFW_KEY_KP_SUBTRACT;
        case KEY_KPPLUS:        return GLFW_KEY_KP_ADD;
        case KEY_KP0:           return GLFW_KEY_KP_0;
        case KEY_KP1:           return GLFW_KEY_KP_1;
        case KEY_KP2:           return GLFW_KEY_KP_2;
        case KEY_KP3:           return GLFW_KEY_KP_3;
        case KEY_KP4:           return GLFW_KEY_KP_4;
        case KEY_KP5:           return GLFW_KEY_KP_5;
        case KEY_KP6:           return GLFW_KEY_KP_6;
        case KEY_KP7:           return GLFW_KEY_KP_7;
        case KEY_KP8:           return GLFW_KEY_KP_8;
        case KEY_KP9:           return GLFW_KEY_KP_9;
        case KEY_KPCOMMA:       return GLFW_KEY_KP_DECIMAL;
        case KEY_KPEQUAL:       return GLFW_KEY_KP_EQUAL;
        case KEY_KPENTER:       return GLFW_KEY_KP_ENTER;
        default:                return GLFW_KEY_UNKNOWN;
    }
}

void HandleKeyEvent(MirKeyEvent const key, _GLFWwindow* window)
{
    int pressed = key.action == mir_key_action_up ?  GLFW_RELEASE : GLFW_PRESS;

    // FIXME Get the correct modifiers
    _glfwInputKey(window, toGLFWKeyCode(key.scan_code), key.scan_code, pressed, 0);

   long text = _glfwKeySym2Unicode(key.key_code);

   // FIXME fill in mod, and last argument
   _glfwInputChar(window, text, 0, 0);
}

void HandleMouseButton(_GLFWwindow* window, int pressed, MirMotionButton button)
{
    static int last_button;
    int glfw_button;

    switch (button)
    {
        case mir_motion_button_primary:
            glfw_button = GLFW_MOUSE_BUTTON_LEFT;
            break;
        case mir_motion_button_secondary:
            glfw_button = GLFW_MOUSE_BUTTON_RIGHT;
            break;
        case mir_motion_button_tertiary:
            glfw_button = GLFW_MOUSE_BUTTON_MIDDLE;
            break;
        case mir_motion_button_forward:
            // FIXME What is the forward button?
            glfw_button = GLFW_MOUSE_BUTTON_4;
            break;
        case mir_motion_button_back:
            // FIXME What is the back button?
            glfw_button = GLFW_MOUSE_BUTTON_5;
            break;
        default:
            glfw_button = last_button;
            break;
    }

    last_button = glfw_button;

    // FIXME Get the modifiers
    _glfwInputMouseClick(window, glfw_button, pressed, 0);
}

// TODO Confirm the x/y is correct and no futher work needs to be done.
void HandleMouseMotion(_GLFWwindow* window, int x, int y)
{
    _glfwInputCursorMotion(window, x, y);
}

// TODO Confirm it really wants the dx/dy and that they are in the correct direction!
void HandleMouseScroll(_GLFWwindow* window, int dx, int dy)
{
    _glfwInputScroll(window, dx, dy);
}

void HandleMouseEvent(MirMotionEvent const motion, int cord_index, _GLFWwindow* window)
{
    switch (motion.action)
    {
          case mir_motion_action_down:
          case mir_motion_action_pointer_down:
              HandleMouseButton(window, GLFW_PRESS, motion.button_state);
              break;
          case mir_motion_action_up:
          case mir_motion_action_pointer_up:
              HandleMouseButton(window, GLFW_RELEASE, motion.button_state);
              break;
          case mir_motion_action_hover_move:
          case mir_motion_action_move:
              HandleMouseMotion(window,
                                motion.pointer_coordinates[cord_index].x,
                                motion.pointer_coordinates[cord_index].y);
              break;
          case mir_motion_action_outside:
              break;
          case mir_motion_action_scroll:
              HandleMouseScroll(window,
                                motion.pointer_coordinates[cord_index].hscroll,
                                motion.pointer_coordinates[cord_index].vscroll);
              break;
          case mir_motion_action_cancel:
          case mir_motion_action_hover_enter:
          case mir_motion_action_hover_exit:
              break;
          default:
              break;

    }
}

static void HandleMotionEvent(MirMotionEvent const motion, _GLFWwindow* window)
{
    int cord_index;
    for (cord_index = 0; cord_index < motion.pointer_count; cord_index++) {
        HandleMouseEvent(motion, cord_index, window);
        /*
        // TODO Does GLFW handle touch events?
        if (motion.pointer_coordinates[cord_index].tool_type == mir_motion_tool_type_finger) {
            HandleTouchEvent(motion, cord_index, window);
        }
        else {
            HandleMouseEvent(motion, cord_index, window);
        }
        */
    }
}

void HandleInput(MirSurface* surface, MirEvent const* event, void* context)
{
  switch (event->type)
  {
    case(mir_event_type_key):
      HandleKeyEvent(event->key, (_GLFWwindow*)context);
      break;
    case(mir_event_type_motion):
      HandleMotionEvent(event->motion, (_GLFWwindow*)context);
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////////
//////                       GLFW platform API                      //////
//////////////////////////////////////////////////////////////////////////

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GL_FALSE;

    // FIXME Add a check here to ensure we are within our max width/height
    window->mir.width  = wndconfig->width;
    window->mir.height = wndconfig->height;

    MirSurfaceParameters params = 
    {
        .name         = "MirSurface",
        .width        = wndconfig->width,
        .height       = wndconfig->height,
        .pixel_format = mir_pixel_format_invalid,
        .buffer_usage = mir_buffer_usage_hardware,
        .output_id    = mir_display_output_id_invalid
    };

    MirEventDelegate delegate =
    {
        HandleInput,
        window
    };

    params.pixel_format = FindValidPixelFormat();
    if (params.pixel_format == mir_pixel_format_invalid)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Mir: Unable to find a correct pixel format!\n");
        return GL_FALSE;
    }

    window->mir.surface = mir_connection_create_surface_sync(_glfw.mir.connection, &params);
    if (!mir_surface_is_valid(window->mir.surface))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Mir: Unable to create surface!\n");
        return GL_FALSE;
    }

    window->mir.native_window = mir_surface_get_egl_native_window(window->mir.surface);

    mir_surface_set_event_handler(window->mir.surface, &delegate);

    return GL_TRUE;
}

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
  if (mir_surface_is_valid(window->mir.surface))
  {
    mir_surface_release_sync(window->mir.surface);
    window->mir.surface = NULL;
  }
}

void _glfwPlatformSetWindowTitle(_GLFWwindow* window, const char* title)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetWindowPos(_GLFWwindow* window, int xpos, int ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetWindowSize(_GLFWwindow* window, int width, int height)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetWindowSize(_GLFWwindow* window, int* width, int* height)
{
    *width  = window->mir.width;
    *height = window->mir.height;
}

void _glfwPlatformIconifyWindow(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformRestoreWindow(_GLFWwindow* window)
{
}

void _glfwPlatformHideWindow(_GLFWwindow* window)
{
}

// Mir does event handling in a different thread, so windows get events directly as they happen
void _glfwPlatformPollEvents(void)
{
}

void _glfwPlatformWaitEvents(void)
{
}

void _glfwPlatformPostEmptyEvent(void)
{
}

void _glfwPlatformGetFramebufferSize(_GLFWwindow* window, int* width, int* height)
{
    *width  = window->mir.width;
    *height = window->mir.height;
}

void _glfwPlatformGetWindowFrameSize(_GLFWwindow* window, int* left, int* top, int* right, int* bottom)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformShowWindow(_GLFWwindow* window)
{
}

void _glfwPlatformUnhideWindow(_GLFWwindow* window)
{
}

void _glfwPlatformGetWindowPos(_GLFWwindow* window, int* xpos, int* ypos)
{
}

int _glfwPlatformCreateCursor(_GLFWcursor* cursor, const GLFWimage* image, int xhot, int yhot)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);

    return 0;
}

void _glfwPlatformDestroyCursor(_GLFWcursor* cursor)
{
}

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
}

void _glfwPlatformSetCursorPos(_GLFWwindow* window, double xpos, double ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

void _glfwPlatformApplyCursorMode(_GLFWwindow* window)
{
}

void _glfwPlatformSetClipboardString(_GLFWwindow* window, const char* string)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);
}

const char* _glfwPlatformGetClipboardString(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Mir: Unsupported Function %s!\n", __PRETTY_FUNCTION__);

    return NULL;
}