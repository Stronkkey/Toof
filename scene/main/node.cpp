#include <scene/main/node.hpp>
#include <scene/main/scene_tree.hpp>
#include <input/input.hpp>

#include <SDL_events.h>

using namespace sdl;

Node::Node(): children(),
    tree(nullptr),
    parent(nullptr),
    name("Node"),
    is_ready(false),
	is_deletion_queued(false) {
}

Node::~Node() {
	notification(NOTIFICATION_PREDELETE);

	if (parent)
		parent->remove_child(this);

	remove_children();
}

void Node::_reset_tree() {
	if (tree)
		propagate_notification(NOTIFICATION_EXIT_TREE);

	tree = nullptr;
}

void Node::_reset_parent(const bool erase_as_child) {
	if (parent && erase_as_child)
		parent->children.erase(this);

	parent = nullptr;
	notification(NOTIFICATION_PARENTED);
}

void Node::_add_child_nocheck(Node *new_child) {
	children.insert(new_child);
	new_child->parent = this;

	if (tree)
		new_child->set_tree(tree);

	new_child->notification(NOTIFICATION_PARENTED);
}

void Node::_ready() {
}

void Node::_process(double) {
}

void Node::_physics_process(const double) {
}

void Node::_render(double) {
}

void Node::_event(const std::shared_ptr<InputEvent>&) {
}

void Node::_notification(const int) {
}

void Node::queue_free() {
	if (is_deletion_queued || !tree)
		return;

	tree->queue_free(this);
	is_deletion_queued = true;
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
		case NOTIFICATION_PROCESS:
			_process(get_process_delta_time());
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

	for (Node *child: children)
		child->propagate_notification(what);
}

const std::unique_ptr<Input> &Node::get_input() const {
	if (tree)
		return tree->get_input();

	const std::unique_ptr<Input> _i;
	const std::unique_ptr<Input> *i = &_i;
	return *i;
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

void Node::set_name(const String &new_name) {
	name = new_name;
	renamed(name);
}

void Node::remove_child(Node* node) {
	if (node->parent != this)
		return;

	node->_reset_parent();
	node->_reset_tree();
}

double Node::get_delta_time() const {
	return tree ? tree->get_render_delta_time() : 0.0;
}

double Node::get_process_delta_time() const {
	return tree ? tree->get_process_delta_time() : 0.0;
}

double Node::get_physics_delta_time() const {
	#ifdef B2_INCLUDED
	return tree ? tree->get_physics_delta_time() : 0.0;
	#else
	return 0.0;
	#endif
}

const std::unique_ptr<SDL_Event> &Node::get_event() const {
	if (tree)
		return tree->get_event();

	const std::unique_ptr<SDL_Event> _i, *i = &_i;
	return *(i);
}

void Node::propagate_input_event(const std::shared_ptr<InputEvent> &input_event) {
	notification(NOTIFICATION_EVENT);
	_event(input_event);

	for (Node *node: children)
		node->propagate_input_event(input_event);
}

void Node::remove_children() {
	for (Node *node: children) {
		node->_reset_parent(false);
		node->_reset_tree();
	}
	children.clear();
}
