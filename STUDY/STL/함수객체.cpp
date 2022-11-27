#include "allHeader.h"
using namespace std;

struct Functor {
    void operator() (int a) {
        printf("%d\n", a);
    }
    void operator() (int a, int b) {
        printf("call func obj: %d, %d\n", a, b);
    }
};

struct Less {
    bool operator() (int a, int b) {
        return a < b;
    }
};

template<typename TP> 
struct Minus : public binary_function<TP, TP, TP> {
    TP operator() (const TP& a, const TP& b) {
        return a - b;
    }
};

int main() {

    // 함수 객체의 사용
    Functor functor;
    functor(10, 100);

    // 함수 객체 전달
    // java의 익명 구현 객체 전달하는 것과 비슷함
    int arr[] = {1, 2, 3, 4, 5};
    for_each(arr, arr + 5, Functor()); // algorithm header

    // STL에는 유용한 함수 객체가 있는데, less와 greater다
    // less는 < 연산자의 함수 객체이고, greater는 > 연산자의 함수 객체이다.
    // 또한 less와 greater는 bool 형을 반환하는 조건자이다.
    Less l;
    printf("10 < 20: %s\n", l(10, 20) ? "true" : "false"); // 암묵적 호출
    printf("10 < 20: %s\n", l.operator() (10, 20) ? "true" : "false"); // 명시적 호출

    // 대신 STL의 less와 greater는 템플릿 클래스이기 때문에 타입 지정이 필요하다.
    // less<int>() 처럼 말이다. 이는 int형 변수 < 연산자의 함수 객체를 의미한다.
    less<int> l2;
    printf("40 < 20: %s\n", l2(40, 20) ? "true" : "false"); // 암묵적 호출
    printf("30 < 20: %s\n", l2.operator() (30, 20) ? "true" : "false"); // 명시적 호출

    // 연산자 오버라이드와 템플릿을 적절히 이용하면 STL의 less와 greater와 같은 도구를 만드는 것은 정말 쉬울 것 같다.
    Minus<int> myMinus;
    printf("40 - 20: %d\n", myMinus(40, 20)); // 암묵적
    printf("40 - 20: %d\n", myMinus.operator() (40, 20)); // 명시적
    printf("40 - 20: %d\n", Minus<int>() (40, 20)); // 함수 객체 전달

    // SO EASY...
}