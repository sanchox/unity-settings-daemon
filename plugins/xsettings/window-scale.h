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

#ifndef __WINDOW_SCALE_H__
#define __WINDOW_SCALE_H__

typedef struct {
        int width;
        int height;
        int width_mm;
        int height_mm;
        int scale;
} MonitorSize;

int get_auto_window_scale (const MonitorSize *monitors,
                           int                n_monitors,
                           double             hidpi_limit);

#endif
