#include <items/item.hpp>
#include <items/tree.hpp>

#include <SDL_events.h>

using namespace sdl;

Item::Item() {
}

void Item::ready() {
}

void Item::loop(double) {
}

void Item::render(double) {
}

void Item::event(const SDL_Event*) {
}

void Item::on_parent_changed(Item*) {
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

void Item::propagate_loop(double delta) {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->loop(delta);
  }
}

void Item::propagate_render(double delta) {
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->render(delta);
  }
}

Tree *Item::get_tree() const {
  return tree;
}

void Item::set_tree(Tree *new_tree) {
  Tree *old_tree = tree;
  tree = new_tree;
  if (!old_tree && tree)
    ready();
}

void Item::set_name(const std::string &new_name) {
  name = new_name;
}

std::string Item::get_name() const {
  return name;
}

void Item::add_item(Item *new_item) {
  if (new_item->get_parent() == this)
    return;

  children.insert({new_item->get_name(), new_item});
  new_item->set_parent(this);
}

std::vector<Item*> Item::get_children() const {
  std::vector<Item*> item_children;
  
  for (std::pair<std::string, Item*> iterator: children)
    item_children.push_back(iterator.second);

  return item_children;
}

void Item::set_parent(Item *new_parent) {
  parent = new_parent;
  if (!tree && parent && parent->tree)
    set_tree(parent->tree);

  parent->add_item(this);
  on_parent_changed(new_parent);
}

Item *Item::get_parent() const {
  return parent;
}

SDL_Event *Item::get_event() const {
  return tree ? tree->get_event() : nullptr;
}
