#include <stdio.h>
#define inf 1000

int main()
{
    int n;
    int cost[10][10], dist[10][10], next[10][10];

    printf("How many routers? ");
    scanf("%d", &n);

    printf("Enter initial Routing Table:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);

            if (cost[i][j] == -1)
            {
                cost[i][j] = inf;
                dist[i][j] = inf;
                next[i][j] = -1;
            }
            else
            {
                dist[i][j] = cost[i][j];
                next[i][j] = j;
            }
        }
    }

    /* Distance Vector Algorithm */
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    /* Routing Tables */
    for (int i = 0; i < n; i++)
    {
        printf("\nRouter %d:\n", i);
        printf("Destination Distance NextRouter\n");

        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] >= inf)
                printf("%5d %10d %10d\n", j, -1, -1);
            else
                printf("%5d %10d %10d\n", j, dist[i][j], next[i][j]);
        }
    }

    /* Cost Matrix */
    printf("\nCost Matrix:\n ");
    for (int i = 0; i < n; i++)
        printf("%4d", i);

    printf("\n----------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%2d |", i);
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] >= inf)
                printf("%4d", -1);
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}-
