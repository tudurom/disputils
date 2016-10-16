/* See LICENSE file for copyright and license details. */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "randr.h"
#include "util.h"

xcb_connection_t *conn;
xcb_screen_t     *scrn;

void
usage(char *name)
{
	printf("usage: %s \n", name);
	exit(0);
}

int
main(int argc, char *argv[])
{
#ifdef __OpenBSD__
	if (pledge("stdio rpath unix", NULL) == -1)
		err(1, "pledge");
#endif
	xcb_window_t f_window;
	xcb_get_geometry_reply_t *window_geometry = NULL;

	uint16_t window_x;
	uint16_t window_y;

	xcb_randr_get_output_info_reply_t *output_info = NULL;
	xcb_randr_get_crtc_info_reply_t *output_crtc_info = NULL;
	xcb_randr_output_t output;
	const char *output_name = NULL;

	uint16_t output_w;
	uint16_t output_h;
	uint16_t output_x;
	uint16_t output_y;

	if (argc > 1)
		usage(argv[0]);
	init_xcb(&conn);
	get_screen(conn, &scrn);

	/* Get info about the focused window */
	f_window = get_focused_window(conn);
	window_geometry = get_window_geometry(conn, f_window);
	window_x = window_geometry->x;
	window_y = window_geometry->y;

	/* Iterate through outputs */
	xcb_randr_provider_t *providers;
	int p_len = get_providers(conn, scrn, &providers);

	int i = 0;
	while (i < p_len && output_name == '\0') {
		xcb_randr_output_t *os;
		int o_len = get_outputs(conn, providers[i], &os);

		int j = 0;
		while (j < o_len && output_name == '\0') {
			output = os[j];
			if (get_output_connection(conn, output) == 0) {
				/* Check */
				output_info = get_output_info(conn, output);
				output_crtc_info = get_output_crtc_info(conn, output_info->crtc);
				if (output_crtc_info != NULL) {
					output_w = output_crtc_info->width;
					output_h = output_crtc_info->height;
					output_x = output_crtc_info->x;
					output_y = output_crtc_info->y;

					if (window_x >= output_x &&
						window_y >= output_y &&
					  window_x <= output_x + output_w &&
					  window_y <= output_y + output_h) {

						output_name = (const char *)get_output_name(conn, output);
					}
				}
			}
			j++;
		}

		i++;
	}
	if (output_name == '\0')
		errx(1, "Cannot get output name");
	printf("%s\n", output_name);
	free(window_geometry);
	free(output_info);
	free(output_crtc_info);
	return 0;
}
