#include "ALGraph.h"

int main()
{
	ALGraph wudgGraph(9);
	wudgGraph.CreateWUDG();
	/*wudgGraph.displayGraph();*/

	wudgGraph.PRIM(1);

	//ALGraph<char> wdgGraph(5);
	//wdgGraph.createWDG();
	//wdgGraph.displayGraph();
	//wdgGraph.BellmanFord(1);

	//ALGraph<char> wdgGraph1(6);
	//wdgGraph1.createWDG1();
	//wdgGraph1.displayGraph();
	//wdgGraph1.DagShortestPaths(2);

	//ALGraph<char> wdgGraph2(5);
	//wdgGraph2.createWDG2();
	//wdgGraph2.displayGraph();
	//wdgGraph2.Dijkstra(1);

	system("pause");
    return 0;
}