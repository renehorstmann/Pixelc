#ifndef U_ADMOB_H
#define U_ADMOB_H

//
// Can show an Google AdMob reward ad video on android
//

#include "s/s.h"

typedef void (*u_admob_reward_fn)(void *user_data);

// makes an "expensive" jni call
bool u_admob_reward_ad_loaded();

// the u_admob_reward_fn callback should always be the same
void u_admob_reward_ad_show(u_admob_reward_fn callback, void *callback_user_data);

#endif //U_ADMOB_H
