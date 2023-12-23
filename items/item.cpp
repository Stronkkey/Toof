#include <items/item.hpp>
#include <items/tree.hpp>

#include <SDL_events.h>

using namespace sdl;

// There are at least ten bugs in this

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
  tree = nullptr;
  parent = nullptr;
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->free();
  }

  delete this;
}

void Item::propagate_event(const SDL_Event *sdl_event) {
  event(sdl_event);
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->propagate_event(sdl_event);
  }
}

void Item::propagate_loop(double delta) {
  loop(delta);
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->propagate_loop(delta);
  }
}

void Item::propagate_render(double delta) {
  render(delta);
  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->propagate_render(delta);
  }
}

Tree *Item::get_tree() const {
  return tree;
}

void Item::set_tree(Tree *new_tree) {
  const Tree *old_tree = tree;
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
  if (new_item->parent == this)
    return;

  children.insert({new_item->get_name(), new_item});
  new_item->parent = this;
  new_item->on_parent_changed(this);

  if (tree)
    new_item->set_tree(tree);
}

void Item::remove_item(const std::string &item_name) {
  auto iterator = children.find(item_name);
  if (iterator != children.end()) {
    iterator->second->parent = nullptr;
    iterator->second->tree = nullptr;
    children.erase(iterator);
  }
}

std::vector<Item*> Item::get_children() const {
  std::vector<Item*> item_children;
  
  for (std::pair<std::string, Item*> iterator: children)
    item_children.push_back(iterator.second);

  return item_children;
}

Item *Item::get_parent() const {
  return parent;
}

SDL_Event *Item::get_event() const {
  return tree ? tree->get_event() : nullptr;
}
