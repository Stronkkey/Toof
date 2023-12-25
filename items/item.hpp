#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include <SDL_events.h>

namespace sdl {

class Tree;

class Item {

public:
  enum ProcessMode {
    PROCESS_MODE_INHERIT,
    PROCESS_MODE_PAUSABLE,
    PROCESS_MODE_WHEN_PAUSED,
    PROCESS_MODE_ALWAYS,
    PROCESS_MODE_DISABLED
  };

  enum {
    NOTIFICATION_READY = 1000,
    NOTIFICATION_EVENT,
    NOTIFICATION_RENDER,
    NOTIFICATION_LOOP,
    NOTIFICATION_ENTER_TREE,
    NOTIFICATION_EXIT_TREE,
    NOTIFICATION_PAUSED,
    NOTIFICATION_UNPAUSED,
    NOTIFICATION_UNPARENTED,
    NOTIFICATION_PARENTED,
    NOTIFICATION_DISABLED,
    NOTIFICATION_ENABLED,
    NOTIFICATION_CLOSE_REQUEST,
    NOTIFICATION_PREDELETE
  };

private:
  std::unordered_map<std::string, Item*> children;
  Tree *tree = nullptr;
  Item *parent = nullptr;
  std::string name;

protected:
  virtual void _notification(const int what);
  virtual void _event(const SDL_Event *event);
  virtual void _render(double delta);
  virtual void _loop(double delta);
  virtual void _ready();

public:
  Item();
  virtual ~Item() {}

  SDL_Event *get_event() const;
  double get_delta_time() const;
  double get_loop_delta_time() const;

  void notification(const int what);
  void propagate_notification(const int what);
  void free();

  Tree *get_tree() const;
  void set_tree(Tree *new_tree);

  void set_name(const std::string &new_name);
  std::string get_name() const;

  void add_item(Item *new_item);
  void remove_item(const std::string &item_name);
  std::vector<Item*> get_children() const;

  Item *get_parent() const;
};

}
