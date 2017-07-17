#include "display.h"


t_wrap* create_map() {

  t_wrap* map;
  
  map = malloc(sizeof(t_wrap));

  if (map == NULL) {
    printf("Error malloc \n");
    return NULL;
  }

  map->boxes = malloc(9 * sizeof(t_box*));
  if (map->boxes == NULL) {
    endwin();
    printf("Error malloc \n");
    return NULL;
  }
  for (int i = 0; i < 9; i++) {
    map->boxes[i] = malloc(sizeof(t_box));
    if (map->boxes[i] == NULL){
      endwin();
      printf("Error malloc \n");
      return NULL;
    }
  }
  
  return map;
}

void init_box(t_wrap * map) {

  int margey;
  int margex;
  int sizex, sizey;
  getmaxyx(stdscr, sizey, sizex);
  margey = 10;
  margex = sizex/2 - 45;
  
  map->boxes[0]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                        margey + SIZE_Y_BOX * 0, margex + SIZE_X_BOX * 0);
  map->boxes[1]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 0, margex + SIZE_X_BOX * 1);
  map->boxes[2]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 0, margex + SIZE_X_BOX * 2);

  map->boxes[3]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 1, margex + SIZE_X_BOX * 0);
  map->boxes[4]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 1, margex + SIZE_X_BOX * 1);
  map->boxes[5]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 1, margex + SIZE_X_BOX * 2);

  map->boxes[6]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 2, margex + SIZE_X_BOX * 0);
  map->boxes[7]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 2, margex + SIZE_X_BOX * 1);
  map->boxes[8]->win = newwin(SIZE_Y_BOX, SIZE_X_BOX,
                         margey + SIZE_Y_BOX * 2, margex + SIZE_X_BOX * 2);
  
}

void print_map(t_wrap* map, int cursor) {

  for (int i = 0; i < 9; i++) {
    t_box* box = map->boxes[i];

    wclear(box->win);    
    box(box->win, 0, 0);

    if (cursor == i) {
      wbkgd(box->win, COLOR_PAIR(2));
    } else {
      wbkgd(box->win, COLOR_PAIR(1));
    }
    
    if (box->is_a_circle == 1) {
      print_circle_at(box->win);
    }
    if (box->is_a_cross == 1) {
      print_cross_at(box->win);
    }
    wrefresh(box->win);
  }

}

void display_message_at_center(const char* str, int error) {

  int row, col;

  clear();
  getmaxyx(stdscr, row, col);
  if (error == 1) {
    init_pair(1, COLOR_RED, COLOR_BLACK);
  } else {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
  }
  mvprintw(row/2, (col - strlen(str))/2, "%s", str);
  attron(COLOR_PAIR(1));
  refresh();
  sleep(1);
}

void print_circle_at(WINDOW* win) {

  mvwprintw(win, 0 + 2, 0 + 10, TYPE_O_1);
  mvwprintw(win, 1 + 2, 0 + 10, TYPE_O_2);
  mvwprintw(win, 2 + 2, 0 + 10, TYPE_O_3);
  mvwprintw(win, 3 + 2, 0 + 10, TYPE_O_4);
  mvwprintw(win, 4 + 2, 0 + 10, TYPE_O_5);
  mvwprintw(win, 5 + 2, 0 + 10, TYPE_O_6);
  mvwprintw(win, 6 + 2, 0 + 10, TYPE_O_7);
}

void print_cross_at(WINDOW* win) {
  
  mvwprintw(win, 0 + 2, 0 + 10, TYPE_X_1);
  mvwprintw(win, 1 + 2, 0 + 10, TYPE_X_2);
  mvwprintw(win, 2 + 2, 0 + 10, TYPE_X_3);
  mvwprintw(win, 3 + 2, 0 + 10, TYPE_X_4);
  mvwprintw(win, 4 + 2, 0 + 10, TYPE_X_5);
  mvwprintw(win, 5 + 2, 0 + 10, TYPE_X_6);
  mvwprintw(win, 6 + 2, 0 + 10, TYPE_X_7);
}

void print_logo() {

  int row, col;

  clear();
  curs_set(0);
  getmaxyx(stdscr, row, col);
  mvprintw(row/2 - 9, (col - strlen(LOGO_1))/2, "%s", LOGO_1);
  mvprintw(row/2 + 1 - 9, (col - strlen(LOGO_2))/2, "%s", LOGO_2);
  mvprintw(row/2 + 2 - 9, (col - strlen(LOGO_3))/2, "%s", LOGO_3);
  mvprintw(row/2 + 3 - 9, (col - strlen(LOGO_4))/2, "%s", LOGO_4);
  mvprintw(row/2 + 4 - 9, (col - strlen(LOGO_5))/2, "%s", LOGO_5);
  mvprintw(row/2 + 5 - 9, (col - strlen(LOGO_6))/2, "%s", LOGO_6);
  mvprintw(row/2 + 6 - 9, (col - strlen(LOGO_7))/2, "%s", LOGO_7);
  mvprintw(row/2 + 7 - 9, (col - strlen(LOGO_8))/2, "%s", LOGO_8);
  mvprintw(row/2 + 8 - 9, (col - strlen(LOGO_9))/2, "%s", LOGO_9);
  refresh();
  sleep(2);
}

