#include "CppUnitTest.h"
#include "../Plakatowanie/Classes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlakatowanieUnitTest
{
	TEST_CLASS(PlakatowanieUnitTest)
	{
	public:
		
		TEST_METHOD(testCreateBuilding)
		{
			Building dom(7);
			Assert::IsTrue(7 == dom.get_height());
		}

		TEST_METHOD(testCreateBuildingEmpty)
		{
			Building dom;
			Assert::IsTrue(0 == dom.get_height());
		}

		TEST_METHOD(testBuildingDecreaseHeight)
		{
			Building dom(7);
			Assert::IsTrue(7 == dom.get_height());
			dom.decreaseHeight(4);
			Assert::IsTrue(3 == dom.get_height());
		}

		TEST_METHOD(testCreateStreet)
		{
			vector<int> h{ 4, 2, 6, 8, 2, 5, 8 };
			Street s(7, h);
			Assert::IsTrue(7 == s.Buildings().size());
		}

		TEST_METHOD(testStreetLowestBuilding)
		{
			vector<int> h{ 2, 5, 6, 8, 3, 6, 7 };
			Street s(7, h);
			auto i = s.getLowestBuilding();
			Assert::IsTrue(2 == i->get_height());
		}

		TEST_METHOD(testStreetLowestBuilding2)
		{
			vector<int> h{ 29, 189, 16, 82, 31, 64, 75 };
			Street s(7, h);
			auto i = s.getLowestBuilding();
			Assert::IsTrue(16 == i->get_height());
		}

		TEST_METHOD(testStreetDecreaseHeights)
		{
			vector<int> h{ 16, 189, 16, 82, 31, 64, 75 };
			Street s(7, h);
			auto i = s.getLowestBuilding();
			Assert::IsTrue(16 == i->get_height());
			Assert::IsTrue(7 == s.Buildings().size());
			
			s.decreaseHeights(16);

			i = s.getLowestBuilding();
			Assert::IsTrue(0 == i->get_height());
			Assert::IsTrue(7 == s.Buildings().size());
		}

		TEST_METHOD(testStreetCopy)
		{
			vector<int> h{ 16, 189, 16, 82, 31, 64, 75 };
			Street s(7, h);
			Street s2(s);
			auto i = s2.getLowestBuilding();
			Assert::IsTrue(16 == i->get_height());
			Assert::IsTrue(7 == s2.Buildings().size());
		}

		TEST_METHOD(testCountPosters1)
		{
			vector<int> h{ 16, 189, 16, 82, 31, 64, 75 };
			Street s(7, h);
			Assert::IsTrue(6 == countPosters(s));
		}

		TEST_METHOD(testCountPosters2)
		{
			vector<int> h{2, 2, 2, 2, 2};
			Street s(5, h);
			int a = countPosters(s);
			Assert::AreEqual(a, 1);
		}
	};
}
