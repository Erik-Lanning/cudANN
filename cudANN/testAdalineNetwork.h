#pragma once
#include "adalineNetwork.h"

namespace cudANN
{
	class testAdalineNetwork
	{
	public:
		testAdalineNetwork()
		{
			testTraining();
		}

		void testTraining()
		{
			using std::vector;
			adalineNetwork<double> testNetwork(0.5, 3);
			// Modeling a simple "and" operation.
			vector<vector<double>> inputs = {
				{1, 0},
				{0, 1},
				{0, 0}, 
				{1, 1}
			};
			vector<double> expectedOutputs = {
				-1,
				-1,
				-1,
				1
			};
			testNetwork.train(&inputs, &expectedOutputs);
			assert(testNetwork.computeAnswer(&inputs[3]) == 1);
		}
	};
}