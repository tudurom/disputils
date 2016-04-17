/* disputils lsd.c 04/15/2016 tudurom <xenogenesis@openmailbox.org>
 * ix <arcetera@openmailbox.org
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
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

void
print_output(xcb_connection_t* conn, xcb_randr_output_t output)
{
    uint8_t* name = get_output_name(conn, output);
    if (get_output_connection(conn, output) == 0) {
        printf("%s\n", name);
    }
}

int
main(int argc, char *argv[])
{
    if (argc > 1) usage(argv[0]);
    init_xcb(&conn);
    get_screen(conn, &scrn);

    xcb_randr_provider_t* providers;
    int p_len = get_providers(conn, scrn, &providers);

    for (int i = 0; i < p_len; ++i) {
        xcb_randr_output_t* os;
        int o_len = get_outputs(conn, providers[i], &os);

        /* Print screens from providers */
        for (int j = 0; j < o_len; ++j) {
            print_output(conn, os[j]);
        }
    }
    return 0;
}
