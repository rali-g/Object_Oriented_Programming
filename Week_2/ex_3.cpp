#include <iostream>
#include <fstream>

struct Pair 
{
	int x;
	int y;
};

Pair createPair(int x, int y)
{
	Pair p;
	p.x = x;
	p.y = y;
	return p;
}

void initPair(Pair& toInit, int x, int y) 
{
	toInit.x = x;
	toInit.y = y;
}

Pair readPairFromFile(std::ifstream& inFile)
{
	if (!inFile.is_open())
	{
		throw std::exception();
	}
	Pair p;
	inFile >> p.x >> p.y;
	return p;
}

void writePairToFile(std::ofstream& outFile, const Pair& toWrite)
{
	if (!outFile.is_open())
	{
		throw std::exception();
	}
	outFile << toWrite.x << std::endl << toWrite.y << std::endl;
}

const int MAX_SIZE = 25;
struct Relation {
	Pair pairs[MAX_SIZE];
	int size = 0;
};

bool addPair(Relation& arg, Pair& toInsert)
{
	if (MAX_SIZE - 1 <= arg.size)
	{
		return false;
	}
	arg.pairs[arg.size++] = toInsert;
	return true;
}

void writeRelation(const Relation& arg, const char* filePath)
{
	std::ofstream ofs(filePath, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception();
	}
	ofs.write((const char*)(&arg), sizeof(Relation));
	ofs.close();
}

void readRelation(Relation& arg, const char* filepath)
{
	std::ifstream ifs(filepath, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::exception();
	}
	ifs.read((char*)&arg, sizeof(Relation));
	ifs.close();
}
int main()
{
	Relation pairs;
	Pair p1;
	p1.x = 3;
	p1.y = 5;
	Pair p2;
	p2.x = 6;
	p2.y = 8;
	Pair p3;
	p3.x = 9;
	p3.y = 1;
	addPair(pairs, p1);
	addPair(pairs, p2);
	addPair(pairs, p3);
	writeRelation(pairs, "result");
	Relation newRelation;
	readRelation(newRelation, "result");
	std::cout << newRelation.pairs[newRelation.size - 1].x;
}