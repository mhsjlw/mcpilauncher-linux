#include <string.h>

#include "dll.h"

typedef enum {
  SDL_SYSWM_X11
} SDL_SYSWM_TYPE;

typedef struct {
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
} SDL_version;

typedef unsigned long Window;

typedef struct {
  SDL_version version;
  SDL_SYSWM_TYPE subsystem;
  union {
    struct {
      void* display;
      Window window;

      int filler; // XXX

      void (*lock_func)(void);
      void (*unlock_func)(void);

      Window fswindow;
      Window wmwindow;

      void* gfxdisplay;
    } x11;
  } info;
} SDL_SysWMinfo;

FUNCTION_0(SDL_Quit)
FUNCTION_4(SDL_SetVideoMode)
FUNCTION_1(SDL_Init)
FUNCTION_2(SDL_WM_SetCaption)
FUNCTION_1(SDL_WM_GrabInput)
FUNCTION_1(SDL_ShowCursor)

static void x_lock_function(void) {
  SYSCALL(NULL);
}

static void x_unlock_function(void) {
  SYSCALL(NULL);
}

int SDL_PollEvent(void* a) {
  uint32_t s[1] = { (uint32_t) a };
  SYSCALL(&s);
}

int SDL_GetWMInfo(void* a) {
  memset(a, 0, sizeof(SDL_SysWMinfo));
  SDL_SysWMinfo* info = (SDL_SysWMinfo*) a;

  info->info.x11.lock_func = x_lock_function;
  info->info.x11.unlock_func = x_unlock_function;

  return 1;
}
