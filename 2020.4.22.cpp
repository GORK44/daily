//
//  main.cpp
//  Ray Tracing
//
//  Created by apple on 2019/9/9.
//  Copyright © 2019 apple. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <string>
using namespace std;

#define PI 3.1415926
double rand_back(double i,double j)
{
    double u1=double(rand()%1000)/1000,u2=double(rand()%1000)/1000,r;
    
    static unsigned int seed=0;
    
    r=i+sqrt(j)*sqrt(-2.0*(log(u1)/log(exp(1.0))))*cos(2*PI*u2);
    
    return r;
}


void WriteNoise(const string fileName)
{
    ofstream ouTT;   //流名称
    
    const string folder = "/书/Ray Tracing in weekend/";
    const string name = folder + fileName;
    
//    ouTT.open("/书/Ray Tracing in weekend/z1024.ppm");  //流写入位置
    
    ouTT.open(name);  //流写入位置

    
    int nx = 512;
    int ny = 512;
    ouTT << "P3\n" << nx << " " << ny << "\n255\n";
    
    int aa = 0;
    
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            
            
            int r = (rand_back(0, 1)+3) / 6 * 255;
            while (r < 0 || r > 255)    r = (rand_back(0, 1)+3) / 6 * 255;
            
            int g = (rand_back(0, 1)+3) / 6 * 255;
            while (g < 0 || g > 255)    g = (rand_back(0, 1)+3) / 6 * 255;
            
            int b = (rand_back(0, 1)+3) / 6 * 255;
            while (b < 0 || b > 255)    b = (rand_back(0, 1)+3) / 6 * 255;
            
            
            ouTT << r << " " << g << " " << b << "\n";    //流输出内容，用法和COUT一样
            
            if(g >255/6*5)
                aa++;
            //                std::cout<< ran << " " << ran << " " << ran << "\n";
            
        }
    }
    
    std::cout<< aa << "\n";
    
    
    ouTT.close();
}


int main(int argc, const char * argv[]) {
//
//
    
    WriteNoise("noise1.ppm");
    WriteNoise("noise2.ppm");
    WriteNoise("noise3.ppm");
    
    
    
    
    
//    ofstream ouTT;   //流名称
//    ouTT.open("/书/Ray Tracing in weekend/z1024.ppm");  //流写入位置
//
////    ouTT<<"A C E"<<endl;  //流输出内容，用法和COUT一样
//
//    int nx = 100;
//    int ny = 100;
//    ouTT << "P3\n" << nx << " " << ny << "\n255\n";
//
//    int aa = 0;
//
//    for (int j = ny-1; j >= 0; j--) {
//        for (int i = 0; i < nx; i++) {
//
//
//            int r = (rand_back(0, 1)+3) / 6 * 255;
//            while (r < 0 || r > 255)    r = (rand_back(0, 1)+3) / 6 * 255;
//
//            int g = (rand_back(0, 1)+3) / 6 * 255;
//            while (g < 0 || g > 255)    g = (rand_back(0, 1)+3) / 6 * 255;
//
//            int b = (rand_back(0, 1)+3) / 6 * 255;
//            while (b < 0 || b > 255)    b = (rand_back(0, 1)+3) / 6 * 255;
//
//
//            ouTT << r << " " << g << " " << b << "\n";    //流输出内容，用法和COUT一样
//
//            if(g >255/6*5)
//                aa++;
////                std::cout<< ran << " " << ran << " " << ran << "\n";
//
//        }
//    }
//
//    std::cout<< aa << "\n";
//
//
//    ouTT.close();

}






//#include <iostream>
//#include <fstream>
//using namespace std;
//
//int main(int argc, const char * argv[]) {
//
//    ofstream ouTT;   //流名称
//
//    ouTT.open("/file/noise1000.ppm");  //流写入位置
//    int nx = 1000;
//    int ny = 1000;
//
////    ouTT.open("/file/noise5000.ppm");
////    int nx = 5000;
////    int ny = 5000;
//
//    ouTT << "P3\n" << nx << " " << ny << "\n255\n";
//
//    for (int j = ny-1; j >= 0; j--) {
//        for (int i = 0; i < nx; i++) {
//            float ran = random()%256;
//            ouTT << ran << " " << ran << " " << ran << "\n";
//        }
//    }
//
//    ouTT.close();
//}
