// null 1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <assert.h>
#include <cassert>
#include <stdexcept>

//class Test
//{
//public:
//		void Show()
//		{
//			std::cout << "Hello,World!" << std::endl;
//		}
//
//};
//
//void Func(Test*test)
//{
//	こうあるべきだ
//	assert(test != nullptr);
//
//	test->Show();
//
//}

class Weapon {
public:
	void Use() {}
};

class Sword : public Weapon {};

class Player {
	std::shared_ptr<Weapon> weapon_;
public:
	// 所有権を受け取り、null であれば即時にエラーにする（以後はチェック不要）
	explicit Player(std::shared_ptr<Weapon> weapon)
		: weapon_(std::move(weapon)) {
		assert(weapon_ && "weapon must not be null");
		if (!weapon_) throw std::invalid_argument("weapon must not be null");
		std::cout << weapon_.use_count() << std::endl;
	}
	void Attack() {
		// コンストラクタで非nullを保証しているためチェック不要
		weapon_->Use();
	}
};

int main()
{
	//auto wp = std::make_shared<Weapon>();

	////コピー(参照カウント＋１)
	//Player p(wp);	

	////ムーブ（所有権を移動）
	//Player q(std::move(wp));	

	//auto a = std::make_shared<int>();
	//auto b = a;
	//auto c = std::move(a);

	auto sword = std::make_shared<Sword>();
	Player p2(std::move(sword));

	p2.Attack();

	return 0;

	//if (p != nullptr)
	//{
	//	delete p;
	// }
	/*Func(new Test());
	Func(nullptr);*/
}

