#ifndef NODE_TREE_H
#define NODE_TREE_H

#include "core/object.h"
#include "core/threading/rw_lock.h"

class Node;

class NodeTree : public Object {
	RCPP_OBJECT(NodeTree, Object);

public:
	Node *get_root();
	virtual void set_root(Node *root);

	virtual void update();

	void request_write_lock();

	virtual float get_update_delta_time();

	NodeTree();
	~NodeTree();

protected:
	virtual void _send_update();

	Node *_root_node;
	float _update_interval;

	bool _write_lock_requested;
	RWLock _rw_lock;
};

#endif