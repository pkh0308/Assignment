#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<int> query) {
    // 배열의 왼쪽 끝, 오른쪽 끝 인덱스를 저장할 변수 선언
    int left = 0, right = query.size();
    for(int i = 0; i < query.size(); ++i)
    {
        if((i & 1) == 0) // 짝수 인덱스
            right = left + query[i] + 1;
        else // 홀수 인덱스
            left += query[i];
    }
    // 쿼리 실행 후 arr의 왼쪽 끝부터 오른쪽 끝까지 반환
    return vector<int>(arr.begin() + left, arr.begin() + right);
}