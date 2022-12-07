#ifndef U_BILLING_H
#define U_BILLING_H

//
// Buy stuff from Google Play billing on Android
//

#include "s/s.h"

// return true to consume the purchase
typedef bool (*u_billing_purchased_fn)(int idx, void *user_data);

// makes an "expensive" jni call
bool u_billing_loaded();

// the u_billing_purchased_fn callback should always be the same
void u_billing_buy(int idx, u_billing_purchased_fn callback, void *callback_user_data);

#endif //U_BILLING_H
