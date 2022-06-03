#ifndef RHC_RHC_H
#define RHC_RHC_H

// includes the basics of rhc

#include "systemincludes.h"
#include "types.h"
#include "error.h"
#include "assume.h"
#include "alloc.h"
#include "log.h"

#ifdef RHC_IMPL
#include "impl/assume_impl.h"
#include "impl/error_impl.h"
#include "impl/terminalcolor_impl.h"
#include "impl/log_impl.h"
#include "impl/alloc_impl.h"
#include "impl/file_impl.h"
#include "impl/stream_impl.h"
#include "impl/socket_impl.h"
#endif

#endif //RHC_RHC_H
