#include <string>

using namespace std;

int solution(string my_string, string is_prefix) {
    // is_prefix가 더 길다면 접두사 불가능
    if(is_prefix.size() > my_string.size()) return 0;
    // my_string의 처음부터 is_prefix의 길이만큼 부분 문자열을 땄을 때
    // is_prefix와 동일하다면 접두사
    return my_string.substr(0, is_prefix.size()) == is_prefix;
}