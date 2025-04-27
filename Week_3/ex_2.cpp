#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)

struct Color {
    char name[8];
    int code;
};

size_t colorsInFile(const char* filePath)
{
    std::ifstream ifs(filePath, std::ios::binary);
    if (!filePath || !ifs.is_open())
    {
        throw std::exception();
    }
    ifs.seekg(0, std::ios::end);
    int size = ifs.tellg();
    ifs.close();
    return (size / sizeof(Color));
}

Color findColorByName(const char* name, const char* filePath)
{
    std::ifstream ifs(filePath, std::ios::binary);
    if (!filePath || !ifs.is_open())
    {
        throw std::exception();
    }
    int size = colorsInFile(filePath);
    Color* colors = new Color[size];
    ifs.read((char*)colors, sizeof(Color) * size);
    ifs.close();
    Color result;
    result.code = -1;
    strcpy(result.name, "Error");

    for (int i = 0; i < size; i++)
    {
        if (strcmp(colors[i].name, name) == 0)
        {
            result = colors[i];
            break;
        }
    }
    delete[] colors;
    return result;
}

int main()
{
    Color result;
    result = findColorByName("peis", "color.txt");
    std::cout << result.name;
}