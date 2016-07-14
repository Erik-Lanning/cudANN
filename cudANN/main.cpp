#include "testGlobalFunctions.h"
#include "testNodeLink.h"
#include "testAdalineNode.h"
#include "testAdalineNetwork.h"

int main()
{
	using namespace cudANN;
	testAllGlobalFunctions();
	testNodeLink verifyBaseLinkNode;
	testAdalineNode verifyAdalineNode;
	testAdalineNetwork verifyAdalineNetwork;
	getchar();
}