//////////////////////////////////////////////////////////////////////////////////
//      Bartosz Latosek 
//		Politechnika Warszawska
//		Zadanie rekrutacyjne : "Plakatowanie"
//////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>

std::vector<int> getBuildings();
std::vector<int>::const_iterator getLowestBuilding(const std::vector<int>& b);
std::vector<std::vector<int>> decreaseHeights(std::vector<int>& b, int n);

int countPosters(std::vector<int>& b);

int main()
{
	std::vector<int> buildings = getBuildings();
	std::cout << countPosters(buildings);
}

std::vector<int> getBuildings()
{
	int n;
	std::cin >> n;
	int _;
	int height;
	std::vector<int> buildings;
	for (int a = 0; a < n; a++)
	{
		std::cin >> _ >> height;
		buildings.push_back(height);
	}
	return buildings;
}

std::vector<int>::const_iterator getLowestBuilding(const std::vector<int>& buildings)
{
	auto cur_low = buildings.begin();
	for (auto i = buildings.begin(); i != buildings.end(); ++i)
	{
		if (*i < *cur_low)
			cur_low = i;
	}
	return cur_low;
}

std::vector<std::vector<int>> decreaseHeights(std::vector<int>& b, int n)
{
	std::vector<std::vector<int>> output;
	std::vector<int> curRow;
	for (auto i = b.begin(); i != b.end(); ++i)
	{
		*i-=n;
		if (*i != 0)
		{
			curRow.push_back(*i);
		}
		else
		{
			if (curRow.size())
			{
				output.push_back(curRow);
				curRow.clear();
			}
		}
	}
	output.push_back(curRow);
	return output;
}

int countPosters(std::vector<int>& b)
{
	static int posters = 0;
	if (b.size())
	{
		auto i = getLowestBuilding(b);
		std::vector<std::vector<int>> vectors = decreaseHeights(b, *i);
		posters++;
		for (auto v : vectors)
		{
			countPosters(v);
		}
		return posters;
	}
	else
		return 0;
}
