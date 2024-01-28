#include <items/item.hpp>
#include <items/tree.hpp>

#include <SDL_events.h>

using namespace sdl;

// There are at least ten bugs in this

Item::Item(): children(),
    tree(nullptr),
    parent(),
    name("Item"),
    is_ready(false),
	is_deletion_queued(false) {
}

Item::~Item() {
	notification(NOTIFICATION_PREDELETE);

	for (Item *child: children)
		delete child;
}

void Item::_ready() {
}

void Item::_loop(double) {
}

void Item::_physics_process(const double) {
}

void Item::_render(double) {
}

void Item::_event(const SDL_Event*) {
}

void Item::_notification(const int) {
}

void Item::queue_free() {
	if (is_deletion_queued || !tree)
		return;

	tree->queue_free(this);
	is_deletion_queued = true;
}

bool Item::is_queued_for_deletion() const {
	return is_deletion_queued;
}

void Item::notification(const int what) {
	_notification(what);
	if (what == NOTIFICATION_EXIT_TREE)
		tree_exiting();
	
	if (!tree)
		return;

	switch (what) {
		case NOTIFICATION_PHYSICS_PROCESS:
			_physics_process(get_physics_delta_time());
			break;
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
			ready();
			break;
		case NOTIFICATION_ENTER_TREE:
			tree_entering();
			break;
		default:
			break;
	}
}

void Item::propagate_notification(const int what) {
	notification(what);

	for (Item *child: children)
		child->propagate_notification(what);
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

		if (!is_ready) {
			notification(NOTIFICATION_READY);
			is_ready = true;
		}

	} else if (old_tree && !tree)
		propagate_notification(NOTIFICATION_EXIT_TREE);
}

void Item::set_name(const std::string &new_name) {
	name = new_name;
	renamed(name);
}

const std::string &Item::get_name() const {
	return name;
}

void Item::add_item(Item *new_item) {
	if (new_item->parent == this)
		return;

	children.insert(new_item);
	new_item->parent = this;

	if (tree)
		new_item->set_tree(tree);

	new_item->notification(NOTIFICATION_PARENTED);
}

void Item::remove_item(Item* item) {
	if (!item || item->parent != this)
		return;

	item->parent = nullptr;
	item->set_tree(nullptr);
	children.erase(item);
}

const Item::children_t &Item::get_children() const {
	return children;
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

double Item::get_physics_delta_time() const {
	#ifdef B2_INCLUDED
	return tree ? tree->get_physics_delta_time() : 0.0;
	#else
	return 0.0;
	#endif
}

SDL_Event *Item::get_event() const {
	return tree ? tree->get_event() : nullptr;
}

void Item::remove_children() {
	for (Item *child: children) {
		child->parent = nullptr;
		child->set_tree(nullptr);
	}
	children.clear();
}
