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
    xcb_randr_output_t output = -1;
    char *output_name;

    if (argc != 2) usage(argv[0]);
    output_name = argv[1];

    init_xcb(&conn);
    get_screen(conn, &scrn);

    xcb_randr_provider_t* providers;
    int p_len = get_providers(conn, scrn, &providers);

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
    return 0;
}
