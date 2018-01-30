#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/text_editor.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

void text_loop(){
  while(1){
    char user_input = get_char();
    if(user_input =='\r'){
        break;
    }
    printf("%c", user_input);
  }
}
