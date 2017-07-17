# morpion

## Server morpion localhost with ncurses

compile: make

run server: ./server

run client: telnet 127.0.0.1 7777

on client:

set name user => //n:toto

on success => //r:ok

////////////////////////////// INSTRUCTION
////////////////////////////
////////////////////////////

#define I_TURN "//i:your_turn\n"
#define I_NAME "//n:"
#define I_DISCONNECTED "//i:disconnected\n"
#define I_PING "//i:ping\n"
#define I_DISPLAY "//d"
#define I_NEW_VALUE "//nv:"
#define I_COUNT_HIT "//ci"
#define I_GIVE_UP "//g"
#define I_EXIT "//e"
#define I_COMMENT "//co:"
#define I_WINNER "//over:you_win"
#define I_LOOSER "//over:you_lose"
#define I_EQUAL "//over:eq"
#define I_NEXT_GAME "//next_game"
#define I_VERSUS "//vs:"

// exemple for set coordinate at pos x:0 & y:1 =>  //s:1,0
#define I_SET_VALUE "//s:"
// exemple for get coordinate at pos x:5 & y:2 =>  //g:2,5
#define I_GET_VALUE "//g:"



///////////////////////////// MESSAGE / RESPONSE
////////////////////////////
////////////////////////////
#define MSG_NO "//r:n\n"
#define MSG_YES "//r:y\n"
#define MSG_RESPONSE "//r:"
#define MSG_OK "//r:ok\n"
#define MSG_KO "//r:ko\n"
#define MSG_KO_CMD "//r:unkown_command\n"
#define MSG_BAD_CORD "//r:bad_coordinate\n"
#define MSG_BAD_TURN "//r:bad_turn\n"
#define MSG_BAD_SET "//r:already_set\n"

