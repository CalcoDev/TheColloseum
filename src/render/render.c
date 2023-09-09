#include "render.h"

#ifdef BASE_GRAPHICS_BACKEND_GL33
#  include "render_gl33.c"
#else
#  error Backend support not implemented.
#endif