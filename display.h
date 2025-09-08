#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <panel.h>

typedef enum
{
  THEME_DEFAULT = 0, // standard terminal look
  THEME_MATRIX,      // green on black matrix style
  THEME_PINKY        // some sweet-ass pinky eye burner
} display_theme;

typedef struct display_s {

  WINDOW*         WINDOW_MEMORY;
  PANEL*          PANEL_MEMORY;

  WINDOW*         WINDOW_SELECTOR;
  PANEL*          PANEL_SELECTOR;

  WINDOW*         WINDOW_HUD;
  PANEL*          PANEL_HUD;

  display_theme  theme;

} display_t;

int display_init();  // 0 on success else 1
void display_cleanup();
void display_set_theme(display_t* display, display_theme theme);




#endif