#include <vector>

using namespace std;

int solution(vector<vector<int>> board, int k) {
    int answer = 0;
    // 행의 크기 및 열의 크기 
    const int row = static_cast<int>(board.size());
    const int col = static_cast<int>(board[0].size());
    // 조건을 만족하는 배열의 원소 누적
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            if(i + j <= k)
                answer += board[i][j];
    
    return answer;
}