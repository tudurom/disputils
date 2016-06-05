/*
 * disputils util.h 04/15/2016 tudurom <xenogenesis@openmailbox.org> ix
 * <arcetera@openmailbox.org
 */

#ifndef UTIL_H__
#define UTIL_H__

void        init_xcb (xcb_connection_t **);
void        kill_xcb (xcb_connection_t **);

void        get_screen(xcb_connection_t *, xcb_screen_t **);
int         get_windows(xcb_connection_t *, xcb_window_t, xcb_window_t **);

int         exists    (xcb_connection_t *, xcb_window_t);
int         mapped    (xcb_connection_t *, xcb_window_t);
int         ignore    (xcb_connection_t *, xcb_window_t);

#endif
