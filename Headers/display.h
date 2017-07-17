#ifndef DISPLAY_H
#define DISPLAY_H


#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct box_morpion {
  int is_a_circle;
  int is_a_cross;
  WINDOW* win;
}t_box;

typedef struct box_wrapper {
  struct box_morpion **boxes;
}t_wrap;

void display_message_at_center(const char* str, int error);
void print_logo(void);
void print_circle_at(WINDOW* win);
void print_cross_at(WINDOW* win);
void print_map(t_wrap* map, int cursor);
void init_box(t_wrap * map);
t_wrap* create_map();

#define LOGO_1 "  __       __   ______   _______   _______   ______   ______   __    __\n"
#define LOGO_2 " /  \\     /  | /      \\ /       /\\ /       \\ /      | /      \\ /  \\  /  |\n"
#define LOGO_3 " $$  \\   /$$ |/$$$$$$  |$$$$$$$  |$$$$$$$  |$$$$$$/ /$$$$$$  |$$  \\ $$ |\n"
#define LOGO_4 " $$$  \\ /$$$ |$$ |  $$ |$$ |__$$ |$$ |__$$ |  $$ |  $$ |  $$ |$$$  \\$$ |\n"
#define LOGO_5 " $$$$  /$$$$ |$$ |  $$ |$$    $$< $$    $$/   $$ |  $$ |  $$ |$$$$  $$ |\n"
#define LOGO_6 " $$ $$ $$/$$ |$$ |  $$ |$$$$$$$  |$$$$$$$/    $$ |  $$ |  $$ |$$ $$ $$ |\n"
#define LOGO_7 " $$ |$$$/ $$ |$$ \\__$$ |$$ |  $$ |$$ |       _$$ |_ $$ \\__$$ |$$ |$$$$ |\n"
#define LOGO_8 " $$ | $/  $$ |$$    $$/ $$ |  $$ |$$ |      / $$   |$$    $$/ $$ | $$$ |\n"
#define LOGO_9 " $$/      $$/  $$$$$$/  $$/   $$/ $$/       $$$$$$/  $$$$$$/  $$/   $$/\n"

#define ASK_USERNAME "Enter your name\n"
#define CONNECTION_TO_SERVER "connection au server"
#define ERR_CONNECTION_FAIL "Connection Fail Press any key to quit"


#define SIZE_X_BOX 30
#define SIZE_Y_BOX 10
         
#define TYPE_O_1 "  #######  "
#define TYPE_O_2 "  #     #  "
#define TYPE_O_3 "  #     #  "
#define TYPE_O_4 "  #     #  "
#define TYPE_O_5 "  #     #  "
#define TYPE_O_6 "  #     #  "
#define TYPE_O_7 "  #######  "

                                    
#define TYPE_X_1 "  #     #  "
#define TYPE_X_2 "   #   #   "
#define TYPE_X_3 "    # #    "
#define TYPE_X_4 "     #     "
#define TYPE_X_5 "    # #    "
#define TYPE_X_6 "   #   #   "
#define TYPE_X_7 "  #     #  "

                

#endif
