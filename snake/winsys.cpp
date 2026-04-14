#include "cpoint.h"
#include "screen.h"
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <list>
#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

class CView {
protected:
  CRect geom;

public:
  CView(CRect g) : geom(g) {};
  virtual void paint() = 0;
  virtual bool handleEvent(int key) = 0;
  virtual void move(const CPoint &delta) { geom.topleft += delta; };
  virtual ~CView() {};
};

class CWindow : public CView {
protected:
  char c;

public:
  CWindow(CRect r, char _c = '*') : CView(r), c(_c) {};
  void paint() {
    for (int i = geom.topleft.y; i < geom.topleft.y + geom.size.y; i++) {
      gotoyx(i, geom.topleft.x);
      for (int j = 0; j < geom.size.x; j++)
        printw("%c", c);
    };
  };
  bool handleEvent(int key) {
    switch (key) {
    case KEY_UP:
      move(CPoint(0, -1));
      return true;
    case KEY_DOWN:
      move(CPoint(0, 1));
      return true;
    case KEY_RIGHT:
      move(CPoint(1, 0));
      return true;
    case KEY_LEFT:
      move(CPoint(-1, 0));
      return true;
    };
    return false;
  };
};

class CFramedWindow : public CWindow {
public:
  CFramedWindow(CRect r, char _c = '\'') : CWindow(r, _c) {};
  void paint() {
    for (int i = geom.topleft.y; i < geom.topleft.y + geom.size.y; i++) {
      gotoyx(i, geom.topleft.x);
      if ((i == geom.topleft.y) || (i == geom.topleft.y + geom.size.y - 1)) {
        printw("+");
        for (int j = 1; j < geom.size.x - 1; j++)
          printw("-");
        printw("+");
      } else {
        printw("|");
        for (int j = 1; j < geom.size.x - 1; j++)
          printw("%c", c);
        printw("|");
      }
    }
  };
};

class CInputLine : public CFramedWindow {
  string text;

public:
  CInputLine(CRect r, char _c = ',') : CFramedWindow(r, _c) {};
  void paint() {
    CFramedWindow::paint();
    gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);

    for (unsigned j = 1, i = 0;
         (j + 1 < (unsigned)geom.size.x) && (i < text.length()); j++, i++)
      printw("%c", text[i]);
  };
  bool handleEvent(int c) {
    if (CFramedWindow::handleEvent(c))
      return true;
    if ((c == KEY_DC) || (c == KEY_BACKSPACE)) {
      if (text.length() > 0) {
        text.erase(text.length() - 1);
        return true;
      };
    }
    if ((c > 255) || (c < 0))
      return false;
    if (!isalnum(c) && (c != ' '))
      return false;
    text.push_back(c);
    return true;
  }
};
enum Side {
  FORW = 1,
  BACK = 2,
  RIGHT = 3,
  LEFT = 4,
};
class Snake : public CFramedWindow {
private:
  char head_sym, body_sym, app_sym;
  enum Side s;
  vector<CPoint> snake;
  CPoint apple;
  unsigned int lvl_counter;
  bool game_over;
  bool show_help;
  bool game_paused;
  unsigned int tick;
  unsigned int ticks_to_move;
  CRect game_window;
  CPoint lvl_window;
  void generate_apple() {
    while (true) {
      bool is_uniq = true;
      apple.x = rand() % (game_window.size.x - 2) + game_window.topleft.x + 1;
      apple.y = rand() % (game_window.size.y - 2) + game_window.topleft.y + 1;

      for (long unsigned int i = 0; i < snake.size(); i++) {
        if (snake[i] == apple)
          is_uniq = false;
      }
      if (is_uniq)
        break;
    }
  }
  void draw_help() {
    gotoyx(geom.topleft.y + 3, geom.topleft.x + 2);
    printw("h - toggle help information");
    gotoyx(geom.topleft.y + 4, geom.topleft.x + 2);
    printw("p - toggle pause/play mode");
    gotoyx(geom.topleft.y + 5, geom.topleft.x + 2);
    printw("r - toggle restart game");
    gotoyx(geom.topleft.y + 6, geom.topleft.x + 2);
    printw("arrows - move snake(in play mode) or");
    gotoyx(geom.topleft.y + 7, geom.topleft.x + 2);
    printw("move window (in pause mode)");
  }
  void draw_snake() {
    for (long unsigned int i = 0; i < snake.size(); i++) {
      gotoyx(snake[i].y, snake[i].x);
      if (!i)
        printw("%c", head_sym);
      else
        printw("%c", body_sym);
    }
  }
  void change_coordintaes(CPoint &ch) {
    switch (s) {
    case FORW: {
      ch.y--;
      break;
    }
    case BACK: {
      ch.y++;
      break;
    }
    case LEFT: {
      ch.x--;
      break;
    }
    default: {
      ch.x++;
      break;
    }
    }
  }
  void teleportation(CPoint &ch) {
    if (ch.x == game_window.topleft.x) {
      ch.x = game_window.topleft.x + game_window.size.x - 2;
    } else if (ch.x == game_window.topleft.x + game_window.size.x - 1) {
      ch.x = game_window.topleft.x + 1;
    }

    if (ch.y == game_window.topleft.y) {
      ch.y = game_window.topleft.y + game_window.size.y - 2;
    } else if (ch.y == game_window.topleft.y + game_window.size.y - 1) {
      ch.y = game_window.topleft.y + 1;
    }
  }
  void eat_apple() {
    snake.push_back(snake[snake.size() - 1]);
    lvl_counter++;
    speed -= INCREASE_VALUE;
    if (speed < MINIMUM_SPEED)
      speed = MINIMUM_SPEED;
    generate_apple();
  }
  void restart() {
    tick = 0;
    speed = START_SPEED;
    ticks_to_move = speed;
    show_help = true;
    game_paused = true;
    game_over = false;
    lvl_window = geom.topleft;
    game_window = geom;
    game_window.topleft.y += 1;
    snake.clear();
    int offset = 1;
    for (int i = offset + 2; i > 0; i--) {
      snake.push_back(
          CPoint(game_window.topleft.x + i, game_window.topleft.y + 1));
    }
    generate_apple();
    lvl_counter = 1;
    game_over = false;
    s = RIGHT;
  }
  bool decide_movement(int c) {
    switch (c) {
    case KEY_UP:
      if (!game_paused && s != FORW && s != BACK)
        s = FORW;
      else if (game_paused) {
        move(CPoint(0, -1));
        return true;
      }
      break;
    case KEY_DOWN:
      if (!game_paused && s != BACK && s != FORW)
        s = BACK;
      else if (game_paused) {
        move(CPoint(0, 1));
        return true;
      }
      break;
    case KEY_RIGHT:
      if (!game_paused && s != RIGHT && s != LEFT)
        s = RIGHT;
      else if (game_paused) {
        move(CPoint(1, 0));
        return true;
      }
      break;
    case KEY_LEFT:
      if (!game_paused && s != RIGHT && s != LEFT)
        s = LEFT;
      else if (game_paused) {
        move(CPoint(-1, 0));
        return true;
      }
      break;
    };
    return false;
  }

public:
  Snake(CRect r, char _c = ' ', char hs = '*', char bs = '+', int offset = 1,
        char as = 'O')
      : CFramedWindow(r, _c), head_sym(hs), body_sym(bs), app_sym(as),
        s(RIGHT) {
    tick = 0;
    speed = START_SPEED;
    ticks_to_move = speed;
    show_help = true;
    game_paused = true;
    lvl_window = r.topleft;
    game_window = r;
    game_window.topleft.y += 1;
    if (offset + 2 > game_window.size.x)
      offset = 1;
    for (int i = offset + 2; i > 0; i--) {
      snake.push_back(
          CPoint(game_window.topleft.x + i, game_window.topleft.y + 1));
    }
    generate_apple();
    lvl_counter = 1;
    game_over = false;
  }
  void paint() {
    geom = game_window;
    CFramedWindow::paint();
    gotoyx(apple.y, apple.x);
    printw("%c", app_sym);
    draw_snake();
    if (show_help == true) {
      draw_help();
    }
    if (game_over) {
      gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
      printw("GAME OVER, result: %lu", snake.size());
    } else {
      gotoyx(lvl_window.y, lvl_window.x);
      printw("|LEVEL: %d|", lvl_counter);
    }
    geom.topleft = lvl_window;
  }

  void move(const CPoint &delta) {
    lvl_window += delta;
    game_window.topleft += delta;
    geom.topleft = lvl_window;
    game_window.size = geom.size;
    for (long unsigned int i = 0; i < snake.size(); i++)
      snake[i] += delta;
    apple += delta;
  };
  void moveSnake() {
    CPoint cur = snake[0];
    for (long unsigned int i = 0; i < snake.size(); i++) {
      if (!i) {
        CPoint checker = snake[i];
        change_coordintaes(checker);
        teleportation(checker);
        for (long unsigned int j = 0; j < snake.size(); j++) {
          if (snake[j] == checker) {
            game_over = true;
            game_paused = true;
            return;
          }
        }

        snake[i] = checker;
        if (snake[i] == apple) {
          eat_apple();
        }
        continue;
      }
      CPoint temp = snake[i];
      snake[i] = cur;
      cur = temp;
    }
  }
  bool handleEvent(int c) {
    if (game_paused == false)
      tick++;
    if ((c == 'r') || (c == 'R')) {

      restart();
      return true;
    }
    if ((c == 'p') || (c == 'P')) {
      if (game_paused == true) {
        show_help = false;
        game_paused = false;
      } else {
        game_paused = true;
      }
    }
    if (((c == 'h') || (c == 'H')) && game_over == false) {
      game_paused == false ? game_paused = true : game_paused;
      show_help == true ? show_help = false : show_help = true;
      return true;
    }
    if (decide_movement(c))
      return true;
    if (c == -1 && !game_over && !game_paused) {
      if (tick >= ticks_to_move) {
        ticks_to_move = tick + speed;

        moveSnake();
        return true;
      }
    }
    return false;
  }
};
class CGroup : public CView {
  list<CView *> children;

public:
  CGroup(CRect g) : CView(g) {};
  void paint() {
    for (CView *i : children)
      i->paint();
  };
  bool handleEvent(int key) {
    if (!children.empty() && children.back()->handleEvent(key))
      return true;
    if (key == '\t') {
      if (!children.empty()) {
        children.push_front(children.back());
        children.pop_back();
      };
      return true;
    }
    return false;
  };
  void insert(CView *v) { children.push_back(v); };
  ~CGroup() {
    for (CView *i : children)
      delete i;
  };
};

class CDesktop : public CGroup {
public:
  CDesktop() : CGroup(CRect()) {
    int y, x;
    init_screen();
    getscreensize(y, x);
    geom.size.x = x;
    geom.size.y = y;
  };
  ~CDesktop() { done_screen(); };

  void paint() {
    for (int i = geom.topleft.y; i < geom.topleft.y + geom.size.y; i++) {
      gotoyx(i, geom.topleft.x);
      for (int j = 0; j < geom.size.x; j++)
        printw(".");
    };
    CGroup::paint();
  }

  int getEvent() { return ngetch(); };

  void run() {
    int c;
    paint();
    refresh();
    while (1) {
      c = getEvent();
      if (c == 27) // ESC key
        break;
      if (handleEvent(c)) {
        paint();
        refresh();
      };
    };
  };
};

int main() {
  CDesktop d;
  d.insert(new CInputLine(CRect(CPoint(5, 7), CPoint(15, 15))));
  d.insert(new CWindow(CRect(CPoint(2, 3), CPoint(20, 10)), '#'));
  d.insert(new Snake(CRect(CPoint(10, 10), CPoint(50, 30))));
  d.run();
  return 0;
}
