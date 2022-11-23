#include "KRASKAL.h"


int main()
{
	GRAPH gr("test0.txt");
	gr.fill_graph();
	gr.kraskal();

	system("pause");
	return 0;
}