
#include <iostream>
#include <random>
#include "VectorND.h"
#include "Matrix.h"
#include "Vec3.h"
#include "Random.h"
#include <thread>
#include "Angle.h"
#include "AngleInterval.h"
#include "CreateStrategy.h"
#include "RunTime_Factory.h"
template<typename type>
static constexpr type data = 1000000;

template<>
constexpr float data<float> = 111111;

class Base
{
public:
	Base() : m_data(std::make_unique<int>(30)){}
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

int main()
{
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
