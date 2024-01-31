#include <scene/main/node.hpp>
#include <scene/main/scene_tree.hpp>

#include <SDL_events.h>

using namespace sdl;

Node::Node(): children(),
    tree(nullptr),
    parent(),
    name("Node"),
    is_ready(false),
	is_deletion_queued(false) {
}

Node::~Node() {
	notification(NOTIFICATION_PREDELETE);

	for (const auto &iterator: children)
		delete iterator.second;
}

void Node::_add_child_nocheck(Node *new_item) {
	children.insert({&new_item->name, new_item});
	new_item->parent = this;

	if (tree)
		new_item->set_tree(tree);

	new_item->notification(NOTIFICATION_PARENTED);
}

void Node::_ready() {
}

void Node::_loop(double) {
}

void Node::_physics_process(const double) {
}

void Node::_render(double) {
}

void Node::_event(const SDL_Event*) {
}

void Node::_notification(const int) {
}

void Node::queue_free() {
	if (is_deletion_queued || !tree)
		return;

	tree->queue_free(this);
	is_deletion_queued = true;
}

bool Node::is_queued_for_deletion() const {
	return is_deletion_queued;
}

void Node::notification(const int what) {
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

void Node::propagate_notification(const int what) {
	notification(what);

	for (const auto &iterator: children)
		iterator.second->propagate_notification(what);
}

SceneTree *Node::get_tree() const {
	return tree;
}

bool Node::is_inside_tree() const {
	return tree;
}

void Node::set_tree(SceneTree *new_tree) {
	SceneTree *old_tree = tree;
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

void Node::add_child(Node *child) {
	if (!child || child->parent == this)
		return;

	_add_child_nocheck(child);
}

void Node::set_name(const std::string &new_name) {
	name = new_name;
	renamed(name);
}

const std::string &Node::get_name() const {
	return name;
}

void Node::remove_child(Node* node) {
	if (!node || node->parent != this)
		return;

	node->parent = nullptr;
	node->set_tree(nullptr);
	children.erase(&node->name);
}

const Node::children_t &Node::get_children() const {
	return children;
}

Node *Node::get_parent() const {
	return parent;
}

Node *Node::get_node(std::string *name) const {
	auto iterator = children.find(name);

	return iterator == children.end() ? nullptr : iterator->second;
}

double Node::get_delta_time() const {
	return tree ? tree->get_render_delta_time() : 0.0;
}

double Node::get_loop_delta_time() const {
	return tree ? tree->get_loop_delta_time() : 0.0;
}

double Node::get_physics_delta_time() const {
	#ifdef B2_INCLUDED
	return tree ? tree->get_physics_delta_time() : 0.0;
	#else
	return 0.0;
	#endif
}

SDL_Event *Node::get_event() const {
	return tree ? tree->get_event() : nullptr;
}

void Node::remove_children() {
	for (const auto &iterator: children) {
		iterator.second->parent = nullptr;
		iterator.second->set_tree(nullptr);
	}
	children.clear();
}
