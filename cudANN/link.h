#pragma once
#include <vector>
#define NULL 0

namespace cudANN
{
	template<class T>
	class node;

	template<class T>
	class link
	{
		friend class node<T>;
		friend class testNodeLink;
	public:
		link(node<T> *outgoingNode, node<T> *incomingNode, T weight = defaultWeight) :
			weight_(weight)
		{
			ID_ = ++totalLinks;
			connect(outgoingNode, incomingNode);
		}

		link() : outgoingNode_(NULL), incomingNode(NULL), weight_(defaultWeight)
		{
			ID_ = ++totalLinks;
		}

		~link()
		{
			--totalLinks;
			outgoingNode_->removeOutgoingEdge(this);
			incomingNode_->removeIncomingEdge(this);
		}

		link(const link<T> &other) = delete;
		link<T>& operator=(const link<T> &other) = delete;
		link(link<T> &&other) = delete;
		link<T>& operator=(link<T> &&other) = delete;

		void connect(node<T> *source, node<T> *destination)
		{
			outgoingNode_ = source;
			incomingNode_ = destination;
			source->addOutgoingEdge(this);
			destination->addIncomingEdge(this);
		}

		node<T> *getOutgoingNode()
		{
			return outgoingNode_;
		}

		node<T> *getIncomingNode()
		{
			return incomingNode_;
		}

		virtual T getWeight()
		{
			return weight_;
		}

		virtual void setWeight(T weight)
		{
			weight_ = weight;
		}

		virtual T getOutgoingNodeValue()
		{
			return outgoingNode_->value_;
		}

		virtual T getIncomingNodeValue()
		{
			return incomingNode_->value_;
		}

		virtual void save() {}
		virtual void load() {}

	private:
		static const T defaultWeight;
		static unsigned long totalLinks;
		unsigned long ID_;
		T weight_;
		node<T> *outgoingNode_;
		node<T> *incomingNode_;
	};
	template<typename T>
	const T link<T>::defaultWeight = 1;
	template<typename T>
	unsigned long link<T>::totalLinks = 0;
}