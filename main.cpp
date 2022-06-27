#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;


using std::vector;

enum class State {kEmpty, kObstacle, kClosed};

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}

vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    default: return "0   "; 
  }
}

void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}
bool compare(vector<int> &first, vector<int> &second){
  int f1, f2;

  return f1 < f2;
}

vector<vector<State>> Search(vector<vector<State>> &board, int start[2], int goal[2]){
    vector<vector<State>> boardPath;
    vector<vector<int>> openNodes;
    int x = start[0], y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    
    openNodes.push_back({x, y, g, h});
    
    
    return boardPath;
}


int Heuristic(int x1, int y1,int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &board){
  vector<int> _node{x, y, g, h};

  openNodes.push_back(_node);
  board[x][y] = State::kClosed;
}
int main() {
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, (int []){0, 0}, (int []){4, 5});
  PrintBoard(solution);
}