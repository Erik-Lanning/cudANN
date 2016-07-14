#pragma once
#include "node.h"

namespace cudANN
{
	template<class T>
	class adalineNode : public node<T>
	{
		friend class testAdalineNode;
	public:
		adalineNode(T learningRate) : learningRate_(learningRate), value_(CATEGORYONE), errorValue_(0)
		{}

		void computeAnswer()
		{
			T sum = 0;
			for (auto &iter : incomingEdges_)
			{
				sum += iter->getWeight() * iter->getOutgoingNodeValue();
			}
			if (sum < 0)
				value_ = CATEGORYTWO;
			else
				value_ = CATEGORYONE;
		}

		T getAnswer()
		{
			return value_;
		}

		void learn()
		{
			errorValue_ = value_ * ERROR_CONSTANT;
			auto deltaComponents = learningRate_ * errorValue_;
			for (auto &iter : incomingEdges_)
			{
				T nodeValue = iter->getOutgoingNodeValue();
				auto delta = nodeValue * deltaComponents;
				iter->setWeight(delta + iter->getWeight());
			}
		}

	private:
		// Used in the learning algorithm to properly tweak the error value.
		// It is derived from error = expected - computed, but because error is always -2, 0, or 2,
		// it can be computed from error = computed * -2.
		const double ERROR_CONSTANT = -2.0;
		const double CATEGORYONE = 1.0;
		const double CATEGORYTWO = -1.0;
		T learningRate_;
		T value_;
		T errorValue_;
	};
}