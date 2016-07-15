# cudANN
A simple SANN base, includes basic ADALINE network support.

Here are some basic examples (modified from the unit tests).

```
double learningRate = 0.5;
unsigned int numberOfInputNodes = 2;
adalineNetwork<double> testNetwork(learningRate, numberOfInputNodes);
			
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
```
