/* disputils randr.h 04/15/2016 tudurom <xenogenesis@openmailbox.org>
 * ix <arcetera@openmailbox.org>
 */

#ifndef WMUTILS_RANDR
#define WMUTILS_RANDR

#include <xcb/xcb.h>
#include <xcb/randr.h>
#include <stdlib.h>
#include <err.h>

/* Return the list of outputs provided by a provider. */
int get_outputs(xcb_connection_t* conn, xcb_randr_provider_t provider, xcb_randr_output_t** os);

/* Return an array of providers shown by randr. */
int get_providers(xcb_connection_t* con, xcb_screen_t* scrn, xcb_randr_provider_t **ps);

/* Return info about an output */
xcb_randr_get_output_info_reply_t *get_output_info(xcb_connection_t* conn, xcb_randr_output_t output);

/* Return an output's name */
uint8_t* get_output_name(xcb_connection_t* conn, xcb_randr_output_t output);

int get_output_connection(xcb_connection_t* conn, xcb_randr_output_t output);

/* Return an output's crtc info */
xcb_randr_get_crtc_info_reply_t * get_output_crtc_info(xcb_connection_t* conn, xcb_randr_crtc_t crtc);

/* Return the id of the currently focused window */
xcb_window_t get_focused_window(xcb_connection_t *conn);

/* Return a window's geometry (width, height, x, y) */
xcb_get_geometry_reply_t* get_window_geometry(xcb_connection_t *conn, xcb_window_t window);

/* Return the primary output (display) */
xcb_randr_get_output_primary_reply_t* get_primary_output(xcb_connection_t *conn);

#endif /* end of include guard: WMUTILS_RANDR */
