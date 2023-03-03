#include "color_structs.h"
#include <cmath>
#include <array>
#include <vector>
#include <qDebug>

double FXYZ_RGB(double x) {
    return x >= 0.0031308 ? 1.055 * std::pow(x, 1.0/2.4) - 0.055 : 12.92 * x;
}

double FRGB_XYZ(double x) {
    return x >= 0.04045 ? std::pow((x + 0.055) / 1.055, 2.4) : x / 12.95;
}

std::vector<double> Normalize(const RGB& rgb) {
    std::vector<double> normed(3);
    normed[0] = FRGB_XYZ(static_cast<double>(rgb.red) / 255) * 100;
    normed[1] = FRGB_XYZ(static_cast<double>(rgb.green) / 255) * 100;
    normed[2] = FRGB_XYZ(static_cast<double>(rgb.blue) / 255) * 100;
    qDebug() << "Normed: " << normed[0] << " " << normed[1] << " " << normed[2] << "\n";
    return normed;
}

std::vector<double> Normalize(const std::vector<double>& arr) {
    std::vector<double> ans(3);
    for (int i = 0; i < 3; ++i) {
        ans[i] = FXYZ_RGB(arr[i]);
    }
    return ans;
}

double Scalar(const std::vector<double>& to, const std::vector<double>& from) {
    return to[0] * from[0] + to[1] * from[1] + to [2] * from[2];
}

std::vector<double> MatMul(const std::vector<double> arr, const std::vector<std::vector<double>>& mat) {
    auto ans = arr;
    for (int i = 0; i < arr.size(); ++i) {
        ans[i] = Scalar(arr, mat[i]);
    }
    return ans;
}

RGB::RGB(const XYZ &xyz)
{
    std::vector<double> mine = {xyz.x/100.0, xyz.y/100.0, xyz.z/100.0};
    static const std::vector<std::vector<double>> matrix = {{3.2406, -1.5372, -0.4986},
                                                            {-0.9689, 1.8758, 0.0415},
                                                            {0.0557, -0.2040, 1.0570}};
    red = round(FXYZ_RGB(Scalar(matrix[0], mine)) * 255);
    green = round(FXYZ_RGB(Scalar(matrix[1], mine)) * 255);
    blue = round(FXYZ_RGB(Scalar(matrix[2], mine)) * 255);


}

RGB::RGB(const CMYK &cmyk)
{
red = 255 * (1 - cmyk.cyan / 100) * (1 - cmyk.k / 100);
green = 255 * (1 - cmyk.magenta / 100) * (1 - cmyk.k / 100);
blue = 255 * (1 - cmyk.yellow / 100) * (1 - cmyk.k / 100);
}

XYZ::XYZ(const RGB &rgb)
{
    auto normed = Normalize(rgb);
    static const std::vector<std::vector<double>> matrix = {{0.412453, 0.357580, 0.180423},
                                                            {0.212671, 0.715160, 0.072169},
                                                            {0.019334, 0.119193, 0.950227}};
    x = Scalar(matrix[0], normed);
    y = Scalar(matrix[1], normed);
    z = Scalar(matrix[2], normed);
//    x = FRGB_XYZ(Scalar(matrix[0], normed));
//    y = FRGB_XYZ(Scalar(matrix[1], normed));
//    z = FRGB_XYZ(Scalar(matrix[2], normed));

}

XYZ::XYZ(const CMYK &cmyk) : XYZ(RGB(cmyk))
{

}

XYZ::XYZ(int _x, int _y, int _z) : x(_x), y(_y), z(_z){
//    double sum = x + y + z;
//    if (std::abs(x / sum + y / sum + z / sum - 1) > 0.01) {
//        throw std::runtime_error("Wrong colors!");
//    }
}

CMYK::CMYK(const XYZ &xyz) : CMYK(RGB(xyz))
{

}

CMYK::CMYK(const RGB &rgb)
{
    double r = static_cast<double>(rgb.red), g = static_cast<double>(rgb.green), b = static_cast<double>(rgb.blue);
    k = std::min(std::min(1 - r / 255, 1 - g / 255), 1 - b/255);
    cyan = (1 - r/255 - k)/(1 - k) * 100;
    magenta = (1 - g/255 - k)/(1 - k) * 100;
    yellow = (1 - b/255 - k)/(1 - k) * 100;
    k *= 100;

}
