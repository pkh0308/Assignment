#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, int k) {
    // 꼬치 및 음료수 가격
    const int skewer = 12000;
    const int drink = 2000;
    // 음료 서비스 제공 횟수 
    int service = n / 10;
    // 음료수 가격은 서비스 제공 횟수만큼 차감하여 계산
    // 단, 서비스 횟수가 마신 음료수 수 이상이라면 0으로 처리
    return n * skewer + clamp(k - service, 0, k) * drink;
}