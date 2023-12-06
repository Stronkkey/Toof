#ifndef ITEM
#define ITEM

#include <items/tree.hpp>

namespace sdl {

class Item {

private:
  std::unordered_map<std::string, Item*> children;
  Tree *tree = nullptr;
  Item *parent = nullptr;
  std::string name;

protected:
  virtual void event(const SDL_Event*) {}
  virtual void render(double) {}
  virtual void loop() {}
  virtual void on_parent_changed(Item*) {}
  virtual void ready() {}

public:
  Item();
  virtual ~Item() {}

  void propagate_event(const SDL_Event *event);
  void propagate_render(double delta);
  void propagate_loop();
  void free();

  Tree *get_tree() const;
  void set_tree(Tree *new_tree);

  void set_name(const std::string &new_name);
  std::string get_name() const;

  void add_item(Item *new_item);
  std::vector<Item*> get_children() const;

  void set_parent(Item *new_parent);
  Item *get_parent() const;
};

}

#endif // !ITEM
