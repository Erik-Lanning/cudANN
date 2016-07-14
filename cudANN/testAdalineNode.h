#pragma once
#include <cassert>
#include "adalineNode.h"

namespace cudANN
{
	class testAdalineNode
	{
	public:
		testAdalineNode(): theNode_(0.5)
		{
			const int numNodes = 3;
			node<double> inputNodes[numNodes];
			for (int i = 0; i < numNodes; ++i)
			{
				inputNodes[i].setValue(0.5);
				inputNodes[i].connect(&theNode_);
				inputNodes_.push_back(std::move(inputNodes[i]));
			}

			testComputeAnswer();
			testLearn();
		}

		void testComputeAnswer()
		{
			// A set of all positive weights and values should compute as 1.
			theNode_.computeAnswer();
			assert(theNode_.getAnswer() == 1);
		}

		void testLearn()
		{
			// Loop until category changes to -1, i.e. learning has occured.
			while (theNode_.getAnswer() == 1)
			{
				theNode_.learn();
				theNode_.computeAnswer();
			}
			assert(theNode_.getAnswer() == -1);
		}

	private:
		adalineNode<double> theNode_;
		std::vector<node<double>> inputNodes_;
	};
}