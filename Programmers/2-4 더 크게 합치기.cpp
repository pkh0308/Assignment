#include <string>

using namespace std;

int solution(int a, int b) {
    // a, b를 각각 문자열로 변환
    string sa = to_string(a);
    string sb = to_string(b);
    // 문자열 상태로 a+b, b+a 순서로 붙인 후 다시 정수로 변환
    // 둘 중 큰 값 반환
    int left = stoi(sa + sb);
    int right = stoi(sb + sa);
    return max(left, right);
}