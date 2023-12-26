#include <items/item.hpp>
#include <items/tree.hpp>

#include <SDL_events.h>

using namespace sdl;

// There are at least ten bugs in this

Item::Item() {
}

void Item::_ready() {
}

void Item::_loop(double) {
}

void Item::_render(double) {
}

void Item::_event(const SDL_Event*) {
}

void Item::_notification(const int) {
}

void Item::free() {
  if (parent)
    parent->children.erase(name);

  tree = nullptr;
  parent = nullptr;

  for (auto iterator: children) {
    if (iterator.second == nullptr)
      continue;

    iterator.second->free();
  }

  delete this;
}

void Item::notification(const int what) {
  _notification(what);

  if (!tree)
    return;
  
  switch (what) {
    case NOTIFICATION_RENDER:
      _render(get_delta_time());
      break;
    case NOTIFICATION_LOOP:
      _loop(get_loop_delta_time());
      break;
    case NOTIFICATION_EVENT:
      _event(get_event());
      break;
    case NOTIFICATION_READY:
      _ready();
      break;
    default:
      break;
  }
}

void Item::propagate_notification(const int what) {
  notification(what);

  for (std::pair<std::string, Item*> iterator: children)
    iterator.second->propagate_notification(what);
}

Tree *Item::get_tree() const {
  return tree;
}

bool Item::is_inside_tree() const {
  return tree;
}

void Item::set_tree(Tree *new_tree) {
  Tree *old_tree = tree;
  tree = new_tree;

  if (!old_tree && tree) {
    propagate_notification(NOTIFICATION_ENTER_TREE);
    propagate_notification(NOTIFICATION_READY);
  }
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

  if (tree)
    new_item->set_tree(tree);

  new_item->notification(NOTIFICATION_PARENTED);
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

double Item::get_delta_time() const {
  return tree ? tree->get_render_delta_time() : 0.0;
}

double Item::get_loop_delta_time() const {
  return tree ? tree->get_loop_delta_time() : 0.0;
}

SDL_Event *Item::get_event() const {
  return tree ? tree->get_event() : nullptr;
}
