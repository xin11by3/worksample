#include "solver.h"
#include <stack>
#include <cmath>

void initSolution(int N, std::vector<int>& solution){
  solution.assign(N + 1, 0);
}

bool checkFixedValid(int N, const std::vector<int>& fixedQueens){
  for(int c1 = 1; c1 <= N; c1++){
    if(fixedQueens[c1] == 0) continue;
    for(int c2 = c1 + 1; c2 <= N; c2++){
      if(fixedQueens[c2] == 0) continue;

      int r1 = fixedQueens[c1];
      int r2 = fixedQueens[c2];

      if(r1 == r2) return false;
      if(abs(r1 - r2) == abs(c1-c2)) return false;
    }
  }
  return true;
}

bool isSafe(int col, int row, const std::vector<int>& solution){
  for(int c = 1; c < col; c++){
    if (solution[c] == 0) continue;
    if(solution[c] == row)return false;
    if(abs(solution[c] - row) == abs(c - col)) return false;
  }
  return true;
}

int nextColumn(int col, int N, const std::vector<int>& fixedQueens){
  col++;
  while(col <= N && fixedQueens[col] != 0){
    col++;
  }
  return col;
}

int prevColumn(int col, const std::vector<int>& fixedQueens){
  col--;
  while(col >= 1 && fixedQueens[col] != 0){
    col--;
  }
  return col;
}

bool solveNQueens(int N, const std::vector<int>& fixedQueens, std::vector<int>& solution){
  std::stack<int> st;
  int col = 1;

  while (true) {
    if (col > N) return true; 

    if (fixedQueens[col] != 0) {
      int r = fixedQueens[col];
      if (isSafe(col, r, solution)) {
        solution[col] = r; 
        col++;     
        continue;
      } else {
        if (st.empty()) return false;

        col = prevColumn(col, fixedQueens);
        if (col < 1) return false;

        int last = st.top();
        st.pop();
        solution[col] = last; 
        continue;
      }
    }

    bool placed = false;
    int startRow = solution[col] + 1;

    for (int row = startRow; row <= N; row++) {
      if (isSafe(col, row, solution)) {
        solution[col] = row;
        st.push(row);  
        col++;  
        placed = true;
        break;
      }
    }

    if (!placed) {
      solution[col] = 0; 

      if (st.empty()) return false;

      col = prevColumn(col, fixedQueens);
      if (col < 1) return false;

      int last = st.top();
      st.pop();
      solution[col] = last; 
    }
  }
}
