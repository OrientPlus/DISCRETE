#include "KRASKAL.h"


int main()
{
	GRAPH gr("test5.txt");
	gr.fill_graph();
	gr.kraskal();

	system("pause");
	return 0;
}