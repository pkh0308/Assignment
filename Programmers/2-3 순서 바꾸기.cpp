#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    // n번째 원소와 그 이후 원소들로 초기화
    vector<int> answer(num_list.begin() + n, num_list.end());
    // num_list의 크기만큼 capacity 확보
    answer.reserve(num_list.size());
    // 처음부터 n-1번째 원소까지 추가
    for(int i = 0; i < n; ++i)
        answer.push_back(num_list[i]);
    
    return answer;
}