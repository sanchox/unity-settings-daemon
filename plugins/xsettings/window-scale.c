/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "window-scale.h"

static int
monitor_is_hidpi (const MonitorSize *monitor,
                  double             hidpi_limit)
{
        double dpi_x, dpi_y;

        /* Somebody encoded the aspect ratio (16/9 or 16/10)
         * instead of the physical size */
        if ((monitor->width_mm == 160 && monitor->height_mm == 90) ||
            (monitor->width_mm == 160 && monitor->height_mm == 100) ||
            (monitor->width_mm == 16 && monitor->height_mm == 9) ||
            (monitor->width_mm == 16 && monitor->height_mm == 10))
                return 0;

        if (monitor->width_mm <= 0 || monitor->height_mm <= 0)
                return 0;

        dpi_x = (double)monitor->width * monitor->scale / (monitor->width_mm / 25.4);
        dpi_y = (double)monitor->height * monitor->scale / (monitor->height_mm / 25.4);

        /* We don't completely trust these values so both
           must be high */
        return dpi_x > hidpi_limit && dpi_y > hidpi_limit;
}

/* The X11 window scale applies to all monitors. Never pick higher
 * ratio than 2 automatically, and pick 2 only when every monitor
 * is HiDPI: scale 2 on a low DPI monitor makes it unusable. */
int
get_auto_window_scale (const MonitorSize *monitors,
                       int                n_monitors,
                       double             hidpi_limit)
{
        int i;

        if (n_monitors <= 0)
                return 1;

        for (i = 0; i < n_monitors; i++) {
                if (!monitor_is_hidpi (&monitors[i], hidpi_limit))
                        return 1;
        }

        return 2;
}
