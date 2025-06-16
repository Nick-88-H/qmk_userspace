#pragma once

#undef NKRO_ENABLE
#undef FORCE_NKRO
#define NKRO_ENABLE 0
#define FORCE_NKRO OFF

#define NO_ACTION_KEYBOARD
#define NO_USB_NKRO

#define NO_MOUSEKEY
#define NO_EXTRAKEY
#define NO_MIDI
#define NO_SERIAL
#define NO_STENO

// * THE NUCLEAR PATCH *
#define send_nkro(...)  // disables the broken call in usb_main.c
