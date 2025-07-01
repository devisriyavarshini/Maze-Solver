#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 100;
char maze[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int> parent[MAX][MAX];

int rows, cols;
int startX, startY, endX, endY;

int dx[] = {-1, 1, 0, 0}; // up, down
int dy[] = {0, 0, -1, 1}; // left, right

bool isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols &&
           maze[x][y] != '#' && !visited[x][y];
}

bool bfs() {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        int x = curr.first;
        int y = curr.second;

        q.pop();

        if (x == endX && y == endY) return true;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny)) {
                q.push({nx, ny});
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
            }
        }
    }

    return false;
}

void reconstructPath() {
    int x = endX, y = endY;
    while (!(x == startX && y == startY)) {
        if (maze[x][y] != 'E') maze[x][y] = '*';
        pair<int, int> p = parent[x][y];
        x = p.first;
        y = p.second;
    }
}


void readMaze(string filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file.\n";
        exit(1);
    }

    file >> rows >> cols;
    file.ignore();

    for (int i = 0; i < rows; ++i) {
        file.getline(maze[i], MAX);
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') {
                startX = i; startY = j;
            }
            if (maze[i][j] == 'E') {
                endX = i; endY = j;
            }
        }
    }

    file.close();
}

void printMaze() {
    cout << "\nSolved Maze:\n";
    for (int i = 0; i < rows; ++i)
        cout << maze[i] << endl;
}

int main() {
    readMaze("maze.txt");

    if (bfs()) {
        reconstructPath();
        printMaze();
    } else {
        cout << "No path found from S to E.\n";
    }

    return 0;
}

