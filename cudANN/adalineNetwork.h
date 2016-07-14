#pragma once
#include "adalineNode.h"
#include "link.h"

namespace cudANN
{
	using std::vector;

	template <class T>
	class adalineNetwork
	{
	public:
		adalineNetwork(T learningRate, unsigned int numberOfInputNodes, double threshold = 1.0) :
			adalineNode_(learningRate), biasNode_(1), threshold_(threshold)
		{
			biasNode_.connect(&adalineNode_);
			for (unsigned int i = 0; i < numberOfInputNodes; ++i)
			{
				node<T> *inputNode = new node<T>(0);
				inputNode->connect(&adalineNode_);
 				inputNodes_.push_back(inputNode);
			}
		}

		~adalineNetwork()
		{
			for (unsigned int i = 0; i < inputNodes_.size(); ++i)
				delete inputNodes_[i];
		}

		adalineNetwork(const adalineNetwork &other) = delete;
		adalineNetwork& operator=(const adalineNetwork &other) = delete;
		adalineNetwork(adalineNetwork &&other) = delete;
		adalineNetwork& operator=(adalineNetwork &&other) = delete;

		virtual T computeAnswer(vector<T> *inputs)
		{
			unsigned int inputSize = inputs->size();
			unsigned int inputNodeSize = inputNodes_.size();
			unsigned int end;
			if (inputSize > inputNodeSize)
				end = inputNodeSize;
			else
				end = inputSize;

			for (unsigned int i = 0; i < end; ++i)
			{
				inputNodes_[i]->setValue(inputs->at(i));
			}
			adalineNode_.computeAnswer();
			auto answer = adalineNode_.getAnswer();
			return answer;
		}

		virtual void train(vector<vector<T>> *inputs, vector<T> *expected)
		{
			auto inputSize = inputs->size();
			unsigned int correctInputs = 0;
			while (correctInputs < (int) inputSize * threshold_)
			{
				correctInputs = 0;
				for (unsigned int i = 0; i < inputSize; ++i)
				{	
					auto computedAnswer = computeAnswer(&inputs->at(i));
					auto expectedAnswer = expected->at(i);
					if (expectedAnswer != computedAnswer)
					{
						adalineNode_.learn();
						break;
					}
					else
						++correctInputs;
				}
			}
		}

		virtual void save() {}
		virtual void load() {}

	private:
		adalineNode<T> adalineNode_;
		node<T> biasNode_;
		vector<node<T> *> inputNodes_;
		double threshold_;
	};
}