
#include "node.h"

#include "node_tree.h"

bool Node::is_in_tree() const {
	return _in_tree;
}

Node *Node::get_parent() {
	return _parent;
}
void Node::set_parent(Node *parent) {
	if (_parent == parent) {
		return;
	}

	if (_parent) {
		notification(NOTIFICATION_UNPARENTED);
	}

	_parent = parent;

	if (_parent) {
		notification(NOTIFICATION_PARENTED);
	}
}

int Node::get_child_count() {
	return _children.size();
}
Node *Node::get_child(int index) {
	return _children[index];
}
void Node::add_child(Node *child) {
	ERR_FAIL_COND(!child);
	ERR_FAIL_COND(child->get_parent());

	_children.push_back(child);
	child->set_parent(this);

	if (_in_tree) {
		child->set_tree(_tree);
		child->notification(NOTIFICATION_EXIT_TREE);
	}

	notification(NOTIFICATION_CHILD_ADDED);
}
void Node::remove_child_index(int index) {
	Node *c = _children[index];

	_children.remove_keep_order(index);
	c->set_parent(nullptr);

	notification(NOTIFICATION_CHILD_REMOVED);
}
void Node::remove_child(Node *child) {
	ERR_FAIL_COND(!child);

	for (int i = 0; i < _children.size(); ++i) {
		Node *c = _children[i];

		if (c == child) {
			_children.remove_keep_order(i);
			child->set_parent(nullptr);
			notification(NOTIFICATION_CHILD_REMOVED);
			return;
		}
	}
}

NodeTree *Node::get_tree() {
	return _tree;
}

void Node::set_tree(NodeTree *tree) {
	if (_tree) {
		_in_tree = false;
		_notification(NOTIFICATION_EXIT_TREE);
	}

	_tree = tree;

	if (_tree) {
		_in_tree = true;
	}

	for (int i = 0; i < _children.size(); ++i) {
		_children[i]->set_tree(tree);
	}

	if (_tree) {
		_notification(NOTIFICATION_ENTER_TREE);
	}

}

void Node::notification(const int what) {
	_notification(what);

	for (int i = 0; i < _children.size(); ++i) {
		_children[i]->notification(what);
	}
}
void Node::_notification(const int what) {
}

Node::Node() :
		Object() {

	_in_tree = false;
	_parent = nullptr;
	_tree = nullptr;
}

Node::~Node() {
	for (int i = 0; i < _children.size(); ++i) {
		delete _children[i];
	}

	_children.clear();
}