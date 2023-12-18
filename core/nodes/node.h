#ifndef NODE_H
#define NODE_H

#include "core/object.h"
#include "core/containers/vector.h"

class NodeTree;

class Node : public Object {
	RCPP_OBJECT(Node, Object);

public:
	enum {
		NOTIFICATION_ENTER_TREE = 0,
		NOTIFICATION_EXIT_TREE = 1,
		NOTIFICATION_PARENTED = 2,
		NOTIFICATION_UNPARENTED = 3,
		NOTIFICATION_CHILD_ADDED = 4,
		NOTIFICATION_CHILD_REMOVED = 5,
		NOTIFICATION_CHILD_MOVED = 6,
		NOTIFICATION_UPDATE = 7,
		NOTIFICATION_TREE_WRITE_LOCKED = 8,
	};

	bool is_in_tree() const;

	Node *get_parent();
	void set_parent(Node *parent);

	int get_child_count();
	Node *get_child(int index);
	void add_child(Node *child);
	void remove_child_index(int index);
	void remove_child(Node *child);

	NodeTree *get_tree();
	void set_tree(NodeTree *tree);

	virtual void notification(const int what);
	virtual void _notification(const int what);

	Node();
	~Node();

protected:
	bool _in_tree;
	Node * _parent;
	Vector<Node *> _children;
	NodeTree *_tree;
};

#endif