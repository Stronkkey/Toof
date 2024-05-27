/*  This file is part of the Toof Engine. */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <scene/main/node.hpp>
#include <scene/main/scene_tree.hpp>
#include <input/input.hpp>

#include <SDL_events.h>

using namespace Toof;

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

void Node::_set_tree(SceneTree *tree) {
	SceneTree *old_tree = this->tree;
	this->tree = tree;

	if (!old_tree && tree) {
		notification(NOTIFICATION_ENTER_TREE);

		if (!is_ready) {
			notification(NOTIFICATION_READY);
			is_ready = true;
		}
	} else if (old_tree && !tree)
		notification(NOTIFICATION_EXIT_TREE);
}

void Node::_set_tree_recursive(SceneTree *tree) {
	_set_tree(tree);

	for (Node *child: children)
		child->_set_tree_recursive(tree);
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
	_set_tree_recursive(new_tree);
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
	return tree ? tree->get_render_loop().get_delta_time() : 0.0;
}

double Node::get_process_delta_time() const {
	return tree ? tree->get_process_loop().get_delta_time() : 0.0;
}

double Node::get_physics_delta_time() const {
	#ifdef TOOF_PHYSICS_ENABLED
	return tree ? tree->get_physics_loop().get_delta_time() : 0.0;
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
