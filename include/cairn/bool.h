#ifndef CAIRN_BOOL_H
#define CAIRN_BOOL_H

#include <cairn/config.h>

#if CAIRN_USE_STDBOOL
#    include <stdbool.h>
#endif

typedef CAIRN_BOOL_TYPE cairn_bool;

#define CAIRN_FALSE (0 != 0)
#define CAIRN_TRUE  (0 == 0)

#endif
