#include <glib.h>

#include "window-scale.h"

#define HIDPI_LIMIT (96 * 2)

/* 14" 2560x1440 laptop panel, 210 dpi */
#define LAPTOP_HIDPI { 2560, 1440, 309, 174, 1 }
/* Same panel set to 1600x900, 131 dpi */
#define LAPTOP_LOWRES { 1600, 900, 309, 174, 1 }
/* 27" 2560x1440 monitor, 109 dpi */
#define EXTERNAL_QHD { 2560, 1440, 597, 336, 1 }
/* 27" 3840x2160 monitor, 163 dpi */
#define EXTERNAL_UHD_27 { 3840, 2160, 597, 336, 1 }
/* 24" 3840x2160 monitor, 184 dpi */
#define EXTERNAL_UHD_24 { 3840, 2160, 527, 296, 1 }
/* 15.6" 3840x2160 laptop panel, 282 dpi */
#define LAPTOP_UHD { 3840, 2160, 346, 194, 1 }

static void
test_window_scale (void)
{
  static const struct {
    const char *name;
    MonitorSize monitors[3];
    int n_monitors;
    int expected;
  } tests[] = {
    { "no monitors", { { 0 } }, 0, 1 },
    { "HiDPI laptop", { LAPTOP_HIDPI }, 1, 2 },
    { "laptop below native resolution", { LAPTOP_LOWRES }, 1, 1 },
    { "HiDPI laptop and QHD external", { LAPTOP_HIDPI, EXTERNAL_QHD }, 2, 1 },
    { "QHD external and HiDPI laptop", { EXTERNAL_QHD, LAPTOP_HIDPI }, 2, 1 },
    { "HiDPI laptop and two HiDPI externals", { LAPTOP_HIDPI, LAPTOP_UHD, LAPTOP_UHD }, 3, 2 },
    { "HiDPI laptop and 24\" UHD external", { LAPTOP_HIDPI, EXTERNAL_UHD_24 }, 2, 1 },
    { "27\" UHD external only", { EXTERNAL_UHD_27 }, 1, 1 },
    { "aspect ratio 160x90 mm", { { 3840, 2160, 160, 90, 1 } }, 1, 1 },
    { "aspect ratio 160x100 mm", { { 3840, 2400, 160, 100, 1 } }, 1, 1 },
    { "aspect ratio 16x9 mm", { { 3840, 2160, 16, 9, 1 } }, 1, 1 },
    { "aspect ratio 16x10 mm", { { 3840, 2400, 16, 10, 1 } }, 1, 1 },
    { "unknown physical size", { { 3840, 2160, 0, 0, 1 } }, 1, 1 },
    { "HiDPI laptop and unknown external", { LAPTOP_HIDPI, { 1920, 1080, 0, 0, 1 } }, 2, 1 },
    { "only one axis HiDPI", { { 2560, 1440, 309, 300, 1 } }, 1, 1 },
  };
  guint i;

  for (i = 0; i < G_N_ELEMENTS (tests); i++)
    {
      int scale;

      scale = get_auto_window_scale (tests[i].monitors, tests[i].n_monitors, HIDPI_LIMIT);
      if (scale != tests[i].expected)
        g_error ("%s: expected %d, got %d", tests[i].name, tests[i].expected, scale);
    }
}

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);
  g_test_add_func ("/xsettings/window-scale", test_window_scale);
  return g_test_run ();
}
