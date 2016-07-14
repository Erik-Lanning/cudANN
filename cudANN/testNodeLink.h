#pragma once
#include <cassert>
#include <iostream>
#include <utility>
#include "link.h"
#include "node.h"

namespace cudANN
{
	class testNodeLink
	{
	public:
		testNodeLink()
		{
			testConstructors();
			testRemoveOutgoingEdge();
			testNodeConnect();
			testNodeDisconnect();
			testCopyNode();
		}

		void testConstructors()
		{
			node<int> testNodes[2];
			link<int> testLink(&testNodes[0], &testNodes[1]);

			assert(testLink.incomingNode_ != NULL);
			assert(testLink.outgoingNode_ != NULL);
			assert(testNodes[0].outgoingEdges_.size() > 0);
			assert(testNodes[1].incomingEdges_.size() > 0);
			assert(testNodes[0].outgoingEdges_[0] == testNodes[1].incomingEdges_[0]);
		}

		void testRemoveOutgoingEdge()
		{
			node<int> testNodes[2];
			link<int> testLink(&testNodes[0], &testNodes[1]);

			assert(testNodes[0].outgoingEdges_.size() == 1);
			testNodes[0].removeOutgoingEdge(&testLink);
			assert(testNodes[0].outgoingEdges_.size() == 0);
		}

		void testNodeConnect()
		{
			node<int> *testNode1 = new node<int>();
			node<int> *testNode2 = new node<int>();
			testNode1->connect(testNode2);

			assert(testNode1->outgoingEdges_.size() > 0);
			assert(testNode2->incomingEdges_.size() > 0);
			assert(testNode1->outgoingEdges_[0] == testNode2->incomingEdges_[0]);

			delete testNode1;
			assert(testNode2->incomingEdges_.size() == 0);
			delete testNode2;
		}

		void testNodeDisconnect()
		{
			node<int> testNodes[2];
			testNodes[0].connect(&testNodes[1]);
			testNodes[0].disconnect(&testNodes[1]);
			assert(testNodes[0].outgoingEdges_.size() == 0);
		}

		void testCopyNode()
		{
			node<int> testNodes[2];
			link<int> testLink(&testNodes[0], &testNodes[1]);
			node<int> copyNode(testNodes[0]);
			assert(copyNode.isACopy());
			assert(copyNode.equals(&testNodes[0]));

			copyNode = testNodes[1];
			assert(copyNode.isACopy());
			assert(copyNode.equals(&testNodes[1]));
		}
	};
}