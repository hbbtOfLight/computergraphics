#ifndef COLOR_STRUCTS_H
#define COLOR_STRUCTS_H
#include <cmath>

struct RGB;
struct XYZ;
struct CMYK;
struct RGB{
    int red, green, blue;
    RGB() = default;
    RGB(int r, int g, int b) : red(std::abs(r%256)), green(std::abs(g%256)), blue(std::abs(b%256)){}
    RGB(const XYZ& xyz);
    RGB(const CMYK& cmyk);
};
struct XYZ {
    double x, y, z;
    XYZ() = default;
    XYZ(int _x, int _y, int _z);
    XYZ(const RGB& rgb);
    XYZ(const CMYK& cmyk);

};
struct CMYK {
    double cyan, yellow, magenta, k;
    CMYK() = default;
    CMYK(const XYZ& xyz);
    CMYK(const RGB& rgb);
    CMYK(double c, double y, double m, double _k) : cyan(std::abs(int(c) % 101)), yellow(std::abs(int(y) % 101)), magenta(std::abs(int(m) % 101)), k(std::abs(int(_k) % 101)) {}
};

//void Convert(const RGB& rgb, const XYZ& xyz);
//void Convert(const RGB& rgb, const CMYK& cmyk);
//void Convert(const XYZ& xyz, const RGB& rgb);
//void Convert(const XYZ& xyz, const CMYK& cmyk);
//void Convert(const CMYK& cmyk, const XYZ& xyz);
//void Convert(const CMYK& cmyk, const RGB& rgb);




#endif // COLOR_STRUCTS_H
