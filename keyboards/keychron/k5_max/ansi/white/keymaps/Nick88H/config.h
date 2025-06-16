#pragma once

#undef NKRO_ENABLE
#undef FORCE_NKRO
#define NKRO_ENABLE 0
#define FORCE_NKRO OFF

#define NO_ACTION_KEYBOARD  // disables fallback in action_util
#define NO_USB_NKRO         // disables NKRO path in usb_main.c

#define NO_MOUSEKEY
#define NO_EXTRAKEY
#define NO_MIDI
#define NO_SERIAL
#define NO_STENO
