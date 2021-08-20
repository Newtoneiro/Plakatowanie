#pragma once
#include <vector>

using std::vector;

class Building
{
private:
	int height;
public:
	Building(int h = 0)
		:height(h){};
	
	int get_height() const { return height; }

	void decreaseHeight(int n) { height -= n; }
	
	~Building() = default;
};

class Street
{
private:
	vector<Building> buildings;
public:
	Street(int n, vector<int>& heights)
	{
		for (int i = 0; i < n; ++i)
		{
			buildings.push_back(Building(heights[i]));
		}
	}

	Street(vector<Building> b)
		:buildings(b) {}

	vector<Building> Buildings() const noexcept { return buildings; };

	vector<Building>::const_iterator getLowestBuilding() const
	{
		auto cur_low = buildings.begin();
		for (auto i = buildings.begin(); i != buildings.end(); ++i)
		{
			if (i->get_height() < cur_low->get_height())
				cur_low = i;
		}
		return cur_low;
	}

	vector<vector<Building>> decreaseHeights(int n) noexcept
	{
		vector<vector<Building>> output;
		vector<Building> curRow;
		for (auto i = buildings.begin(); i != buildings.end(); ++i)
		{
			i->decreaseHeight(n);
			if (i->get_height() != 0)
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
};

int posters = 0;

int countPosters(Street s)
{
	if (s.Buildings().size())
	{
		auto i = s.getLowestBuilding();
		vector<vector<Building>> vectors = s.decreaseHeights(i->get_height());
		posters++;
		for (auto v : vectors)
		{
			countPosters(Street(v));
		}
		return posters;
	}
	else
		return 0;
}