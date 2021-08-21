#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>

using std::vector;

class Building
	// This is a single building class that only holds information about building's height
	// since the width is useless in the alghoritm.
{
private:
	int height;
public:
	Building(int h = 0)
		:height(h) {};

	Building(const Building& b)    // copy constr,
		:height(b.height) {}

	int get_height() const { return height; }

	void decreaseHeight(int n) { height -= n; }

	~Building() = default;
};

class Street
	// Street holds the vector of buildings and has all the necessary methods for the alghoritm to work.
{
private:
	vector<Building> buildings;
public:
	Street()
	{
		std::cin >> *this;
	}

	Street(std::istream& is)
	{
		is >> *this;
	}

	Street(int n, vector<int>& heights)
	{
		for (int i = 0; i < n; ++i)
		{
			buildings.push_back(Building(heights[i]));
		}
	}

	Street(vector<Building> b)
		:buildings(b) {}

	Street(std::string filename)
	{
		try
		{
			std::ifstream Reader(filename);
			if (!Reader.good())
				throw std::runtime_error("Could not open file");
			int n;
			Reader >> n;
			int _;
			int height;
			for (int a = 0; a < n; a++)
			{
				Reader >> _ >> height;
				buildings.push_back(Building(height));
			}
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what();
			buildings.clear();
		}
	}

	Street(const Street& s)  // copy constr
	{
		buildings.clear();
		for (Building b : s.buildings)
		{
			buildings.push_back(b);
		}
	}

	vector<Building>& Buildings() noexcept { return buildings; };

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

	friend std::istream& operator>>(std::istream& i, Street& s);
};

std::istream& operator>>(std::istream& i, Street& s)
{
	int n;
	i >> n;
	int _;
	int height;
	s.Buildings().clear();
	for (int a = 0; a < n; a++)
	{
		i >> _ >> height;
		s.Buildings().push_back(Building(height));
	}
	return i;
}

int countPosters(Street s)
{
	static int posters = 0;
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

//int main()
//{
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(0);
//	Street s;
//	std::cout << countPosters(s);
//	return 0;
//}