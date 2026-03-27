#include <stdio.h>
struct node 
{
	unsigned dist[20];
	unsigned from[20];
} rt[10];

int main()
{
	int costmat[20][20];
	int nodes, i, j, k;
	int count;
	printf("\nEnter the number of nodes: ");
	scanf("%d", &nodes);
	printf("\nEnter the cost matrix:\n");
	// Input cost matrix and initialize routing table
	for (i = 0; i < nodes; i++)
	{
		for (j = 0; j < nodes; j++)
		{
			scanf("%d", &costmat[i][j]);
			if (i == j)
				costmat[i][j] = 0;
				
			rt[i].dist[j] = costmat[i][j];
			rt[i].from[j] = j;
		}
	}
	// Bellman-Ford Algorithm
	do
	{
		count = 0;
		for (i = 0; i < nodes; i++) 
		{
			for (j = 0; j < nodes; j++) 
			{
				for (k = 0; k < nodes; k++) 
				{
					if (rt[i].dist[j] > costmat[i][k] + rt[k].dist[j])
					{
						rt[i].dist[j] = costmat[i][k] + rt[k].dist[j];
						rt[i].from[j] = k;
						count++;
					}
				}
			}
		}
	} while (count != 0);
	// Print routing tables
	for (i = 0; i < nodes; i++)
	{
		printf("\nRouting table for Router %d:\n", i + 1);
		for (j = 0; j < nodes; j++)
		{
			printf("Destination: %d Next Hop: %d Distance: %d\n",j + 1,rt[i].from[j] + 1,rt[i].dist[j]);
		}
	}
	return 0;
}

/*
Enter the number of nodes: 3

Enter the cost matrix:
0 2 7
2 0 1
7 1 0

Routing table for Router 1:
Destination: 1 Next Hop: 1 Distance: 0
Destination: 2 Next Hop: 2 Distance: 2
Destination: 3 Next Hop: 2 Distance: 3

Routing table for Router 2:
Destination: 1 Next Hop: 1 Distance: 2
Destination: 2 Next Hop: 2 Distance: 0
Destination: 3 Next Hop: 3 Distance: 1

Routing table for Router 3:
Destination: 1 Next Hop: 2 Distance: 3
Destination: 2 Next Hop: 2 Distance: 1
Destination: 3 Next Hop: 3 Distance: 0
*/