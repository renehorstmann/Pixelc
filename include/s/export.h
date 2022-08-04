#ifndef S_EXPORT_H
#define S_EXPORT_H

//
// to mark functions as library export function
//

#if (defined _WIN32 || defined WINCE || defined __CYGWIN__)
#define S_EXPORT __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#define S_EXPORT __attribute__ ((visibility ("default")))
#else
#define S_EXPORT
#endif

#endif //S_EXPORT_H
