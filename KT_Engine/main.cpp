
#include <iostream>
#include <thread>
#include "Angle.h"
#include "AngleInterval.h"
#include "Dispacher.h"

template<typename type>
static constexpr type data = 1000000;

template<>
constexpr float data<float> = 111111;

class Base
{
public:
	Base() : m_data(std::make_unique<int>(30)){}
	Base(int t): m_data(std::make_unique<int>(t)){}
	Base(const Base& other) : m_data(std::make_unique<int>(*other.m_data)){}
	virtual ~Base() = default;
	virtual void test()
	{
		std::cout << "toto";
	}
protected:
	std::unique_ptr<int> m_data;
};

struct Derived1 : public Base
{
	Derived1():m_t(0)
	{
		
	}
	Derived1(int t): m_t(t)
	{
		m_data = std::make_unique<int>(t);
	}
	 void test() override
	{
		std::cout << *m_data;
	}
private:
	int m_t;
};

struct Derived2 : public Base
{
	Derived2() :m_t(0)
	{

	}
	Derived2(int t) : m_t(t)
	{
		m_data = std::make_unique<int>(t);
	}
	void test() override
	{
		std::cout << *m_data;
	}
private:
	int m_t;
};

void toto(Base& lhs, Base& rhs,int)
{
	std::cout << "base";
}
void toto(Derived2& lhs, Derived1& rhs, int t)
{
	std::cout << " Derived 1 et Devived 2" << t;
}

void toto(Derived1& lhs, Derived1& rhs, int t)
{
	std::cout << " Derived 1 et Devived 1" << t;
}

void toto(Derived2& lhs, Derived2& rhs, int t)
{
	std::cout << " Derived 2 et Devived 2" << t;
}

void info(Base& data)
{
	std::cout << typeid(data).name();
}


void totoLambda(Base& test, Base& test2,int)
{
	std::cout << " GOAL" << std::endl;
}


int main()
{
	Derived1 d;
	info(d);
	auto angle = Degree<float>(100,  SignedInterval<float>{});
	angle.AsDegrees();
	angle.SetInterval(UnsignedInterval<float>());



	/*Derived1 t(12);
	Derived1 t2(t);
	t2.test();
	Base testBase;
	Base Test2Base(testBase);
	RT_Pointer_Factory <std::string,Base> factory{};
	factory.Register<Derived1>("titi");
	factory.Create("titi");*/
	
	//auto StaticAngle = Degree<float,StaticUnsignedInterval<float>>(120);
	//std::cout << StaticAngle.AsDegrees() << std::endl;
	//std::cout << StaticAngle.AsRadians() << std::endl;
	/*StaticUnsignedInterval<float> toto4;
	std::cout << Math::PI;
	Matrix<int, 2, 2> toto(1, 2, 3, 4);
	Vec3<float> test(1,2,3);
	Vec3<float> test2(3, 3, 3);
	if (test2.IsNull())
		std::cout << "nulllllllllll" << std::endl;
	 test = test2;
	test += test2;
	auto test3 = test + test2;
	std::cout << UseRandom().getRandomNumber<int>(1, 10);*/
	return 0;
}
