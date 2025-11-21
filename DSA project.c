#include <stdio.h>
#include <string.h>
#define MAX 10
#define INF 9999

void navigation(int graph[MAX][MAX], int n, int start, int end, char places[MAX][30]) {
    int distance[MAX], visit[MAX], parent[MAX];
    int i, j, count, minDist, nextNode;

    for (i = 0; i < n; i++) {
        distance[i] = graph[start][i];
        parent[i] = start;
        visit[i] = 0;
    }

    distance[start] = 0;
    visit[start] = 1;
    count = 1;

    while (count < n - 1) {
        minDist = INF;
        for (i = 0; i < n; i++)
            if (distance[i] < minDist && !visit[i]) {
                minDist = distance[i];
                nextNode = i;
            }

        visit[nextNode] = 1;
        for (i = 0; i < n; i++)
            if (!visit[i])
                if (minDist + graph[nextNode][i] < distance[i]) {
                    distance[i] = minDist + graph[nextNode][i];
                    parent[i] = nextNode;
                }
        count++;
    }

    printf("\nShortest distance from %s to %s: %d\n", places[start], places[end], distance[end]);
    printf("Path: %s", places[end]);
    j = end;
    do {
        j = parent[j];
        printf(" <- %s", places[j]);
    } while (j != start);
    printf("\n");
}

void displayGraph(int graph[MAX][MAX], int n, char places[MAX][30]) {
    int i, j;
    printf("\n Campus Map (Distance Matrix):\n");
    printf("       ");
    for (i = 0; i < n; i++)
        printf("%10s", places[i]);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%10s", places[i]);
        for (j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf("%10s", "∞");
            else
                printf("%10d", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 0, i, j, choice;
    int graph[MAX][MAX];
    char places[MAX][30];
    int start, end;

    printf("====== CAMPUS NAVIGATION SYSTEM ======\n");

    while (1) {
        printf("\n========= MENU =========\n");
        printf("1. Add Locations\n");
        printf("2. Enter Path Distances\n");
        printf("3. Display Campus Map\n");
        printf("4. Find Shortest Path\n");
        printf("5. Exit\n");
        printf("=========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
        case 1:
            printf("Enter number of locations: ");
            scanf("%d", &n);
            getchar();
            for (i = 0; i < n; i++) {
                printf("Enter name of location %d: ", i + 1);
                fgets(places[i], sizeof(places[i]), stdin);
                places[i][strcspn(places[i], "\n")] = '\0';
            }
            printf("\nlocation added successfully!\n");
            break;

        case 2:
            if (n == 0) {
                printf("please added locations first!\n");
                break;
            }
            printf("\nEnter distance between locations (use %d for no direct path):\n", INF);
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    printf("Distance from %s to %s: ", places[i], places[j]);
                    scanf("%d", &graph[i][j]);
                }
            }
            printf("\n distances added successfully!\n");
            break;

        case 3:
            if (n == 0) {
                printf("No locations added yet!\n");
                break;
            }
            displayGraph(graph, n, places);
            break;

        case 4:
            if (n == 0) {
                printf("please added locations and paths first!\n");
                break;
            }
            printf("\nChoose starting location:\n");
            for (i = 0; i < n; i++)
                printf("%d. %s\n", i + 1, places[i]);
            scanf("%d", &start);

            printf("Choose destination location:\n");
            for (i = 0; i < n; i++)
                printf("%d. %s\n", i + 1, places[i]);
            scanf("%d", &end);

            if (start < 1 || end < 1 || start > n || end > n) {
                printf("Invalid choice!\n");
            } else {
                navigation(graph, n, start - 1, end - 1, places);
            }
            break;

        case 5:
            printf("\nExiting Campus Navigation System. Goodbye!\n");
            return 0;

        default:
            printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}