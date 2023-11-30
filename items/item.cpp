#include "item.hpp"
#include "../tree.hpp"

using namespace sdl;

Item::Item() {
}

void Item::free() {
  for (Item *item: children) {
    if (item == nullptr)
      continue;

    item->free();
  }

  delete this;
}

void Item::propagate_event(const SDL_Event *event) {
  for (Item *item: children) {
    if (item == nullptr)
      continue;

    item->event(event);
  }
}

void Item::propagate_loop() {
  for (Item *item: children) {
    if (item == nullptr)
      continue;

    item->loop();
  }
}

void Item::propagate_render() {
  for (Item *item: children) {
    if (item == nullptr)
      continue;

    item->render();
  }
}

Tree *Item::get_tree() const {
  return tree;
}

void Item::set_tree(Tree *new_tree) {
  tree = new_tree;
  if (tree)
    on_added_to_tree();
}

void Item::set_name(const std::string &new_name) {
  name = new_name;
}

std::string Item::get_name() const {
  return name;
}

void Item::add_item(Item *new_item) {
  std::string item_name = new_item->get_name();
  for (Item *child: children)
    if (child->get_name() == item_name)
      return;

  children.push_back(new_item);
}

std::vector<Item*> Item::get_children() const {
  return children;
}

void Item::set_parent(Item *new_parent) {
  parent = new_parent;
  on_parent_changed(new_parent);
}

Item *Item::get_parent() const {
  return parent;
}
