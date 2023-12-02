#include <iostream>
#include <items/item.hpp>

using namespace sdl;

Item::Item() {
}

void Item::free() {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->free();
  }

  delete this;
}

void Item::propagate_event(const SDL_Event *event) {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->event(event);
  }
}

void Item::propagate_loop() {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->loop();
  }
}

void Item::propagate_render() {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->render();
  }
}

Tree *Item::get_tree() const {
  return tree;
}

void Item::set_tree(Tree *new_tree) {
  tree = new_tree;
  if (tree)
    ready();
}

void Item::set_name(const std::string &new_name) {
  name = new_name;
}

std::string Item::get_name() const {
  return name;
}

void Item::add_item(Item *new_item) {
  if (!new_item || new_item->get_parent() == this)
    return;

  children.insert({new_item->get_name(), new_item});
  new_item->set_parent(this);

  if (new_item->get_tree() == nullptr && get_tree() != nullptr)
    new_item->set_tree(get_tree());
}

std::vector<Item*> Item::get_children() const {
  std::vector<Item*> item_children;
  
  for (std::pair<std::string, Item*> iterator: children)
    item_children.push_back(iterator.second);

  return item_children;
}

void Item::set_parent(Item *new_parent) {
  parent = new_parent;
  if (get_tree() == nullptr && parent && parent->get_tree())
    set_tree(parent->get_tree());

  parent->add_item(this);
  on_parent_changed(new_parent);
}

Item *Item::get_parent() const {
  return parent;
}
