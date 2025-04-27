#include "MultiSet.h"

void MultiSet::free()
{
	delete[] buckets;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	n = other.n;
	k = other.k;
	bucketsCount = other.bucketsCount;
	
	if (other.buckets == nullptr)
	{
		buckets = nullptr;
	}
	else
	{
		buckets = new char[strlen(other.buckets) + 1];
		strcpy(buckets, other.buckets);
	}
}

size_t MultiSet::calculateBuckets() const
{
	size_t size = (n + 1)* k;
	if (size % Constants::BITS != 0)
	{
		return size / Constants::BITS + 1;
	}
	else
	{
		return size / Constants::BITS;
	}
}

void MultiSet::printBits() const
{
	for (size_t i = 0; i < bucketsCount; i++)
	{
		size_t mask = 1;
		char bucket = buckets[i];
		for (size_t j = 0; j < Constants::BITS; j++)
		{
			std::cout << (bool)(bucket & mask) << " ";
			mask <<= 1;
		}
		std::cout << std::endl;
	}
}

void MultiSet::setElementCount(size_t num, size_t numCount)
{
	size_t currentNumber = 0;
	size_t bitsCount = (num + 1) * k;
	char oldBucket;
	char newBucket = 0;
	char prevBucket = 0;
	size_t currentBucketsCount = 0;

	for (size_t i = 0; i < bitsCount || i % Constants::BITS != 0; i++) //take the whole bucket
	{
		if (i % Constants::BITS == 0)
		{
			oldBucket = buckets[currentBucketsCount++];
			prevBucket = newBucket;
			newBucket = 0;

		}

		if (i % k == 0 && i != 0)
		{
			currentNumber++;
		}

		newBucket <<= 1;   //shift to save
		if (currentNumber == num)
		{
			newBucket = (numCount & 1) | newBucket;
			numCount >>= 1;
		}
		else
		{
			newBucket = (oldBucket & 1) | newBucket; 
			//save the rest information from the bucket
		}
		oldBucket >>= 1;  //shift to delete

	}

	buckets[currentBucketsCount - 1] = reverse(newBucket, Constants::BITS);

	if (currentBucketsCount > 1)
	{
		buckets[currentBucketsCount - 2] = reverse(prevBucket, Constants::BITS);
	}
}

size_t MultiSet::elementsCount(size_t num) const
{
	if (num > n)
	{
		throw std::exception("Out of scope");
	}

	size_t currentNumber = 0;
	size_t currentNumberCount = 0;
	size_t bitsCount = (num + 1) * k;
	char bucket;
	size_t currentBucketsCount = 0;

	for (size_t i = 0; i < bitsCount; i++)
	{
		if (i % Constants::BITS == 0)
		{
			bucket = buckets[currentBucketsCount++];
		}

		if (i % k == 0 && i != 0)
		{
			currentNumber++;
			currentNumberCount = 0;
		}
		currentNumberCount <<= 1;
		currentNumberCount = (bucket & 1) | currentNumberCount;
		bucket >>= 1;
	}

	return reverse(currentNumberCount, k);
}

void MultiSet::complement()
{ 
	for (size_t i = 0; i < bucketsCount; i++)
	{
		buckets[i] = ~buckets[i];
	}
}

void MultiSet::intersection(const MultiSet& other)
{
	size_t i = 0;
	for (i ; i <= n && i <= other.n; i++)
	{
		size_t otherCount = other.elementsCount(i);
		if (elementsCount(i) > otherCount)
		{
			setElementCount(i, otherCount);
		}
	}

	for (i; i <= n; i++)
	{
		setElementCount(i, 0);
	}
}

void MultiSet::difference(const MultiSet& other)
{
	for (size_t i = 0; i <= n && i <= other.n; i++)
	{
		int difference = elementsCount(i) - other.elementsCount(i);

		if (difference < 0)
		{
			setElementCount(i, 0);
		}

		else
		{
			setElementCount(i, difference);
		}
	}
}

void MultiSet::readFromFile(const char* filePath)
{
	free();
	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::exception("File not open!");
	}

	ifs.read((char*)&n, sizeof(size_t));
	ifs.read((char*)&k, sizeof(size_t));
	ifs.read((char*)&bucketsCount, sizeof(size_t));
	buckets = new char[bucketsCount];
	ifs.read((char*)buckets, sizeof(char) * bucketsCount);

	ifs.close();
}

void MultiSet::writeInFile(const char* filePath)
{
	std::ofstream ofs(filePath, std::ios::binary);

	if (!ofs.is_open())
	{
		throw std::exception("File not open!");
	}

	ofs.write((const char*)&n, sizeof(size_t));
	ofs.write((const char*)&k, sizeof(size_t));
	ofs.write((const char*)&bucketsCount, sizeof(size_t));
	ofs.write((const char*)buckets, sizeof(char) * bucketsCount);

	ofs.close();
}

MultiSet::MultiSet() : k(1), n(Constants::DEFAULT_SIZE)
{
	bucketsCount = calculateBuckets();
	buckets = new char[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++)
	{
		buckets[i] = 0;
	}
}

MultiSet::MultiSet(size_t n, size_t k)
{
	this->n = n;
	this->k = k;

	bucketsCount = calculateBuckets();
	buckets = new char[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++)
	{
		buckets[i] = 0;
	}
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::addElement(size_t num)
{
	bucketsCount = calculateBuckets();
	if (num > n)
	{
		throw std::exception("Number is out of scope!");
	}

	size_t currentNumberCount = elementsCount(num);
	size_t maxCount = (1 << k) - 1;

	if (currentNumberCount >= maxCount)
	{
		throw std::exception("Not enough space");
	}
	setElementCount(num, currentNumberCount + 1);

}

std::ostream& operator<<(std::ostream& os, const MultiSet& ref)
{
	os << "N: " << ref.n << std::endl;
	os << "K: " << ref.k << std::endl;
	os << "Multiset: ";

	for (size_t i = 0; i <= ref.n; i++)
	{
		size_t count = ref.elementsCount(i);
		for (size_t j = 0; j < count; j++)
		{
			os << i << " ";
		}
	}

	os << std::endl;
	return os;
}


char reverse(char bucket, size_t length)
{
	char result = 0;
	for (size_t i = 0; i < length; i++)
	{
		result <<= 1;
		result = (bucket & 1) | result;
		bucket >>= 1;
	}
	return result;
}
