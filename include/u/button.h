#ifndef U_BUTTON_H
#define U_BUTTON_H

//
// simple button
// sprite.x:
//    0 = unpressed
//    1 = pressed
// pointer.pos coordinates should be in the same 
//     coordination system as the rect
//

#include "e/input.h"
#include "r/rect.h"

// returns true if the button is pressed (sprite.x>0.5)
bool u_button_is_pressed(rRect_s *self);

// sets the button pressed (sprite.x = 1)
void u_button_set_pressed(rRect_s *self, bool pressed);

// returns true, if the button was pressed and unpressed
// so on POINTER_UP
bool u_button_clicked(rRect_s *self, ePointer_s pointer);

// returns true, if the button is pressed
// so on POINTER_DOWN
bool u_button_pressed(rRect_s *self, ePointer_s pointer);

// returns true if the button was pressed and changes its state (pressed-unpressed)
// good for radio button groups or active/not activr modes
bool u_button_toggled(rRect_s *self, ePointer_s pointer);

#endif //U_BUTTON_H
