
#include "node_tree.h"

#include "node.h"

Node *NodeTree::get_root() {
	return _root_node;
}

void NodeTree::set_root(Node *root) {
	if (_root_node) {
		_root_node->set_tree(nullptr);
	}

	_root_node = root;

	if (_root_node) {
		_root_node->set_tree(this);
	}
}

void NodeTree::update() {
	if (!_root_node) {
		return;
	}

	_root_node->notification(Node::NOTIFICATION_UPDATE);

	if (_write_lock_requested) {
		_rw_lock.write_lock();
		_root_node->notification(Node::NOTIFICATION_TREE_WRITE_LOCKED);
		_rw_lock.write_unlock();

		_write_lock_requested = false;
	}
}

void NodeTree::_send_update() {
	if (_root_node) {
		_root_node->notification(Node::NOTIFICATION_UPDATE);
	}
}

float NodeTree::get_update_delta_time() {
	return 0;
}

NodeTree::NodeTree() :
		Object() {

	_root_node = nullptr;
	_update_interval = 0;
}

NodeTree::~NodeTree() {
	if (_root_node) {
		delete _root_node;
		_root_node = nullptr;
	}
}