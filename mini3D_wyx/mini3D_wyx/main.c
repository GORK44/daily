//
//  main.c
//  mini3D_wyx
//
//  Created by apple on 2019/7/22.
//===============================================
//  知乎 @韦易笑 的mini3d项目：https://github.com/skywind3000/mini3d
//  https://www.zhihu.com/question/33712299/answer/58495947
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//#include <windows.h>
//#include <tchar.h>

typedef unsigned int IUINT32;

//=====================================================================
// 数学库：此部分应该不用详解，熟悉 D3D 矩阵变换即可
//=====================================================================
typedef struct {float m[4][4];} matrix_t;           //矩阵
typedef struct { float x, y, z, w; } vector_t;      //矢量
typedef vector_t point_t;                           //点

//把 x 限定在 min 到 max 之间
int CMID(int x, int min, int max)
{return (x < min) ? min : ((x > max) ? max : x);}

//计算插值：t为【0，1】之间数值
float interp(float x1, float x2, float t)
{return x1 * (1 - t) + x2 * t;}

//  |v|     矢量的模
float vector_length(const vector_t *v){
    float sq = v->x * v->x + v->y * v->y + v->z * v->z;
    return (float)sqrt(sq);
}

// z = x + y       矢量相加
void vector_add(vector_t *z, const vector_t *x, const vector_t *y){
    z->x = x->x + y->x;
    z->y = x->y + y->y;
    z->z = x->z + y->z;
    z->w = 1.0;
}

// z = x - y        矢量相减
void vector_sub(vector_t *z, const vector_t *x, const vector_t *y){
    z->x = x->x - y->x;
    z->y = x->y - y->y;
    z->z = x->z - y->z;
    z->w = 1.0;
}

//矢量点乘
float vector_dotproduct(const vector_t *x, const vector_t *y){
    return x->x * y->x + x->y * y->y + x->z * y->z;
}

//矢量叉乘
void vector_crossproduct(vector_t *z, const vector_t *x, const vector_t *y){
    float m1, m2, m3;
    m1 = x->y * y->z - x->z * y->y;
    m2 = x->z * y->x - x->x * y->z;
    m3 = x->x * y->y - x->y * y->x;
    z->x = m1;
    z->y = m2;
    z->z = m3;
    z->w = 1.0f;
}

//矢量插值， t取值【0，1】
void vector_interp(vector_t *z, const vector_t *x1, const vector_t *x2, float t){
    z->x = interp(x1->x, x2->x, t);
    z->y = interp(x1->y, x2->y, t);
    z->z = interp(x1->z, x2->z, t);
    z->w = 1.0f;
}

//矢量归一化
void vector_normalize(vector_t *v){
    float length = vector_length(v);
    if(length != 0.0f){
        float inv = 1.0f / length;
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
    }
}

//c = a + b     矩阵相加
void matrix_add(matrix_t *c, const matrix_t *a, const matrix_t *b){
    int i ,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            c->m[i][j] = a->m[i][j] + b->m[i][j];
        }
    }
}

//c = a - b     矩阵相减
void matrix_sub(matrix_t *c, const matrix_t *a, const matrix_t *b){
    int i, j;
    for (i = 0; i<4; i++) {
        for (j=0; j<4; j++) {
            c->m[i][j] = a->m[i][j] - b->m[i][j];
        }
    }
}

//c = a * b     矩阵相乘
void matrix_mul(matrix_t *c, const matrix_t *a, const matrix_t *b){
    matrix_t z;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j<4; j++) {
            z.m[j][i] = (a->m[j][0] * b->m[0][i]) +
            (a->m[j][1] * b->m[1][i]) +
            (a->m[j][2] * b->m[2][i]) +
            (a->m[j][3] * b->m[3][i]);
        }
    }
    c[0] = z;
}

//c = a * f;    矩阵*数字
void matrix_scale(matrix_t *c, const matrix_t *a, float f){
    int i, j;
    for (i = 0; i<4; i++) {
        for (j = 0; j<4; j++) {
            c->m[i][j] = a->m[i][j] * f;
        }
    }
}

//y = x * m     矢量乘矩阵
void matrix_apply(vector_t *y, const vector_t *x, const matrix_t *m){
    float X = x->x, Y = x->y, Z = x->z, W = x->w;
    y->x = X * m->m[0][0] + Y * m->m[1][0] + Z * m->m[2][0] + W * m->m[3][0];
    y->y = X * m->m[0][1] + Y * m->m[1][1] + Z * m->m[2][1] + W * m->m[3][1];
    y->z = X * m->m[0][2] + Y * m->m[1][2] + Z * m->m[2][2] + W * m->m[3][2];
    y->w = X * m->m[0][3] + Y * m->m[1][3] + Z * m->m[2][3] + W * m->m[3][3];
}

// 单位矩阵
void matrix_set_identity(matrix_t *m){
    m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0f;
    m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
}

// 0 矩阵
void matrix_set_zero(matrix_t *m) {
    m->m[0][0] = m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][1] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][2] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = m->m[3][3] = 0.0f;
}

//平移矩阵
void matrix_set_translate(matrix_t *m, float x, float y, float z){
    matrix_set_identity(m);
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}

//缩放矩阵
void matrix_set_scale(matrix_t *m, float x, float y, float z){
    matrix_set_identity(m);
    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
}

//旋转矩阵
void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta){
    float qsin = (float)sin(theta * 0.5f);
    float qcos = (float)cos(theta * 0.5f);
    vector_t vec = { x, y, z, 1.0f };
    float w = qcos;
    vector_normalize(&vec);
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;
    m->m[0][0] = 1 - 2 * y * y - 2 * z * z;
    m->m[1][0] = 2 * x * y - 2 * w * z;
    m->m[2][0] = 2 * x * z + 2 * w * y;
    m->m[0][1] = 2 * x * y + 2 * w * z;
    m->m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m->m[2][1] = 2 * y * z - 2 * w * x;
    m->m[0][2] = 2 * x * z - 2 * w * y;
    m->m[1][2] = 2 * y * z + 2 * w * x;
    m->m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
}

//设置摄像机
void matrix_set_lookat(matrix_t *m, const vector_t *eye, const vector_t *at, const vector_t *up){
    vector_t xaxis, yaxis, zaxis;
    
    vector_sub(&zaxis, at, eye);                    // z轴 = at - eye
    vector_normalize(&zaxis);
    vector_crossproduct(&xaxis, up, &zaxis);        // x轴 = up X z轴
    vector_normalize(&xaxis);
    vector_crossproduct(&yaxis, &zaxis, &xaxis);    // y轴 = z轴 X x轴
    
    m->m[0][0] = xaxis.x;
    m->m[1][0] = xaxis.y;
    m->m[2][0] = xaxis.z;
    m->m[3][0] = -vector_dotproduct(&xaxis, eye);
    
    m->m[0][1] = yaxis.x;
    m->m[1][1] = yaxis.y;
    m->m[2][1] = yaxis.z;
    m->m[3][1] = -vector_dotproduct(&yaxis, eye);
    
    m->m[0][2] = zaxis.x;
    m->m[1][2] = zaxis.y;
    m->m[2][2] = zaxis.z;
    m->m[3][2] = -vector_dotproduct(&zaxis, eye);
    
    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][3] = 1.0f;
}

// 投影矩阵。把 x ，y 分别映射到【-z，z】，z从【n，f】映射到【0，z】。cvv规则观察体
void matrix_set_perspective(matrix_t *m, float fovy, float aspect, float zn, float zf){
    float fax = 1.0f / (float)tan(fovy * 0.5f);
    matrix_set_zero(m);
    m->m[0][0] = (float)(fax / aspect);//aspect = width / height
    m->m[1][1] = (float)(fax);
    m->m[2][2] = zf / (zf - zn);
    m->m[3][2] = - zn * zf / (zf - zn);
    m->m[2][3] = 1;
}


//=====================================================================
// 坐标变换
//=====================================================================
typedef struct{
    matrix_t world;             //世界坐标变换
    matrix_t view;              //摄像机坐标变换
    matrix_t projection;        //投影变换
    matrix_t transform;         //transform = world * view * projection
    float w, h;                 //屏幕大小
} transform_t;

//矩阵更新，transform = world * view * projection
void transform_update(transform_t *ts){
    matrix_t m;
    matrix_mul(&m, &ts->world, &ts->view);
    matrix_mul(&ts->transform, &m, &ts->projection);
}

//初始化，设置屏幕长宽
void transform_init(transform_t *ts, int width, int height){
    float aspect = (float)width/ ((float)height);
    matrix_set_identity(&ts->world);
    matrix_set_identity(&ts->view);
    matrix_set_perspective(&ts->projection, 3.1415926f * 0.5f, aspect, 1.0f, 500.0f);
    ts->w = (float)width;
    ts->h = (float)height;
    transform_update(ts);
}

//将矢量 x 进行 project（投影）
void transform_apply(const transform_t *ts, vector_t *y, const vector_t *x) {
    matrix_apply(y, x, &ts->transform);
}

//检查齐次坐标同 cvv 的边界用于视锥裁剪
int transform_check_cvv(const vector_t *v) {
    float w = v->w;
    int check = 0;
    if (v->z < 0.0f) check |= 1;
    if (v->z <  w) check |= 2;
    if (v->x < -w) check |= 4;
    if (v->x >  w) check |= 8;
    if (v->y < -w) check |= 16;
    if (v->y >  w) check |= 32;
    return check;
}

//映射到屏幕坐标
void transform_homogenize(const transform_t *ts, vector_t *y, const vector_t *x) {
    float rhw = 1.0f / x->w;                        // rhw = 1/z
    y->x = (x->x * rhw + 1.0f) * ts->w * 0.5f;      // x 的范围从【-z，z】映射到 【0，w】
    y->y = (1.0f - x->y * rhw) * ts->h * 0.5f;      // y 轴向下
    y->z = x->z * rhw;                              // z 的范围从【0，z】映射到 【0，1】
    y->w = 1.0f;
}

//========================================
//几何计算：顶点，扫描线，边缘，矩形，步长计算
//========================================
typedef struct{ float r, g, b; } color_t;       //颜色
typedef struct{ float u, v; } texcoord_t;       //纹理
typedef struct{ point_t pos; texcoord_t tc; color_t color; float rhw; } vertex_t;   //顶点

typedef struct{ vertex_t v, v1, v2; } edge_t;       //v1 , v2 为边的两端点，v 为边上一点
typedef struct{ float top, bottom; edge_t left, right;} trapezoid_t;    //梯形
typedef struct{ vertex_t v, step; int x, y, w; } scanline_t;   //扫描线，v ：起点; step ：步长（x变化1，其他量变化多少）; w ：长度（右x - 左x）

//初始化w（透视矫正）
void vertex_rhw_init(vertex_t *v) {
    float rhw = 1.0f / v->pos.w;
    v->rhw = rhw;
    v->tc.u *= rhw;
    v->tc.v *= rhw;
    v->color.r *= rhw;
    v->color.g *= rhw;
    v->color.b *= rhw;
}

//顶点插值
void vertex_interp(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float t) {
    vector_interp(&y->pos, &x1->pos, &x2->pos, t);
    y->tc.u = interp(x1->tc.u, x2->tc.u, t);
    y->tc.v = interp(x1->tc.v, x2->tc.v, t);
    y->color.r = interp(x1->color.r, x2->color.r, t);
    y->color.g = interp(x1->color.g, x2->color.g, t);
    y->color.b = interp(x1->color.b, x2->color.b, t);
    y->rhw = interp(x1->rhw, x2->rhw, t);
}

//顶点之差。w = x2->pos.x - x1->pos.x ， 相当于 x 变化 1 个单位后，其他量变化多少
void vertex_division(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float w) {
    float inv = 1.0 / w;
    y->pos.x = (x2->pos.x - x1->pos.x) * inv;
    y->pos.y = (x2->pos.y - x1->pos.y) * inv;
    y->pos.z = (x2->pos.z - x1->pos.z) * inv;
    y->pos.w = (x2->pos.w - x1->pos.w) * inv;
    y->tc.u = (x2->tc.u - x1->tc.u) * inv;
    y->tc.v = (x2->tc.v - x1->tc.v) * inv;
    y->color.r = (x2->color.r - x1->color.r) * inv;
    y->color.g = (x2->color.g - x1->color.g) * inv;
    y->color.b = (x2->color.g - x1->color.b) * inv;
    y->rhw = (x2->rhw - x1->rhw) * inv;
}

//顶点相加
void vertex_add(vertex_t *y, const vertex_t *x) {
    y->pos.x += x->pos.x;
    y->pos.y += x->pos.y;
    y->pos.z += x->pos.z;
    y->pos.w += x->pos.w;
    y->rhw += x->rhw;
    y->tc.u += x->tc.u;
    y->tc.v += x->tc.v;
    y->color.r += x->color.r;
    y->color.g += x->color.g;
    y->color.b += x->color.b;
}

//根据三角形生成 0-2 个梯形，并且返回合法梯形的数量
int trapezpoid_init_triangle(trapezoid_t *trap, const vertex_t *p1, const vertex_t *p2, const vertex_t *p3) {
    const vertex_t *p;
    float k, x;
    
    // p1, p2, p3 从小到大（从上到下）（注意：y轴向下）
    if(p1->pos.y > p2->pos.y) p = p1, p1 = p2, p2 = p;
    if(p1->pos.y > p3->pos.y) p = p1, p1 = p3, p3 = p;
    if(p2->pos.y > p3->pos.y) p = p2, p2 = p3, p3 = p;
    if(p1->pos.y == p2->pos.y && p1->pos.y == p3->pos.y) return 0;//p1,p2,p3在一直线上
    if(p1->pos.x == p2->pos.x && p1->pos.x == p3->pos.x) return 0;//p1,p2,p3在一直线上
    
    if (p1->pos.y == p2->pos.y) {    // p1, p2 纵坐标相等，底朝上的三角形（注意：y轴向下）
        if (p1->pos.x > p2->pos.x) p = p1, p1 = p2, p2 = p;
        trap[0].top = p1->pos.y;
        trap[0].bottom = p3->pos.y;
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p3;
        trap[0].right.v1 = *p2;
        trap[0].right.v2 = *p3;
        return (trap[0].top < trap[0].bottom)? 1 : 0;
    }
    
    if (p2->pos.y == p3->pos.y) {    // p2, p3 纵坐标相等，底朝下的三角形（注意：y轴向下）
        if (p2->pos.x > p3->pos.x) p = p2, p2 = p3, p3 = p;
        trap[0].top = p1->pos.y;
        trap[0].bottom = p3->pos.y;
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p2;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p3;
        return (trap[0].top < trap[0].bottom)? 1 : 0;
    }
    
    //将一个三角形分割成上下两个三角形
    trap[0].top = p1->pos.y;
    trap[0].bottom = p2->pos.y;
    trap[1].top = p2->pos.y;
    trap[1].bottom = p3->pos.y;
    
    k = (p3->pos.y - p1->pos.y) / (p2->pos.y - p1->pos.y);
    x = p1->pos.x + (p2->pos.x - p1->pos.x) * k;
    
    if (x <= p3->pos.x) {        // triangle left
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p2;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p3;
        trap[1].left.v1 = *p2;
        trap[1].left.v2 = *p3;
        trap[1].right.v1 = *p1;
        trap[1].right.v2 = *p3;
    }    else {                    // triangle right
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p3;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p2;
        trap[1].left.v1 = *p1;
        trap[1].left.v2 = *p3;
        trap[1].right.v1 = *p2;
        trap[1].right.v2 = *p3;
    }
    
    return 2;
}

//按照 Y 坐标计算出左右两条边纵坐标等于 Y 的顶点（顶点的uv，rgb，1/z插值）（参数y已经+0.5，像素中心）
void trapezoid_edge_interp(trapezoid_t *trap, float y){
    float s1 = trap->left.v2.pos.y - trap->left.v1.pos.y;
    float s2 = trap->right.v2.pos.y - trap->right.v1.pos.y;
    float t1 = (y - trap->left.v1.pos.y) / s1;
    float t2 = (y - trap->right.v1.pos.y) / s2;
    vertex_interp(&trap->left.v, &trap->left.v1, &trap->left.v2, t1);
    vertex_interp(&trap->right.v, &trap->right.v1, &trap->right.v2, t2);
}

//根据左右两边的端点，初始化计算出扫描线的起点和步长（直线基于整数域，一个一个像素buffer）
void trapezoid_init_scan_line(const trapezoid_t *trap, scanline_t *scanline, int y){
    float width = trap->right.v.pos.x - trap->left.v.pos.x;         //长度
    scanline->x = (int)(trap->left.v.pos.x + 0.5f);                 //起点横坐标（buffer）
    scanline->w = (int)(trap->right.v.pos.x + 0.5f) - scanline->x;  //长度（buffer）
    scanline->y = y;                                                //起点纵坐标（buffer）
    scanline->v = trap->left.v;                                     //起点（包含颜色，uv）
    if (trap->left.v.pos.x >= trap->right.v.pos.x) scanline->w = 0;
    vertex_division(&scanline->step, &trap->left.v, &trap->right.v, width);//（x+1后其他参数的变化）
}



//=====================================================================
// 渲染设备
//=====================================================================
typedef struct{
    transform_t transform;                  //坐标变换器
    int width;                              //窗口宽度
    int height;                             //窗口高度
    IUINT32 **framebuffer;                  //像素缓存：framebuffer[y] 代表第 y 行
    float **zbuffer;                        //深度缓存：zbuffer[y] 为f第 y行指针
    IUINT32 **texture;                      //纹理：同样是每行索引
    int tex_width;                          //纹理宽度
    int tex_height;                         //纹理高度
    float max_u;                            //纹理最大宽度：tex_width - 1
    float max_v;                            //纹理最大高度：tex_height - 1
    int render_state;                       //渲染状态
    IUINT32 background;                     //背景颜色
    IUINT32 foreground;                     //线框颜色
} device_t;

#define RENDER_STATE_WIREFRAME      1       //渲染线框
#define RENDER_STATE_TEXTURE        2       //渲染纹理
#define RENDER_STATE_COLOR          4       //渲染颜色

//设备初始化，fb为外部帧缓存，非 NULL 将引用外部帧缓存（每行 4字节对齐）
void device_init(device_t *device, int width, int height, void *fb) {
    int need = sizeof(void*) * (height * 2 + 1024) + width * height * 8;//framebuffer + zbuffer + texture + framebuf + zbuf
    char *ptr = (char*)malloc(need + 64);
    char *framebuf, *zbuf;
    int j;
    assert(ptr);//assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。
    
    device->framebuffer = (IUINT32**)ptr;//sizeof(void*) * height
    
    device->zbuffer = (float**)(ptr + sizeof(void*) * height);//sizeof(void*) * height
    ptr += sizeof(void*) * height * 2;
    
    device->texture = (IUINT32**)ptr;//sizeof(void*) * 1024
    ptr += sizeof(void*) * 1024;
    
    framebuf = (char*)ptr;//width * height * 4
    
    zbuf = (char*)ptr + width * height * 4;//width * height * 4
    ptr += width * height * 8;
    
    if(fb != NULL) framebuf = (char*)fb;
    for (j = 0; j < height; j++) {
        device->framebuffer[j] = (IUINT32*)(framebuf + width * 4 * j);
        device->zbuffer[j] = (float*)(zbuf + width * 4 * j);
    }
    
    device->texture[0] = (IUINT32*)ptr;
    device->texture[1] = (IUINT32*)(ptr + 16);
    memset(device->texture[0], 0, 64);//memset() 函数用来将指定内存(device->texture[0]所指的内存区域)的前n(64)个字节设置为特定的值(0)
    device->tex_width = 2;
    device->tex_height = 2;
    device->max_u = 1.0f;
    device->max_v = 1.0f;
    device->width = width;
    device->height = height;
    device->background = 0xc0c0c0;
    device->foreground = 0;
    transform_init(&device->transform, width, height);
    device->render_state = RENDER_STATE_WIREFRAME;
    
}

//删除设备
void device_destory(device_t *device) {
    if(device->framebuffer)
        free(device->framebuffer);
    device->framebuffer = NULL;
    device->zbuffer = NULL;
    device->texture = NULL;
}

//设置当前纹理
void device_set_texture(device_t *device, void *bits, long pitch, int w, int h) {
    char *ptr = (char*)bits;
    int j;
    assert(w <= 1024 && h <= 1024);
    for (j = 0; j < h; ptr += pitch, j++) {         //pitch = 宽度 * 4（字节）
        device->texture[j] = (IUINT32*)ptr;
    }
    device->tex_width = w;
    device->tex_height = h;
    device->max_u = (float)(w-1);
    device->max_v = (float)(h-1);
}


//清空 framebuffer 和 zbuffer
void device_clear(device_t *device, int mode) {
    int y, x, height = device->height;
    for(y = 0; y < device->height; y++) {
        IUINT32 *dst = device->framebuffer[y];
        IUINT32 cc = (height - 1 - y) * 230 / (height - 1);
        cc = (cc << 16) | (cc << 8) | cc;//左移两个字节，一个字节，二进制或计算(rgb)
        if (mode == 0) cc = device->background;
        for (x = device->width; x > 0; dst++, x--) {
            dst[0] = cc;
        }
    }
    for (y = 0; y < device->height; y++) {
        float *dst = device->zbuffer[y];
        for (x = device->width; x > 0; dst++, x--) {
            dst[0] = 0.0f;
        }
    }
}

//画点
void device_pixel(device_t *device, int x, int y, IUINT32 color) {
    if (((IUINT32)x) < (IUINT32)device->width && ((IUINT32)y) < (IUINT32)device->height) {
        device->framebuffer[y][x] = color;
    }
}

//绘制线段
void device_draw_line(device_t *device, int x1, int y1, int x2, int y2, IUINT32 c) {
    int x, y, rem = 0;
    if (x1 == x2 && y1 == y2) {             //两点重合
        device_pixel(device, x1, y1, c);
    }   else if (x1 == x2) {                //两端点横坐标相等
        int inc = (y1 <= y2) ? 1 : -1;
        for (y = y1; y != y2; y += inc) device_pixel(device, x1, y, c);
        device_pixel(device, x2, y2, c);
    }   else if (y1 == y2) {                //两端点纵坐标相等
        int inc = (x1 <= x2) ? 1 : -1;
        for (x = x1; x != x2; x += inc) device_pixel(device, x, y1, c);
        device_pixel(device, x2, y2, c);
    }   else {                              //两个横纵坐标不等的端点
        int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
        int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
        if (dx >= dy) {                         //斜率小于 1
            if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y; //使 x1 < x2
            for (x = x1, y = y1; x <= x2; x++) {
                device_pixel(device, x, y, c);          //横向绘制像素点
                rem += dy;
                if (rem >= dx) {                        //dy累加 >= dx
                    rem -= dx;
                    y += (y2 >= y1) ? 1 : -1;
                    device_pixel(device, x, y, c);      //纵向绘制像素点
                }
            }
            device_pixel(device, x2, y2, c);            //终点
        }   else {                             //斜率大于 1
            if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
            for (x = x1, y = y1; y <= y2; y++) {
                device_pixel(device, x, y, c);          //纵向绘制像素点
                rem += dx;
                if (rem >= dy) {                        //dx累加 >= dy
                    rem -= dy;
                    x += (x2 >= x1) ? 1 : -1;
                    device_pixel(device, x, y, c);      //横向绘制像素点
                }
            }
            device_pixel(device, x2, y2, c);            //终点
        }
    }
}

// 根据坐标读取纹理
IUINT32 device_texture_read(const device_t *device, float u, float v) {
    int x, y;
    u = u * device->max_u;
    v = v * device->max_v;
    x = (int)(u + 0.5f);            //四舍五入到整数域（纹素）
    y = (int)(v + 0.5f);
    x = CMID(x, 0, device->tex_width - 1);  //范围限定
    y = CMID(y, 0, device->tex_height - 1);
    return device->texture[y][x];
}


//=====================================================================
// 渲染实现
//=====================================================================

//绘制扫描线（片元着色器放在这）
void device_draw_scanline(device_t *device, scanline_t *scanline) {
    IUINT32 *framebuffer = device->framebuffer[scanline->y];
    float *zbuffer = device->zbuffer[scanline->y];
    int x = scanline->x;        //扫描线起点
    int w = scanline->w;        //扫描线长度
    int width = device->width;  //窗口宽度
    int render_state = device->render_state;
    for ( ; w > 0; x++, w--) {
        if (x >= 0 && x < width) {
            float rhw = scanline->v.rhw; //rhw = 1/z（相机空间z）
            if (rhw >= zbuffer[x]) {   // 1/z 比较，z 较小的保存
                float w = 1.0f / rhw;  // w = z
                zbuffer[x] = rhw;      // 1/z 缓存
                if (render_state & RENDER_STATE_COLOR) {
                    float r = scanline->v.color.r * w;      //之前 * 1/z 线性插值，现在乘回来
                    float g = scanline->v.color.g * w;
                    float b = scanline->v.color.b * w;
                    int R = (int)(r * 255.0f);
                    int G = (int)(g * 255.0f);
                    int B = (int)(b * 255.0f);
                    R = CMID(R, 0, 255);
                    G = CMID(G, 0, 255);
                    B = CMID(B, 0, 255);
                    framebuffer[x] = (R << 16) | (G << 8) | (B);    //保存当前像素颜色
                }
                if (render_state & RENDER_STATE_TEXTURE) {
                    float u = scanline->v.tc.u * w;
                    float v = scanline->v.tc.v * w;
                    IUINT32 cc = device_texture_read(device, u, v);     //读取对应uv坐标纹理颜色
                    framebuffer[x] = cc;                                //保存当前像素颜色
                }
            }
        }
        vertex_add(&scanline->v, &scanline->step);
        if (x >= width) break;
    }
}

//主渲染函数
void device_render_trap(device_t *device, trapezoid_t *trap) {
    scanline_t scanline;
    int j, top, bottom;
    top = (int)(trap->top + 0.5f);          //四舍五入到整数域
    bottom = (int)(trap->bottom + 0.5f);
    for (j = top; j < bottom; j++) {
        if (j >= 0 && j < device->height) {
            
            trapezoid_edge_interp(trap, (float)j + 0.5f);
            //计算出左右两条边纵坐标等于 j + 0.5 的顶点（像素中心）
            //顶点的u/w，v/w，rgb/w，1/w 关于屏幕坐标 做线性插值（w为相机空间z）
            
            trapezoid_init_scan_line(trap, &scanline, j);
            //根据左右两边的端点，初始化计算出扫描线的起点和步长(x+1后其他参数的变换）
            //直线基于整数域（把屏幕坐标 转换到 像素buffer）
            
            device_draw_scanline(device, &scanline);//绘制扫描线
        }
        if (j >= device->height) break;
    }
}

//根据 render_state 绘制三角形 （primitive 图元）（顶点着色器放在这）
void device_draw_primitive(device_t *device, const vertex_t *v1,const vertex_t *v2, const vertex_t *v3) {
    point_t p1, p2, p3, c1, c2, c3;
    int render_state = device->render_state;
    
    //按照 Transform 变化（world * view * projection）
    transform_apply(&device->transform, &c1, &v1->pos);     //将 v1点坐标 变换成 c1（转换到cvv规则观察体内）
    transform_apply(&device->transform, &c2, &v2->pos);
    transform_apply(&device->transform, &c3, &v2->pos);
    
    //裁剪，注意此处可以完善为具体判断几个点在cvv内以及同cvv相交平面的坐标比例
    //进行进一步精细裁剪，将一个分解为几个完全处在cvv内的三角形
    if (transform_check_cvv(&c1) != 0) return;
    if (transform_check_cvv(&c2) != 0) return;
    if (transform_check_cvv(&c3) != 0) return;
    
    //归一化，把 c1 映射到屏幕上 p1
    transform_homogenize(&device->transform, &p1, &c1);     // p1 为屏幕坐标
    transform_homogenize(&device->transform, &p2, &c2);
    transform_homogenize(&device->transform, &p3, &c3);
    
    //纹理或色彩绘制
    if (render_state & (RENDER_STATE_TEXTURE | RENDER_STATE_COLOR)) {
        vertex_t t1 = *v1, t2 = *v2, t3 = *v3;
        trapezoid_t traps[2];
        int n;
        
        t1.pos = p1;                // t1 为屏幕坐标
        t2.pos = p2;
        t3.pos = p3;
        t1.pos.w = c1.w;            // w 保存的是相机空间中的 z
        t2.pos.w = c2.w;
        t3.pos.w = c3.w;
        
        vertex_rhw_init(&t1);       //初始化顶点，uv和rgb 先除以w，之后再插值
        vertex_rhw_init(&t2);
        vertex_rhw_init(&t3);
        
        //拆分三角形为0-2个三角形，并返回可用三角形数量
        n = trapezpoid_init_triangle(traps, &t1, &t2, &t3);
        
        if (n >= 1) device_render_trap(device, &traps[0]);      //填充三角形（主渲染函数）
        if (n >= 2) device_render_trap(device, &traps[1]);
    }
    
    if (render_state & RENDER_STATE_WIREFRAME) {        //线框绘制
        device_draw_line(device, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, device->foreground);
        device_draw_line(device, (int)p1.x, (int)p1.y, (int)p3.x, (int)p3.y, device->foreground);
        device_draw_line(device, (int)p3.x, (int)p3.y, (int)p2.x, (int)p2.y, device->foreground);
    }
}


































int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
