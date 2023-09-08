#include "os.h"

#ifdef BASE_OS_WIN
#  include "os_win.c"
#else
#  error OS support not implemented.
#endif