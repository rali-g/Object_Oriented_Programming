#include <iostream>
#include <fstream>

struct Color {
    char name[8];
    int code;
};

void readColor(Color &color)
{
    std::cin.ignore();
    std::cin.getline(color.name, 8);
    std::cin >> color.code;
}

void writeInFile(std::ofstream& ofs, const Color* colors, int n)
{
    if (!ofs.is_open())
    {
        throw std::exception();
    }
    ofs.write((const char*)colors, sizeof(Color)*n);
    ofs.close();
}
int main() 
{
    int n = 0;
    std::cin >> n;
    Color* colors = new Color[n];

    for (int i = 0; i < n; i++)
    {
        Color temp;
        readColor(temp);
        colors[i] = temp;
    }
    std::ofstream ofs("color.txt", std::ios::binary);
    writeInFile(ofs, colors, n);

    Color* newColors = new Color[n];

    std::ifstream ifs("color.txt", std::ios::binary);
    
    delete[] colors;
    delete[] newColors;

}