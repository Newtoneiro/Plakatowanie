//////////////////////////////////////////////////////////////////////////////////
//      Bartosz Latosek 
//		Politechnika Warszawska
//		Zadanie rekrutacyjne : "Plakatowanie"
//////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//----------= *Deklaracje* =---------


// Funkcje pomocnicze

std::vector<int> getBuildings(const std::string filename = "");
std::vector<int>::const_iterator getLowestBuilding(const std::vector<int>& b) noexcept;
std::vector<std::vector<int>> decreaseHeights(std::vector<int>& b, int n) noexcept;

// G³ówna funkcja rekursywna

int countPosters(std::vector<int>& b) noexcept;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::vector<int> buildings = getBuildings();
	std::cout << countPosters(buildings);
	return 0;
}

//----------= *Definicje* =---------



std::vector<int> getBuildings(const std::string filename)
{
	int n;
	int _;
	int height;
	std::vector<int> buildings;
	if (filename.empty())
	{
		std::cin >> n;
		for (int a = 0; a < n; a++)
		{
			std::cin >> _ >> height;
			buildings.push_back(height);
		}
	}
	else
	{
		try
		{
			std::ifstream file(filename);
			if (!file.good())
				throw std::runtime_error("Could not open file");
			file >> n;
			for (int a = 0; a < n; a++)
			{
				file >> _ >> height;
				buildings.push_back(height);
			}

		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what();
			exit(-1);
		}
	}
	return buildings;
}

std::vector<int>::const_iterator getLowestBuilding(const std::vector<int>& buildings) noexcept
{
	auto cur_low = buildings.begin();
	for (auto i = buildings.begin(); i != buildings.end(); ++i)
	{
		if (*i < *cur_low)
			cur_low = i;
	}
	return cur_low;
}

std::vector<std::vector<int>> decreaseHeights(std::vector<int>& b, int n) noexcept
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

int countPosters(std::vector<int>& b) noexcept
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
