#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> getNeighbors(vector<vector<int>> &matrix, vector<vector<int>> &visited, int row, int col) {
    vector<vector<int>> neighbors = {};
    if(row > 0 && !visited[row - 1][col] && matrix[row - 1][col] == 1) {
        neighbors.push_back(vector<int> {row - 1, col});
    }
    if(row < matrix.size() - 1 && !visited[row + 1][col] && matrix[row + 1][col] == 1) {
        neighbors.push_back(vector<int> {row + 1, col});
    }
    if(col > 0 && !visited[row][col - 1] && matrix[row][col - 1] == 1) {
        neighbors.push_back(vector<int> {row, col - 1});
    }
    if(col < matrix[0].size() - 1 && !visited[row][col + 1] && matrix[row][col + 1] == 1) {
        neighbors.push_back(vector<int> {row, col + 1});
    }
    return neighbors;
}

void dfs(vector<vector<int>> &matrix, vector<int> &rivers, vector<vector<int>> &visited, int row, int col) {
    int riverLength = 0;
    vector<vector<int>> stack = {{row, col}};
    while(!stack.empty()) {
        vector<int> current = stack.back();
        stack.pop_back();
        row = current[0];
        col = current[1];
        if(visited[row][col]) {
            continue;
        }
        visited[row][col] = true;
        if(matrix[row][col] != 1) {
            continue;
        }
        riverLength++;
        vector<vector<int>> neighbors = getNeighbors(matrix, visited, row, col);
        for(const auto& neighbor : neighbors) {
            stack.push_back(neighbor);
        }
    }
    if(riverLength > 0) {
        rivers.push_back(riverLength);
    }
}

vector<int> riverSizes(vector<vector<int>> &matrix) {
    vector<int> rivers = {};
    vector<vector<int>> visited(matrix.size(), vector<int>(matrix[0].size(), false));
    for(int row = 0; row < matrix.size(); row++) {
        for(int col = 0; col < matrix[0].size(); col++) {
            if(!visited[row][col] && matrix[row][col] == 1) {
                dfs(matrix, rivers, visited, row, col);
            }
        }
    }
    return rivers;
}

int main() {
    vector<vector<int>> input = {
            {1, 0, 0, 1, 0},
            {1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1},
            {1, 0, 1, 1, 0}
    };
    vector<int> output = riverSizes(input);
    sort(output.begin(), output.end());
    for(auto element : output) {
        cout << element << " ";
    }
    return 0;
}