/*
 * UAE - The Un*x Amiga Emulator
 *
 * Support for platform-independent key-mapping
 *
 * Copyright 2004 Richard Drummond
 *           2010-2011 Mustafa Tufan
 */

#include "sysconfig.h"
#include "sysdeps.h"

#include "options.h"
#include "inputdevice.h"
#include "keymap.h"
#include "keyboard.h"

/*
 * Default mapping of UAE keycodes to UAE input events
 *
 * This list is ordered by UAEKEY_#? code. Input events correspond
 * to Amiga keycodes or UAE commands.
 */
static const int default_keymap[] = {
				INPUTEVENT_ZERO,
    /* UAEKEY_ESCAPE */ 	INPUTEVENT_KEY_ESC,

    /* UAEKEY_F1 */		INPUTEVENT_KEY_F1,
    /* UAEKEY_F2 */		INPUTEVENT_KEY_F2,
    /* UAEKEY_F3 */		INPUTEVENT_KEY_F3,
    /* UAEKEY_F4 */		INPUTEVENT_KEY_F4,
    /* UAEKEY_F5 */		INPUTEVENT_KEY_F5,
    /* UAEKEY_F6 */		INPUTEVENT_KEY_F6,
    /* UAEKEY_F7 */		INPUTEVENT_KEY_F7,
    /* UAEKEY_F8 */		INPUTEVENT_KEY_F8,
    /* UAEKEY_F9 */		INPUTEVENT_KEY_F9,
    /* UAEKEY_F10 */		INPUTEVENT_KEY_F10,
    /* UAEKEY_F11 */		INPUTEVENT_ZERO,
    /* UAEKEY_F12 */		INPUTEVENT_ZERO,

    /* UAEKEY_PRINTSCR */	INPUTEVENT_SPC_SCREENSHOT,
    /* UAEKEY_SCROLL_LOCK */	INPUTEVENT_SPC_INHIBITSCREEN,
    /* UAEKEY_PAUSE */		INPUTEVENT_SPC_PAUSE,

    /* UAEKEY_1 */		INPUTEVENT_KEY_1,
    /* UAEKEY_2 */		INPUTEVENT_KEY_2,
    /* UAEKEY_3 */		INPUTEVENT_KEY_3,
    /* UAEKEY_4 */		INPUTEVENT_KEY_4,
    /* UAEKEY_5 */		INPUTEVENT_KEY_5,
    /* UAEKEY_6 */		INPUTEVENT_KEY_6,
    /* UAEKEY_7 */		INPUTEVENT_KEY_7,
    /* UAEKEY_8 */		INPUTEVENT_KEY_8,
    /* UAEKEY_9 */		INPUTEVENT_KEY_9,
    /* UAEKEY_0	*/		INPUTEVENT_KEY_0,

    /* UAEKEY_MINUS */		INPUTEVENT_KEY_SUB,
    /* UAEKEY_EQUALS */		INPUTEVENT_KEY_EQUALS,

    /* UAEKEY_BACKSPACE */	INPUTEVENT_KEY_BACKSPACE,
    /* UAEKEY_ENTER */		INPUTEVENT_KEY_RETURN,
    /* UAEKEY_SPACE */		INPUTEVENT_KEY_SPACE,

    /* UAEKEY_TAB */		INPUTEVENT_KEY_TAB,

    /* UAEKEY_A */		INPUTEVENT_KEY_A,
    /* UAEKEY_B */		INPUTEVENT_KEY_B,
    /* UAEKEY_C */		INPUTEVENT_KEY_C,
    /* UAEKEY_D */		INPUTEVENT_KEY_D,
    /* UAEKEY_E */		INPUTEVENT_KEY_E,
    /* UAEKEY_F */		INPUTEVENT_KEY_F,
    /* UAEKEY_G */		INPUTEVENT_KEY_G,
    /* UAEKEY_H */		INPUTEVENT_KEY_H,
    /* UAEKEY_I */		INPUTEVENT_KEY_I,
    /* UAEKEY_J */		INPUTEVENT_KEY_J,
    /* UAEKEY_K */		INPUTEVENT_KEY_K,
    /* UAEKEY_L */		INPUTEVENT_KEY_L,
    /* UAEKEY_M */		INPUTEVENT_KEY_M,
    /* UAEKEY_N */		INPUTEVENT_KEY_N,
    /* UAEKEY_O */		INPUTEVENT_KEY_O,
    /* UAEKEY_P */		INPUTEVENT_KEY_P,
    /* UAEKEY_Q */		INPUTEVENT_KEY_Q,
    /* UAEKEY_R */		INPUTEVENT_KEY_R,
    /* UAEKEY_S */		INPUTEVENT_KEY_S,
    /* UAEKEY_T */		INPUTEVENT_KEY_T,
    /* UAEKEY_U */		INPUTEVENT_KEY_U,
    /* UAEKEY_V */		INPUTEVENT_KEY_V,
    /* UAEKEY_W */		INPUTEVENT_KEY_W,
    /* UAEKEY_X */		INPUTEVENT_KEY_X,
    /* UAEKEY_Y */		INPUTEVENT_KEY_Y,
    /* UAEKEY_Z */		INPUTEVENT_KEY_Z,

    /* UAEKEY_LEFTBRACKET */	INPUTEVENT_KEY_LEFTBRACKET,
    /* UAEKEY_RIGHTBRACKET */	INPUTEVENT_KEY_RIGHTBRACKET,
    /* UAEKEY_SEMICOLON */	INPUTEVENT_KEY_SEMICOLON,
    /* UAEKEY_SINGLEQUOTE */	INPUTEVENT_KEY_SINGLEQUOTE,
    /* UAEKEY_GRAVE */		INPUTEVENT_KEY_BACKQUOTE,
    /* UAEKEY_BACKSLASH */	INPUTEVENT_KEY_BACKSLASH,
    /* UAEKEY_COMMA */		INPUTEVENT_KEY_COMMA,
    /* UAEKEY_PERIOD */		INPUTEVENT_KEY_PERIOD,
    /* UAEKEY_SLASH */		INPUTEVENT_KEY_DIV,
    /* UAEKEY_LTGT */		INPUTEVENT_KEY_30,

    /* UAEKEY_NUMLOCK */	INPUTEVENT_ZERO,
    /* UAEKEY_NUMPAD_1 */	INPUTEVENT_KEY_NP_1,
    /* UAEKEY_NUMPAD_2 */	INPUTEVENT_KEY_NP_2,
    /* UAEKEY_NUMPAD_3 */	INPUTEVENT_KEY_NP_3,
    /* UAEKEY_NUMPAD_4 */	INPUTEVENT_KEY_NP_4,
    /* UAEKEY_NUMPAD_5 */	INPUTEVENT_KEY_NP_5,
    /* UAEKEY_NUMPAD_6 */	INPUTEVENT_KEY_NP_6,
    /* UAEKEY_NUMPAD_7 */	INPUTEVENT_KEY_NP_7,
    /* UAEKEY_NUMPAD_8 */	INPUTEVENT_KEY_NP_8,
    /* UAEKEY_NUMPAD_9 */	INPUTEVENT_KEY_NP_9,
    /* UAEKEY_NUMPAD_0 */	INPUTEVENT_KEY_NP_0,
    /* UAEKEY_NUMPAD_PERIOD */	INPUTEVENT_KEY_NP_PERIOD,
    /* UAEKEY_NUMPAD_PLUS */	INPUTEVENT_KEY_NP_ADD,
    /* UAEKEY_NUMPAD_MINUS */	INPUTEVENT_KEY_NP_SUB,
    /* UAEKEY_NUMPAD_MULTIPLY */INPUTEVENT_KEY_NP_MUL,
    /* UAEKEY_NUMPAD_DIVIDE */	INPUTEVENT_KEY_NP_DIV,
    /* UAEKEY_NUMPAD_ENTER */	INPUTEVENT_KEY_ENTER,
    /* UAEKEY_NUMPAD_EQUALS */  INPUTEVENT_ZERO,
    /* UAEKEY_NUMPAD_LPAREN */  INPUTEVENT_KEY_NP_LPAREN,
    /* UAEKEY_NUMPAD_RPAREN */  INPUTEVENT_KEY_NP_RPAREN,

    /* UAEKEY_INSERT */		INPUTEVENT_KEY_HELP,
    /* UAEKEY_DELETE */		INPUTEVENT_KEY_DEL,
    /* UAEKEY_HOME */		INPUTEVENT_ZERO,
    /* UAEKEY_END */		INPUTEVENT_ZERO,
    /* UAEKEY_PAGEUP */ 	INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_PAGEDOWN */	INPUTEVENT_KEY_AMIGA_LEFT,

    /* UAEKEY_CURSOR_UP */	INPUTEVENT_KEY_CURSOR_UP,
    /* UAEKEY_CURSOR_DOWN */	INPUTEVENT_KEY_CURSOR_DOWN,
    /* UAEKEY_CURSOR_LEFT */	INPUTEVENT_KEY_CURSOR_LEFT,
    /* UAEKEY_CURSOR_RIGHT */	INPUTEVENT_KEY_CURSOR_RIGHT,

    /* UAEKEY_LEFT_CTRL */	INPUTEVENT_KEY_CTRL,
    /* UAEKEY_LEFT_SHIFT */	INPUTEVENT_KEY_SHIFT_LEFT,
    /* UAEKEY_LEFT_ALT */	INPUTEVENT_KEY_ALT_LEFT,
    /* UAEKEY_LEFT_SUPER */	INPUTEVENT_KEY_AMIGA_LEFT,
    /* UAEKEY_RIGHT_SUPER */	INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_RIGHT_ALT */	INPUTEVENT_KEY_ALT_RIGHT,
    /* UAEKEY_MENU */		INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_RIGHT_SHIFT */	INPUTEVENT_KEY_SHIFT_RIGHT,
    /* UAEKEY_RIGHT_CTRL */	INPUTEVENT_KEY_CTRL_RIGHT,
    /* UAEKEY_CAPSLOCK */	INPUTEVENT_KEY_CAPS_LOCK,

    /* UAEKEY_HELP */		INPUTEVENT_KEY_HELP,

    /* UAEKEY_POWER */		INPUTEVENT_ZERO,
    /* UAEKEY_SLEEP */		INPUTEVENT_ZERO,
    /* UAEKEY_WAKE */		INPUTEVENT_ZERO
};

static struct uae_input_device_kbr_default keytrans[] = {

	{ DIK_ESCAPE, INPUTEVENT_KEY_ESC },

	{ DIK_F1, INPUTEVENT_KEY_F1 },
	{ DIK_F2, INPUTEVENT_KEY_F2 },
	{ DIK_F3, INPUTEVENT_KEY_F3 },
	{ DIK_F4, INPUTEVENT_KEY_F4 },
	{ DIK_F5, INPUTEVENT_KEY_F5 },

	{ DIK_F6, INPUTEVENT_KEY_F6 },
	{ DIK_F7, INPUTEVENT_KEY_F7 },
	{ DIK_F8, INPUTEVENT_KEY_F8 },
	{ DIK_F9, INPUTEVENT_KEY_F9 },
	{ DIK_F10, INPUTEVENT_KEY_F10 },

	{ DIK_1, INPUTEVENT_KEY_1 },
	{ DIK_2, INPUTEVENT_KEY_2 },
	{ DIK_3, INPUTEVENT_KEY_3 },
	{ DIK_4, INPUTEVENT_KEY_4 },
	{ DIK_5, INPUTEVENT_KEY_5 },
	{ DIK_6, INPUTEVENT_KEY_6 },
	{ DIK_7, INPUTEVENT_KEY_7 },
	{ DIK_8, INPUTEVENT_KEY_8 },
	{ DIK_9, INPUTEVENT_KEY_9 },
	{ DIK_0, INPUTEVENT_KEY_0 },

	{ DIK_TAB, INPUTEVENT_KEY_TAB },

	{ DIK_A, INPUTEVENT_KEY_A },
	{ DIK_B, INPUTEVENT_KEY_B },
	{ DIK_C, INPUTEVENT_KEY_C },
	{ DIK_D, INPUTEVENT_KEY_D },
	{ DIK_E, INPUTEVENT_KEY_E },
	{ DIK_F, INPUTEVENT_KEY_F },
	{ DIK_G, INPUTEVENT_KEY_G },
	{ DIK_H, INPUTEVENT_KEY_H },
	{ DIK_I, INPUTEVENT_KEY_I },
	{ DIK_J, INPUTEVENT_KEY_J },
	{ DIK_K, INPUTEVENT_KEY_K },
	{ DIK_L, INPUTEVENT_KEY_L },
	{ DIK_M, INPUTEVENT_KEY_M },
	{ DIK_N, INPUTEVENT_KEY_N },
	{ DIK_O, INPUTEVENT_KEY_O },
	{ DIK_P, INPUTEVENT_KEY_P },
	{ DIK_Q, INPUTEVENT_KEY_Q },
	{ DIK_R, INPUTEVENT_KEY_R },
	{ DIK_S, INPUTEVENT_KEY_S },
	{ DIK_T, INPUTEVENT_KEY_T },
	{ DIK_U, INPUTEVENT_KEY_U },
	{ DIK_W, INPUTEVENT_KEY_W },
	{ DIK_V, INPUTEVENT_KEY_V },
	{ DIK_X, INPUTEVENT_KEY_X },
	{ DIK_Y, INPUTEVENT_KEY_Y },
	{ DIK_Z, INPUTEVENT_KEY_Z },

	{ DIK_CAPITAL, INPUTEVENT_KEY_CAPS_LOCK, ID_FLAG_TOGGLE },

	{ DIK_NUMPAD1, INPUTEVENT_KEY_NP_1 },
	{ DIK_NUMPAD2, INPUTEVENT_KEY_NP_2 },
	{ DIK_NUMPAD3, INPUTEVENT_KEY_NP_3 },
	{ DIK_NUMPAD4, INPUTEVENT_KEY_NP_4 },
	{ DIK_NUMPAD5, INPUTEVENT_KEY_NP_5 },
	{ DIK_NUMPAD6, INPUTEVENT_KEY_NP_6 },
	{ DIK_NUMPAD7, INPUTEVENT_KEY_NP_7 },
	{ DIK_NUMPAD8, INPUTEVENT_KEY_NP_8 },
	{ DIK_NUMPAD9, INPUTEVENT_KEY_NP_9 },
	{ DIK_NUMPAD0, INPUTEVENT_KEY_NP_0 },
	{ DIK_DECIMAL, INPUTEVENT_KEY_NP_PERIOD },
	{ DIK_ADD, INPUTEVENT_KEY_NP_ADD },
	{ DIK_SUBTRACT, INPUTEVENT_KEY_NP_SUB },
	{ DIK_MULTIPLY, INPUTEVENT_KEY_NP_MUL },
	{ DIK_DIVIDE, INPUTEVENT_KEY_NP_DIV },
	{ DIK_NUMPADENTER, INPUTEVENT_KEY_ENTER },

	{ DIK_MINUS, INPUTEVENT_KEY_SUB },
	{ DIK_EQUALS, INPUTEVENT_KEY_EQUALS },
	{ DIK_BACK, INPUTEVENT_KEY_BACKSPACE },
	{ DIK_RETURN, INPUTEVENT_KEY_RETURN },
	{ DIK_SPACE, INPUTEVENT_KEY_SPACE },

	{ DIK_LSHIFT, INPUTEVENT_KEY_SHIFT_LEFT },
	{ DIK_LCONTROL, INPUTEVENT_KEY_CTRL },
	{ DIK_LWIN, INPUTEVENT_KEY_AMIGA_LEFT },
	{ DIK_LMENU, INPUTEVENT_KEY_ALT_LEFT },
	{ DIK_RMENU, INPUTEVENT_KEY_ALT_RIGHT },
	{ DIK_RWIN, INPUTEVENT_KEY_AMIGA_RIGHT },
	{ DIK_APPS, INPUTEVENT_KEY_AMIGA_RIGHT },
	{ DIK_RCONTROL, INPUTEVENT_KEY_CTRL_RIGHT },
	{ DIK_RSHIFT, INPUTEVENT_KEY_SHIFT_RIGHT },

	{ DIK_UP, INPUTEVENT_KEY_CURSOR_UP },
	{ DIK_DOWN, INPUTEVENT_KEY_CURSOR_DOWN },
	{ DIK_LEFT, INPUTEVENT_KEY_CURSOR_LEFT },
	{ DIK_RIGHT, INPUTEVENT_KEY_CURSOR_RIGHT },

	{ DIK_INSERT, INPUTEVENT_KEY_AMIGA_LEFT },
	{ DIK_DELETE, INPUTEVENT_KEY_DEL },
	{ DIK_HOME, INPUTEVENT_KEY_AMIGA_RIGHT },
	{ DIK_NEXT, INPUTEVENT_KEY_HELP },

	{ DIK_LBRACKET, INPUTEVENT_KEY_LEFTBRACKET },
	{ DIK_RBRACKET, INPUTEVENT_KEY_RIGHTBRACKET },
	{ DIK_SEMICOLON, INPUTEVENT_KEY_SEMICOLON },
	{ DIK_APOSTROPHE, INPUTEVENT_KEY_SINGLEQUOTE },
	{ DIK_GRAVE, INPUTEVENT_KEY_BACKQUOTE },
	{ DIK_BACKSLASH, INPUTEVENT_KEY_BACKSLASH },
	{ DIK_COMMA, INPUTEVENT_KEY_COMMA },
	{ DIK_PERIOD, INPUTEVENT_KEY_PERIOD },
	{ DIK_SLASH, INPUTEVENT_KEY_DIV },
	{ DIK_OEM_102, INPUTEVENT_KEY_30 },

	{ DIK_VOLUMEDOWN, INPUTEVENT_SPC_MASTER_VOLUME_DOWN },
	{ DIK_VOLUMEUP, INPUTEVENT_SPC_MASTER_VOLUME_UP },
	{ DIK_MUTE, INPUTEVENT_SPC_MASTER_VOLUME_MUTE },

	{ DIK_HOME, INPUTEVENT_KEY_70 },
	{ DIK_END, INPUTEVENT_KEY_71 },
	//    { DIK_SYSRQ, INPUTEVENT_KEY_6E },
	//    { DIK_F12, INPUTEVENT_KEY_6F },
	{ DIK_INSERT, INPUTEVENT_KEY_47 },
	//    { DIK_PRIOR, INPUTEVENT_KEY_48 },
	{ DIK_PRIOR, INPUTEVENT_SPC_FREEZEBUTTON },
	{ DIK_NEXT, INPUTEVENT_KEY_49 },
	{ DIK_F11, INPUTEVENT_KEY_4B },

	{ DIK_MEDIASTOP, INPUTEVENT_KEY_CDTV_STOP },
	{ DIK_PLAYPAUSE, INPUTEVENT_KEY_CDTV_PLAYPAUSE },
	{ DIK_PREVTRACK, INPUTEVENT_KEY_CDTV_PREV },
	{ DIK_NEXTTRACK, INPUTEVENT_KEY_CDTV_NEXT },

	{ -1, 0 }
};

static int kb_np[] = { DIK_NUMPAD4, -1, DIK_NUMPAD6, -1, DIK_NUMPAD8, -1, DIK_NUMPAD2, -1, DIK_NUMPAD0, DIK_NUMPAD5, -1, DIK_DECIMAL, -1, DIK_NUMPADENTER, -1, -1 };
static int kb_ck[] = { DIK_LEFT, -1, DIK_RIGHT, -1, DIK_UP, -1, DIK_DOWN, -1, DIK_RCONTROL, DIK_RMENU, -1, DIK_RSHIFT, -1, -1 };
static int kb_se[] = { DIK_A, -1, DIK_D, -1, DIK_W, -1, DIK_S, -1, DIK_LMENU, -1, DIK_LSHIFT, -1, -1 };
static int kb_np3[] = { DIK_NUMPAD4, -1, DIK_NUMPAD6, -1, DIK_NUMPAD8, -1, DIK_NUMPAD2, -1, DIK_NUMPAD0, DIK_NUMPAD5, -1, DIK_DECIMAL, -1, DIK_NUMPADENTER, -1, -1 };
static int kb_ck3[] = { DIK_LEFT, -1, DIK_RIGHT, -1, DIK_UP, -1, DIK_DOWN, -1, DIK_RCONTROL, -1, DIK_RSHIFT, -1, DIK_RMENU, -1, -1 };
static int kb_se3[] = { DIK_A, -1, DIK_D, -1, DIK_W, -1, DIK_S, -1, DIK_LMENU, -1, DIK_LSHIFT, -1, DIK_LCONTROL, -1, -1 };

static int kb_cd32_np[] = { DIK_NUMPAD4, -1, DIK_NUMPAD6, -1, DIK_NUMPAD8, -1, DIK_NUMPAD2, -1, DIK_NUMPAD0, DIK_NUMPAD5, DIK_NUMPAD1, -1, DIK_DECIMAL, DIK_NUMPAD3, -1, DIK_NUMPAD7, -1, DIK_NUMPAD9, -1, DIK_DIVIDE, -1, DIK_SUBTRACT, -1, DIK_MULTIPLY, -1, -1 };
static int kb_cd32_ck[] = { DIK_LEFT, -1, DIK_RIGHT, -1, DIK_UP, -1, DIK_DOWN, -1, DIK_RCONTROL, -1, DIK_RMENU, -1, DIK_NUMPAD7, -1, DIK_NUMPAD9, -1, DIK_DIVIDE, -1, DIK_SUBTRACT, -1, DIK_MULTIPLY, -1, -1 };
static int kb_cd32_se[] = { DIK_A, -1, DIK_D, -1, DIK_W, -1, DIK_S, -1, -1, DIK_LMENU, -1, DIK_LSHIFT, -1, DIK_NUMPAD7, -1, DIK_NUMPAD9, -1, DIK_DIVIDE, -1, DIK_SUBTRACT, -1, DIK_MULTIPLY, -1, -1 };

static int kb_cdtv[] = { DIK_NUMPAD1, -1, DIK_NUMPAD3, -1, DIK_NUMPAD7, -1, DIK_NUMPAD9, -1, -1 };

static int kb_xa1[] = { DIK_NUMPAD4, -1, DIK_NUMPAD6, -1, DIK_NUMPAD8, -1, DIK_NUMPAD2, DIK_NUMPAD5, -1, DIK_LCONTROL, -1, DIK_LMENU, -1, DIK_SPACE, -1, -1 };
static int kb_xa2[] = { DIK_D, -1, DIK_G, -1, DIK_R, -1, DIK_F, -1, DIK_A, -1, DIK_S, -1, DIK_Q, -1 };
static int kb_arcadia[] = { DIK_F2, -1, DIK_1, -1, DIK_2, -1, DIK_5, -1, DIK_6, -1, -1 };
static int kb_arcadiaxa[] = { DIK_1, -1, DIK_2, -1, DIK_3, -1, DIK_4, -1, DIK_6, -1, DIK_LBRACKET, DIK_LSHIFT, -1, DIK_RBRACKET, -1, DIK_C, -1, DIK_5, -1, DIK_Z, -1, DIK_X, -1, -1 };

static int *kbmaps[] = {
	kb_np, kb_ck, kb_se, kb_np3, kb_ck3, kb_se3,
	kb_cd32_np, kb_cd32_ck, kb_cd32_se,
	kb_xa1, kb_xa2, kb_arcadia, kb_arcadiaxa, kb_cdtv
};

/*
 * Build a default key translation table using the
 * specified host keymap.
 */
void keyboard_settrans (void)
{
	inputdevice_setkeytranslation (keytrans, kbmaps);
}

struct uae_input_device_kbr_default *uaekey_make_default_kbr (const struct uaekey_hostmap *hostkeys)
{
	int i;
	int count;
	struct uae_input_device_kbr_default *trans;

	for (i = 0; i < 256 && hostkeys[i].hostkey != -1; i++);

	if (i == 256)
		abort ();

	count = i;

	trans = (struct uae_input_device_kbr_default*) malloc (sizeof (struct uae_input_device_kbr_default) * (count + 1));

	if (trans) {
		for (i = 0; i < count; i++) {
			trans[i].scancode	= hostkeys[i].hostkey;
			trans[i].evt		= default_keymap[hostkeys[i].uaekey];
		}
		trans[i].scancode = -1;
	}

	return trans;
};