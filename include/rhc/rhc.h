#ifndef RHC_RHC_H
#define RHC_RHC_H

#include "types.h"
#include "error.h"
#include "log.h"
#include "time.h"
#include "allocator.h"
#include "file.h"
#include "str.h"
#include "string.h"
#include "str_parse.h"


#ifdef RHC_IMPL
#include "impl/error_impl.h"
#include "impl/log_impl.h"
#include "impl/allocator_impl.h"
#include "impl/file_impl.h"
#endif

#endif //RHC_RHC_H
