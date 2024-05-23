/** @file node.hpp
    @brief Definition of the Node class. */
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
#pragma once

#include <core/string/string_def.hpp>
#include <core/memory/signal.hpp>

#include <memory>
#include <unordered_set>

#include <SDL_events.h>

namespace Toof {

class SceneTree;
class InputEvent;
class Input;

/**
* @brief Base class for all scene objects.
* @see The documentation for Godot Nodes https://docs.godotengine.org/en/stable/classes/class_node.html. Most properties are reflected in Toof as well.
*/

class Node {

using children_t = std::unordered_set<Node*>;

public:
	enum ProcessMode {
		/**
		* @brief Inherits the process mode from the nodes parent.
		*/
		PROCESS_MODE_INHERIT,

		/**
		* @brief Stops processing when the tree is paused (process when unpaused).
		*/
		PROCESS_MODE_PAUSABLE,

		/**
		* @brief Only process when the tree is paused (don't process when unpaused).
		*/
		PROCESS_MODE_WHEN_PAUSED,

		/**
		* @brief Always process regardless of if the tree is paused or not.
		*/
		PROCESS_MODE_ALWAYS,

		/**
		* @brief Don't process regardless when the tree is paused or not.
		*/
		PROCESS_MODE_DISABLED
	};

	enum {
		/**
		* @brief Notification received when the node is ready. @see @b _ready.
		*/
		NOTIFICATION_READY = 1000,

		/**
		* @brief Notification received when an event has been process. @see @b _event.
		*/
		NOTIFICATION_EVENT,

		/**
		* @brief Notification received each render step. @see @b _render.
		*/
		NOTIFICATION_RENDER,

		/**
		* @brief Notification received each process step. @see @b _process.
		*/
		NOTIFICATION_PROCESS,

		/**
		* @brief Notification received each physics step. @see @b _physics_process.
		*/
		NOTIFICATION_PHYSICS_PROCESS,

		/**
		* @brief Notification received when the node enters the tree
		*/
		NOTIFICATION_ENTER_TREE,

		/**
		* @brief Notification received when the node is removed from the tree.
		*/
		NOTIFICATION_EXIT_TREE,

		/**
		* @brief Notification received when the processing of this node has been paused.
		*/
		NOTIFICATION_PAUSED,

		/**
		* @brief Notification received when the processing of this node has been unpaused.
		*/
		NOTIFICATION_UNPAUSED,

		/**
		* @brief Notification received when the parent is set. @note This notification is received even if the parent is @b nullptr.
		*/
		NOTIFICATION_PARENTED,

		/**
		* @brief Notification received when the node is disabled. @see @b PROCESS_MODE_DISABLED.
		*/
		NOTIFICATION_DISABLED,

		/**
		* @brief Notification received when the node is enabled after being disabled. @see @b PROCESS_MODE_DISABLED.
		*/
		NOTIFICATION_ENABLED,

		/**
		* @brief Notification received when the window is about to be closed.
		*/
		NOTIFICATION_CLOSE_REQUEST,

		/**
		* @brief Notification received before the Node is deleted with free.
		*/
		NOTIFICATION_PREDELETE,

		/**
		* @brief Notification received from the SceneTree's crash handler when the program is about to crash. Implemented on desktop platforms.
		*/
		NOTIFICATION_CRASH,
	};

private:
	children_t children;
	SceneTree *tree;
	Node *parent;
	String name;
	bool is_ready, is_deletion_queued;

	void _reset_tree();
	void _reset_parent(const bool erase_as_child = true);
	void _add_child_nocheck(Node *node);
	void _set_tree(SceneTree *tree);
	void _set_tree_recursive(SceneTree *tree);

protected:
	/**
	* @brief Called when the node receives a notification by the @b notification function.
	* @param what The notification. Can be compared to any integer constant.
	*/
	virtual void _notification(const int what);

	/**
	* @brief Called each time an "event" happens.
	* @details This can be keyboard input, mouse movement, window size changing, etc.
	* Events are instantly processed from when they happen.
	*/
	virtual void _event(const std::shared_ptr<InputEvent> &event);

	/**
	* @brief Called in the render step of the tree.
	* @details This usually happens every 1/60th of a second, but can take longer if the system cannot catch up.
	* @param delta The time from between the previous frame and the current frame. This value is very close to 0 on the first frame.
	*/
	virtual void _render(double delta);

	/**
	* @brief Called in the process step of the tree.
	* @details This usually happens every 1/60th of a second, but can take longer if the system cannot catch up.
	* @param delta The time from between the previous frame and the current frame. This value is very close to 0 on the first frame.
	*/
	virtual void _process(double delta);

	/**
	* @brief Called in each physics step of the tree.
	* @details This usually happens every 1/60th of a second, but can take longer if the system cannot catch up.
	* @param delta The time from between the previous frame and the current frame. This value is very close to 0 on the first frame.
	* @note This method is only called if physics are enabled.
	*/
	virtual void _physics_process(const double delta);

	/**
	* @brief Called when the node is "ready".
	* @details A node is "ready" when the set_tree has been called with a valid SceneTree.
	* This only gets called once and not on any subsequent set_tree.
	*/
	virtual void _ready();

public:
	Node();

	/**
	* @brief Removes this node as a child from the parent.
	*/
	virtual ~Node();

	/**
	* @brief Emitted when the node is ready. Called after @b _ready callback and follows the same rules.
	*/
	Signal<> ready;

	/**
	* @brief Emitted when the node is renamed.
	*/
	Signal<const String&> renamed;

	/**
	* @brief Emitted when the node enters the tree.
	* @details This signal is emitted before the related @b NOTIFICATION_ENTER_TREE notification.
	*/
	Signal<> tree_entering;

	/**
	* @brief Emitted when the node is still active but about to exit the tree.
	* @details This signal is emitted before the related @b NOTIFICATION_EXIT_TREE notification
	*/
	Signal<> tree_exiting;

	/**
	* @brief Returns the SDL_Event structure from the tree.
	* @note The return value is undefined if the node is not inside the SceneTree.
	*/
	const std::unique_ptr<SDL_Event> &get_event() const;

	/**
	* @brief Propagates the InputEvent to all descendants.
	*/
	void propagate_input_event(const std::shared_ptr<InputEvent> &input_event);

	/**
	* @brief Returns the time between the previous render step and the current render step.
	* @details This value is very close to 0 on the first frame.
	*/
	double get_delta_time() const;

	/**
	* @brief Returns the time between the previous process step and the current proccess step.
	* @details This value is very close to 0 on the first frame.
	*/
	double get_process_delta_time() const;

	/**
	* @brief Returns the time between the previous physics step and the current physics step.
	* @details This value is very close to 0 on the first frame.
	* @note Always returns 0 if physics are not enabled.
	*/
	double get_physics_delta_time() const;

	/**
	* @brief Sends the given notification to the node, calling @b _notification with @b what as well.
	*/
	void notification(const int what);

	/**
	* @brief Calls notification with @b what to itself and all descendants.
	*/
	void propagate_notification(const int what);

	/**
	* @brief Queues a node for deletion at the end of the current frame.
	* @details The deletion is equivalent to: @code delete note @endcode
	* It is safe to call queue_free multiple times per frame on a node, and to free a node that is currently queued for deletion.
	* Use @b is_queued_for_deletion to check whether an node will be deleted at the end of the frame.
	* The node will only be freed after all other deferred calls are finished.
	* @note The behavior is undefined the Node is not allocated with @b new.
	*/
	void queue_free();

	/**
	* @brief Returns @b true if the node is queued for deletion.
	* @see @b queue_free.
	*/
	constexpr bool is_queued_for_deletion() const {
		return is_deletion_queued;
	}

	/**
	* @brief Returns the SceneTree this node belongs to, or @b nullptr if the SceneTree hasn't been set.
	*/
	constexpr SceneTree *get_tree() const {
		return tree;
	}

	/**
	* @brief Returns the Input from the tree.
	* @note The return value is undefined if the Node is not inside the SceneTree.
	*/
	const std::unique_ptr<Input> &get_input() const;

	/**
	* @brief Sets the SceneTree for this Node.
	* @details The Node will also receive the @b NOTIFICATION_ENTERED_TREE and @b NOTIFICATION_READY (with the rules of <b>ready</b>) notifications.
	*/
	void set_tree(SceneTree *new_tree);

	/**
	* @brief Returns @b true if the node is inside the SceneTree.
	*/
	bool is_inside_tree() const;

	/**
	* @brief Sets the name of the Node.
	*/
	void set_name(const String &new_name);

	/**
	* @brief Returns the name of the Node.
	*/
	constexpr const String &get_name() const {
		return name;
	}

	/**
	* @brief Adds a child @b node.
	* @details This methods overwrites the parent of the new child node.
	*/
	void add_child(Node *child);

	/**
	* @brief Removes the Node @b child from this Node.
	* @details If the @b child Node is inside the SceneTree, then the SceneTree of the @b child Node will be set to @b nullptr.
	* Does nothing if the parent of the @b child Node is not this Node.
	*/
	void remove_child(Node *child);

	/**
	* @brief Returns an implementation defined container of all children.
	*/
	constexpr const children_t &get_children() const {
		return children;
	}

	/**
	* @brief Returns the parent of this Node.
	*/
	constexpr Node *get_parent() const {
		return parent;
	}

	/**
	* @brief Removes all children from this Node.
	*/
	void remove_children();
};

}
