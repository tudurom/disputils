/* disputils randr.h 04/15/2016 tudurom <unknown>
 * ix <arcetera@openmailbox.org
 */

#ifndef RANDR_H__
#define RANDR_H__

#include <xcb/xcb.h>
#include <xcb/randr.h>
#include <err.h>

/* return the list of outputs provided by a provider */
int
get_outputs(xcb_connection_t* conn, xcb_randr_provider_t provider, xcb_randr_output_t** os);

/* return an array of providers shown by randr */
int
get_providers(xcb_connection_t* con, xcb_screen_t* scrn, xcb_randr_provider_t **ps);

uint8_t* get_output_name(xcb_connection_t* conn, xcb_randr_output_t output);
int get_output_connection(xcb_connection_t* conn, xcb_randr_output_t output);

#endif /* end of include guard: RANDR_H__ */
