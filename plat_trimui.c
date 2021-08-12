#include <SDL/SDL.h>
#include "main.h"
#include "libretro.h"
#include "libpicofe/plat.h"
#include "libpicofe/input.h"
#include "libpicofe/in_sdl.h"

#define SAMPLE_RATE 48000

static const struct in_default_bind in_sdl_defbinds[] = {
	{ SDLK_UP,        IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_UP },
	{ SDLK_DOWN,      IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_DOWN },
	{ SDLK_LEFT,      IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_LEFT },
	{ SDLK_RIGHT,     IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_RIGHT },
	{ SDLK_LCTRL,     IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_B },
	{ SDLK_SPACE,     IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_A },
	{ SDLK_LSHIFT,    IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_X },
	{ SDLK_LALT,      IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_Y },
	{ SDLK_RETURN,    IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_START },
	{ SDLK_RCTRL,     IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_SELECT },
	{ SDLK_TAB,       IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_L },
	{ SDLK_BACKSPACE, IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_R },
	{ SDLK_q,         IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_L2 },
	{ SDLK_BACKSLASH, IN_BINDTYPE_PLAYER12, RETRO_DEVICE_ID_JOYPAD_R2 },
	{ SDLK_ESCAPE,    IN_BINDTYPE_EMU, EACTION_MENU },
	{ 0, 0, 0 }
};

const struct menu_keymap in_sdl_key_map[] =
{
	{ SDLK_UP,        PBTN_UP },
	{ SDLK_DOWN,      PBTN_DOWN },
	{ SDLK_LEFT,      PBTN_LEFT },
	{ SDLK_RIGHT,     PBTN_RIGHT },
	{ SDLK_SPACE,     PBTN_MOK },
	{ SDLK_LCTRL,     PBTN_MBACK },
	{ SDLK_LALT,      PBTN_MA2 },
	{ SDLK_LSHIFT,    PBTN_MA3 },
	{ SDLK_TAB,       PBTN_L },
	{ SDLK_BACKSPACE, PBTN_R },
	{ SDLK_ESCAPE,    PBTN_MENU },
};

const struct menu_keymap in_sdl_joy_map[] =
{
	{ SDLK_UP,    PBTN_UP },
	{ SDLK_DOWN,  PBTN_DOWN },
	{ SDLK_LEFT,  PBTN_LEFT },
	{ SDLK_RIGHT, PBTN_RIGHT },
	{ SDLK_WORLD_0, PBTN_MOK },
	{ SDLK_WORLD_1, PBTN_MBACK },
	{ SDLK_WORLD_2, PBTN_MA2 },
	{ SDLK_WORLD_3, PBTN_MA3 },
};

static const char * const in_sdl_key_names[SDLK_LAST] = {
	[SDLK_UP]         = "up",
	[SDLK_DOWN]       = "down",
	[SDLK_LEFT]       = "left",
	[SDLK_RIGHT]      = "right",
	[SDLK_LSHIFT]     = "x",
	[SDLK_LCTRL]      = "b",
	[SDLK_SPACE]      = "a",
	[SDLK_LALT]       = "y",
	[SDLK_RETURN]     = "start",
	[SDLK_RCTRL]      = "select",
	[SDLK_TAB]        = "l",
	[SDLK_BACKSPACE]  = "r",
	[SDLK_1]          = "menu+up",
	[SDLK_2]          = "menu+down",
	[SDLK_3]          = "menu+left",
	[SDLK_4]          = "menu+right",
	[SDLK_5]          = "menu+b",
	[SDLK_6]          = "menu+a",
	[SDLK_7]          = "menu+x",
	[SDLK_8]          = "menu+y",
	[SDLK_9]          = "menu+start",
	[SDLK_0]          = "menu+select",
	[SDLK_q]          = "menu+l",
	[SDLK_BACKSLASH]  = "menu+r",
	[SDLK_ESCAPE]     = "menu",
};

static const struct mod_keymap in_sdl_mod_keymap[] = {
	{ SDLK_UP,        SDLK_1 },
	{ SDLK_DOWN,      SDLK_2 },
	{ SDLK_LEFT,      SDLK_3 },
	{ SDLK_RIGHT,     SDLK_4 },
	{ SDLK_LCTRL,     SDLK_5 },
	{ SDLK_SPACE,     SDLK_6 },
	{ SDLK_LSHIFT,    SDLK_7 },
	{ SDLK_LALT,      SDLK_8 },
	{ SDLK_RETURN,    SDLK_9 },
	{ SDLK_RCTRL,     SDLK_0 },
	{ SDLK_TAB,       SDLK_q },          /* mod+L1 = L2 */
	{ SDLK_BACKSPACE, SDLK_BACKSLASH },  /* mod+R1 = R2 */
};

static const struct in_pdata in_sdl_platform_data = {
	.defbinds  = in_sdl_defbinds,
	.key_map   = in_sdl_key_map,
	.kmap_size = array_size(in_sdl_key_map),
	.joy_map   = in_sdl_joy_map,
	.jmap_size = array_size(in_sdl_joy_map),
	.key_names = in_sdl_key_names,
	.mod_key      = SDLK_ESCAPE,
	.mod_keymap   = in_sdl_mod_keymap,
	.modmap_size  = array_size(in_sdl_mod_keymap),
};

#include "plat_sdl.c"
