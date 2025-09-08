#include "display.h"

#include <ncurses.h>
#include <panel.h>

#include <stdbool.h>

/*** GOOD IDEA THANKS CHAT! ***/

// static const display_state_t DEFAULT_STATE = {
//     .theme = THEME_MATRIX,
//     .cursor_visible = 0,
//     .auto_refresh = 1
// };

/******************************/

// Window resizing:

// wresize(window, new_lines, new_cols) - Resize the window
// mvwin(window, new_y, new_x) - Move the window to new position

// Panel management:

// replace_panel(panel, new_window) - Replace the window associated with a panel
// move_panel(panel, new_y, new_x) - Move the panel to new position

// Display updates:

// update_panels() - Update all panels after changes
// doupdate() - Refresh the screen

// Terminal size detection:

// getmaxyx(stdscr, max_y, max_x) - Get current terminal size
// Handle SIGWINCH signal to detect when terminal is resized

// The typical flow is: detect resize → wresize() → replace_panel() → update_panels() → doupdate()


static const display_theme DEFAULT = THEME_DEFAULT;

static bool WINDOWS_INITIALIZED = false;
static bool PANELS_INITIALIZED = false;

static int  initialize_windows(display_t* display);
static int  initialize_panels(display_t* display);
static void cleanup_panels(display_t* display);

static int d_initialize_themes();

int d_ncurses_init()
{
  if (initscr() == NULL) {
    fprintf(stderr, "Error initializing ncurses\n");
    return -1;
  }

  if (has_colors()) {
    d_initialize_themes();
    start_color();   
  }

  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE); // FALSE MEANS BLOCKING INPUT ON GETCH!

  return 0;
}

void d_ncurses_shutdown()
{
  endwin();
}

int display_init(display_t* display)
{
  if (initialize_windows(display) == 1) {
    return 1;
  }

  if (initialize_panels(display) == 1) {
    return 1;
  }

  display_set_theme(display, DEFAULT);

  return 0; 
}

void display_cleanup(display_t* display)
{
  if (PANELS_INITIALIZED) {
    cleanup_panels(display);
  }

  if (WINDOWS_INITIALIZED) {
    cleanup_windows(display);
  }

  display_set_theme(display, DEFAULT);
}

static void cleanup_panels(display_t* display)
{
  del_panel(display->PANEL_MEMORY);
  del_panel(display->PANEL_SELECTOR);
  del_panel(display->PANEL_HUD);

  display->PANEL_MEMORY =   NULL;
  display->PANEL_SELECTOR = NULL;
  display->PANEL_HUD =      NULL;
}

static void cleanup_windows(display_t* display)
{
  delwin(display->WINDOW_MEMORY);
  delwin(display->WINDOW_SELECTOR);
  delwin(display->WINDOW_HUD);

  display->WINDOW_MEMORY =   NULL;
  display->WINDOW_SELECTOR = NULL;
  display->WINDOW_HUD =      NULL;
}

static int initialize_windows(display_t* display)
{
  display->WINDOW_MEMORY =   newwin(1, 1, 0, 0);
  display->WINDOW_SELECTOR = newwin(1, 1, 0, 0);
  display->WINDOW_HUD =      newwin(1, 1, 0, 0);

  if (display->WINDOW_MEMORY   == NULL ||
      display->WINDOW_SELECTOR == NULL ||
      display->WINDOW_HUD      == NULL) {
    return 1;
  }

  return 0;
}

void display_set_theme(display_t* display, display_theme theme)
{
  display->theme = theme;
}

static int initialize_panels(display_t* display)
{
  display->PANEL_MEMORY =   new_panel(display->PANEL_MEMORY);
  display->PANEL_SELECTOR = new_panel(display->PANEL_SELECTOR);
  display->PANEL_HUD =      new_panel(display->PANEL_HUD);

  if (display->PANEL_MEMORY   == NULL ||
      display->PANEL_SELECTOR == NULL ||
      display->PANEL_HUD      == NULL) {
    return 1;
  }

  return 0;
}

static int d_initialize_themes()
{
  init_pair(THEME_MATRIX, COLOR_GREEN, COLOR_BLACK);
  init_pair(THEME_PINKY, COLOR_MAGENTA, COLOR_BLACK);
  return 0;
}



