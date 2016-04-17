/* disputils ppd.c 04/17/2016 tudurom <xenogenesis@openmailbox.org>
 * ix <arcetera@openmailbox.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "randr.h"
#include "util.h"

xcb_connection_t *conn;
xcb_screen_t *scrn;

void
usage(char *name)
{
    printf("usage: %s \n", name);
    exit(0);
}

int
main(int argc, char *argv[])
{
    xcb_randr_get_output_primary_reply_t *primary_output;
    xcb_window_t root;

    if (argc > 1) usage(argv[0]);
    init_xcb(&conn);
    get_screen(conn, &scrn);
    root = scrn->root;

    primary_output = get_primary_output(conn);

    printf("%s\n", get_output_name(conn, primary_output->output));
    return 0;
}
