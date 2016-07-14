#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include "globalFunctions.h"
#include "link.h"

namespace cudANN
{
	template<class T>
	class node
	{
		friend class testNodeLink;
		friend class link<T>;
	public:
		node(int value = 0) : value_(value), isACopy_(false)
		{
			ID_ = ++totalNodes;
		}

		~node()
		{
			--totalNodes;
			if (isACopy_ == true)
				return;

			for (unsigned int i = 0; i < incomingEdges_.size(); ++i)
				delete incomingEdges_[i];
			for (unsigned int i = 0; i < outgoingEdges_.size(); ++i)
				delete outgoingEdges_[i];
		}
		
		node(const node<T> &other)
		{
			copyNode(other);
		}

		node<T>& operator=(const node<T> &other)
		{
			if (this == &other)
				return *this;

			copyNode(other);
			return *this;
		}
		
		void copyNode(const node<T> &other)
		{
			isACopy_ = true;
			ID_ = other.ID_;
			value_ = other.value_;
			incomingEdges_ = other.incomingEdges_;
			outgoingEdges_ = other.outgoingEdges_;
			++totalNodes;
		}

		void connect(node<T> *destination)
		{
			link<T> *theLink = new link<T>(this, destination);
		}

		void disconnect(node<T> *match)
		{
			for (unsigned int i = 0; i < incomingEdges_.size(); ++i)
			{
				if (linkContainsNode(incomingEdges_[i], match))
				{
					delete incomingEdges_[i];
				}
			}

			for (unsigned int i = 0; i < outgoingEdges_.size(); ++i)
			{
				if (linkContainsNode(outgoingEdges_[i], match))
				{
					delete outgoingEdges_[i];
				}
			}
		}

		bool linkContainsNode(link<T> *theLink, node<T> *match)
		{
			return (theLink->getIncomingNode() == match ||
					theLink->getOutgoingNode() == match);
		}
		
		virtual bool isACopy()
		{
			return isACopy_;
		}
		virtual T getValue()
		{
			return value_;
		}

		virtual void setValue(T value)
		{
			value_ = value;
		}

		virtual const bool equals(const node<T> *other)
		{
			bool expectedValues = true;
			bool compareValues = (value_ == other->value_);
			bool compareIncomingEdges = (incomingEdges_ == other->incomingEdges_);
			bool compareOutgoingEdges = (outgoingEdges_ == other->outgoingEdges_);
			return isEqual(expectedValues, compareValues, compareIncomingEdges, compareOutgoingEdges);
		}

		virtual void save() {}
		virtual void load() {}

	protected:
		static unsigned long totalNodes;
		unsigned long ID_;
		T value_;
		std::vector<link<T> *> incomingEdges_;
		std::vector<link<T> *> outgoingEdges_;
		bool isACopy_;
		
		void addOutgoingEdge(link<T> *theLink)
		{
			outgoingEdges_.push_back(theLink);
		}

		void addIncomingEdge(link<T> *theLink)
		{
			incomingEdges_.push_back(theLink);
		}

		void removeOutgoingEdge(link<T> *theLink)
		{
			outgoingEdges_.erase(std::remove(outgoingEdges_.begin(), outgoingEdges_.end(), theLink), 
				outgoingEdges_.end());
		}

		void removeIncomingEdge(link<T> *theLink)
		{
			incomingEdges_.erase(std::remove(incomingEdges_.begin(), incomingEdges_.end(), theLink),
				incomingEdges_.end());
		}
	};
	template<typename T>
	unsigned long node<T>::totalNodes = 0;
}