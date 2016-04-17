/* disputils randr.c 04/15/2016 tudurom <xenogenesis@openmailbox.org>
 * ix <arcetera@openmailbox.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "randr.h"
#include "util.h"

static xcb_connection_t *conn;
static xcb_screen_t *scrn;

static void
usage(char *name)
{
    printf("usage: [whxy] %s \n", name);
    exit(0);
}

int
main(int argc, char *argv[])
{
    xcb_randr_output_t output = -1;
    xcb_randr_get_output_info_reply_t *output_info = NULL;
    xcb_randr_crtc_t screen_crtc;
    xcb_randr_get_crtc_info_reply_t *screen_crtc_info = NULL;
    char *output_name;

    if (argc != 3) usage(argv[0]);
    output_name = argv[2];

    init_xcb(&conn);
    get_screen(conn, &scrn);

    xcb_randr_provider_t* providers;
    int p_len = get_providers(conn, scrn, &providers);

    /* get the id of the output */
    int i = 0;
    while (i < p_len && output == -1) {
        xcb_randr_output_t *os;
        int o_len = get_outputs(conn, providers[i], &os);

        int j = 0;
        while (j < o_len && output == -1) {
            if (strcmp(output_name, (const char *)get_output_name(conn, os[j])) == 0)
                output = os[j];

            j++;
        }

        i++;
    }

    if (output == -1) {
        errx(1, "Output not found");
    }
    output_info = get_output_info(conn, output);

    /* get info about output */
    screen_crtc = output_info->crtc;
    screen_crtc_info = get_output_crtc_info(conn, screen_crtc);
    if (!screen_crtc_info)
        errx(1, "Output not in use");

    /* print info */
    for (int i = 0; i < strlen(argv[1]); i++) {
        switch (argv[1][i]) {
            case 'w':
                printf("%d", screen_crtc_info->width);
                break;
            case 'h':
                printf("%d", screen_crtc_info->height);
                break;
            case 'x':
                printf("%d", screen_crtc_info->x);
                break;
            case 'y':
                printf("%d", screen_crtc_info->y);
                break;
        }
        /* print a space if more attributes come after */
        putc(i + 1 < strlen(argv[1]) ? ' ' : '\n', stdout);
    }
    free(output_info);
    free(screen_crtc_info);
    kill_xcb(&conn);
    return 0;
}
