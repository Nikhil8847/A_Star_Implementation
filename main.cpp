#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::sort;


using std::vector;

enum class State {kStart, kEnd, kPath, kEmpty, kObstacle, kClosed};

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
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
    case State::kStart: return "🚦   ";
    case State::kEnd: return "🏁   ";
    case State::kPath: return "🚗   ";
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
  int f1=first[2]+first[3];
  int f2 = second[2]+second[3];
  return f1 > f2;
}

int Heuristic(int x1, int y1,int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}



void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &board){
  vector<int> _node{x, y, g, h};

  openNodes.push_back(_node);
  board[x][y] = State::kClosed;
}

void CellSort(vector<vector<int>> *v){
  sort(v->begin(), v->end(), compare);
}

bool CheckValidCell(vector<vector<State>> &board, int x, int y){
  
  // the coordinate is on the board
  bool on_board_x = (x >= 0 and x < board.size());
  bool on_board_y = (y >= 0 and y < board[0].size());
  
  // The coordinate on block is empty, but not obstacle or closed
  if(on_board_x and on_board_y)
    return board[x][y] == State::kEmpty;

  return false;
}

void ExpandNeighbours(vector<int> &_currentNode, vector<vector<int>> &openNodes, vector<vector<State>> &board, int goal[]){
  int x1 = _currentNode[0];
  int y1 = _currentNode[1];
  int g = _currentNode[2];
  int h = _currentNode[3];
  

  for(int i = 0;i < 4; i++){
    int x2 = delta[i][0]+x1;
    int y2 = delta[i][1]+y1;
    // check that this neighbour is on grid and not closed
    if(CheckValidCell(board, x2, y2)){
      int g2 = g+1;
      int h2 = Heuristic(x2, y2, goal[0],goal[1]);
      AddToOpen(x2, y2, g2, h2, openNodes, board);
    }
  }
}

vector<vector<State>> Search(vector<vector<State>> &board, int start[2], int goal[2]){
    vector<vector<State>> boardPath(board.size());
    for(int i = 0;i < board.size() ;i++){
      for(auto x : board[i]){
        boardPath[i].emplace_back(x);
      }
    }
    vector<vector<int>> openNodes;

    // x and y coordinate of starting position
    int x = start[0];
    int y = start[1];

    // A* specific values of starting position.
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    
    AddToOpen(x, y, g, h, openNodes, board);
    
    while(openNodes.size()){
      // Sort in decreasing order of (g+h) value
      CellSort(&openNodes);

      // Get the node with lowerst g+h value
      auto current = openNodes.back();
      openNodes.pop_back();

      int x1 = current[0];
      int y1 = current[1];
      boardPath[x1][y1] = State::kPath;

      if(goal[0] == x1 and goal[1] == y1){
        boardPath[start[0]][start[1]] = State::kStart;
        boardPath[x1][y1] = State::kEnd;
        return boardPath;
      }
      ExpandNeighbours(current, openNodes, board, goal);
    }
    
    return board;
}


int main() {
  auto board = ReadBoardFile("1.board");
  // PrintBoard(board);
  int start[2]{0, 0};
  int goal[2]{4, 5};
  auto PathGrid = Search(board, start, goal);
  PrintBoard(PathGrid);
}