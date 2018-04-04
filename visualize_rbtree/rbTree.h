#ifndef rbTree_
#define rbTree_

#include <utility>

using namespace std;

template <class K, class E>
class rbTree {
public:
	virtual ~rbTree() {};
	virtual void insert(pair<K,E>&) = 0;	//≤Â»Î
	virtual E find(const K&) const = 0;	//≤È’“
	virtual void erase(const K&) = 0;	//…æ≥˝
};

#endif