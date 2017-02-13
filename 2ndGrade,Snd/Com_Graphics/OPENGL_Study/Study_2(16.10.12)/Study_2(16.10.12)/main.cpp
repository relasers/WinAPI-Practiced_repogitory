#include <iostream>
#include <Windows.h>
using namespace std;

class CFramework {
private:
	int count{ 0 }; // 균일 초기화
public:
	void Draw();
	void Update();

	void Run();
};

// namespace에 이름이 안 붙어있을 시 :: 이 cpp 파일 내에서만 사용이 가능하다
// 익명 namespace,비슷 :: static
// 전역변수 사용하기 싫을 때 
namespace {
	CFramework framework;
};

int main() {
	framework.Run();
}

void CFramework::Draw()
{
	system("cls");
	
	cout << "나는 천재다. (" << count++ << ")" << endl;
}

void CFramework::Update()
{
	Sleep(1000);
}

void CFramework::Run()
{
	while (true) {
		Update();
		Draw();
	}
}
