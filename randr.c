/* disputils randr.c 04/15/2016 tudurom <xenogenesis@openmailbox.org>
 * ix <arcetera@openmailbox.org
 */

#include <xcb/randr.h>
#include "util.h"
#include "randr.h"

int
get_providers(xcb_connection_t* conn, xcb_screen_t* scrn, xcb_randr_provider_t **ps)
{ /* get all providers */
    xcb_randr_get_providers_cookie_t pc;
    pc = xcb_randr_get_providers(conn, scrn->root);

    xcb_randr_get_providers_reply_t *pr;
    pr = xcb_randr_get_providers_reply(conn, pc, NULL);
    if (!pr)
        errx(1, "Could not aquire the array of providers.");

    *ps = xcb_randr_get_providers_providers(pr);

    return xcb_randr_get_providers_providers_length(pr);
}

int
get_outputs(xcb_connection_t* conn, xcb_randr_provider_t provider, xcb_randr_output_t** os)
{ /* get array of outputs */
    xcb_randr_get_provider_info_cookie_t pic;
    pic = xcb_randr_get_provider_info(conn, provider, 0);

    xcb_randr_get_provider_info_reply_t *pir;
    pir = xcb_randr_get_provider_info_reply(conn, pic, NULL);
    if (!pir)
        errx(1, "Could not aquire the array of outputs.");

    *os = xcb_randr_get_provider_info_outputs(pir);
    return xcb_randr_get_provider_info_outputs_length(pir);
}

xcb_randr_get_output_info_reply_t *
get_output_info(xcb_connection_t* conn, xcb_randr_output_t output)
{ /* get info about the output like crtc, modes etc */
    xcb_randr_get_output_info_cookie_t oic;

    oic = xcb_randr_get_output_info(conn, output, 0);
    xcb_randr_get_output_info_reply_t *output_info_reply;

    output_info_reply = xcb_randr_get_output_info_reply(conn, oic, NULL);
    if (!output_info_reply)
        errx(1, "Could not get output info.");

    return output_info_reply;
}

uint8_t* get_output_name(xcb_connection_t* conn, xcb_randr_output_t output)
{ /* get output's name, like LVDS-1 */
    xcb_randr_get_output_info_reply_t* r;
    r = get_output_info(conn, output);
    return xcb_randr_get_output_info_name(r);
}

int get_output_connection(xcb_connection_t* conn, xcb_randr_output_t output)
{ /* returns 0 if the output is connected */
    xcb_randr_get_output_info_reply_t* r;
    r = get_output_info(conn, output);
    return r->connection;
}

xcb_randr_get_crtc_info_reply_t *
get_output_crtc_info(xcb_connection_t* conn, xcb_randr_crtc_t crtc)
{ /* get crtc info (width, height, x, y, ...) */
    xcb_randr_get_crtc_info_cookie_t cic;

    cic = xcb_randr_get_crtc_info(conn, crtc, 0);

    xcb_randr_get_crtc_info_reply_t *crtc_info_reply;
    crtc_info_reply = xcb_randr_get_crtc_info_reply(conn, cic, NULL);
    if (!crtc_info_reply)
        errx(1, "Output not in use");

    return crtc_info_reply;
}

xcb_window_t
get_focused_window(xcb_connection_t *conn)
{ /* returns the id of the focused window */
    xcb_window_t win = 0;
    xcb_get_input_focus_cookie_t input_focus_cookie;
    xcb_get_input_focus_reply_t *input_focus_reply;

    input_focus_cookie = xcb_get_input_focus(conn);
    input_focus_reply = xcb_get_input_focus_reply(conn, input_focus_cookie, NULL);
    if (!input_focus_reply)
        errx(1, "Cannot get focused window.");
    win = input_focus_reply->focus;
    free(input_focus_reply);
    return win;
}

xcb_get_geometry_reply_t*
get_window_geometry(xcb_connection_t *conn, xcb_window_t window)
{ /* returns the geometry of a window (width, height, x, y) */
    xcb_get_geometry_cookie_t get_geometry_cookie;
    xcb_get_geometry_reply_t *get_geometry_reply;

    get_geometry_cookie = xcb_get_geometry(conn, window);
    get_geometry_reply = xcb_get_geometry_reply(conn, get_geometry_cookie, NULL);

    if (!get_geometry_reply)
        errx(1, "0x%08x: no such window", window);
    return get_geometry_reply;
}

xcb_randr_get_output_primary_reply_t*
get_primary_output(xcb_connection_t *conn)
{ /* returns the primary output (display) */
    xcb_screen_t *scrn;
    xcb_window_t root;
    xcb_randr_get_output_primary_cookie_t c;
    xcb_randr_get_output_primary_reply_t *primary_output;

    get_screen(conn, &scrn);
    root = scrn->root;

    c = xcb_randr_get_output_primary(conn, root);
    primary_output = xcb_randr_get_output_primary_reply(conn, c, NULL);

    return primary_output;
}
