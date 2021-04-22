#include <graphics.h>
#include <math.h>
#include <cstdio>

using namespace std;

float find_direction(float xpos, float ypos, float xtarget, float ytarget)
{
    float result, temp;
    xtarget -= xpos;
    ytarget -= ypos;

    temp = sqrt((xtarget * xtarget) + (ytarget * ytarget));
    if (xtarget >= 0 && ytarget >= 0 || xtarget >= 0 && ytarget < 0)
    {
        result = asin(ytarget / temp);
    }
    else if (xtarget >= 0 && ytarget >= 0 || xtarget < 0 && ytarget >= 0)
    {
        result = acos(xtarget / temp);
    }
    else if (xtarget < 0 && ytarget < 0)
    {
        xtarget *= -1;
        ytarget *= -1;
        result = asin(ytarget / temp);
        result += (180 / 180) * 3.141592653589793238;
    }
    result *= 180 / 3.141592653589793238;
    return result + 90;
}

void heavy_rotation(float xpos, float ypos, float x0, float y0, float *xrot, float *yrot, float angle)
{
    angle *= 3.141592653589793238 / 180;
    x0 -= xpos;
    y0 -= ypos;
    *xrot = (cos(angle) * x0) + (-1 * sin(angle) * y0) + xpos;
    *yrot = (sin(angle) * x0) + (cos(angle) * y0) + ypos;
}
void line_with_rotate(float xpos, float ypos, float x0, float y0, float x1, float y1, float angle)
{
    float xrot[2], yrot[2];
    heavy_rotation(xpos, ypos, x0, y0, &xrot[0], &yrot[0], angle);
    heavy_rotation(xpos, ypos, x1, y1, &xrot[1], &yrot[1], angle);
    line(xrot[0], yrot[0], xrot[1], yrot[1]);
}
void arc_with_rotate(float xpos, float ypos, float angle, float x0, float y0, float stangle, float endtangle, float radius)
{
    float xrot, yrot;
    heavy_rotation(xpos, ypos, x0, y0, &xrot, &yrot, angle);
    arc(xrot, yrot, stangle - angle, endtangle - angle, radius);
}
void circle_with_rotate(float xpos, float ypos, float x1, float y1, float angle, float size, float *xresult, float *yresult)
{
    float xrot, yrot;
    heavy_rotation(xpos, ypos, x1, y1, &xrot, &yrot, angle);
    circle(xrot, yrot, size);
    *xresult = xrot - xpos;
    *yresult = yrot - ypos;
}
void init_bullet(float xpos, float ypos, float rx, float yx, float angle)
{
    ellipse(xpos, ypos, 0, 0, rx, yx);
    // arc_with_rotate(100,100,90,200,200,)
    //arc_with_rotate(xpos, ypos, angle, x[1] * size + xpos, y[8] * size + ypos - size, 270, 360, size);
    // arc_with_rotate(100, 100, 90, 200, 200, 0, 90, 10);
}
void init_enemy(float xpos, float ypos, float size, float angle)
{
    float smaller_r = size * 5 / 8;
    angle += 180;
    circle(xpos, ypos, size);
    circle(xpos, ypos, smaller_r);
    line_with_rotate(xpos, ypos, xpos, ypos + smaller_r, xpos, ypos + smaller_r * 3, angle);
}
void init_tank(float xpos, float ypos, float size, float angle)
{
    int n = 20;
    //andwilinawd  0, 1, 2,  3,  4, 5, 6,  7,  8, 9, 10,11,  12,   13,14 ->st9
    float x[n] = {-3, 3, 3, -3, -2, 2, 2, -2, -4, 4, -4, 4, 0.5, -0.5};
    //laiwdidwaaw  0, 1,  2,  3, 4, 5, 6, 7, 8, 9, 10, 11,12, 13,14
    float y[n] = {5, 5, -5, -5, 4, 4, 2, 2, 6, 6, -6, -6, 8, -9, -3};

    for (int i = 0; i < 3; i++)
    {
        line_with_rotate(xpos, ypos, x[i] * size + xpos, y[i] * size + ypos, x[i + 1] * size + xpos, y[i + 1] * size + ypos, angle);
    }
    line_with_rotate(xpos, ypos, x[0] * size + xpos, y[0] * size + ypos, x[3] * size + xpos, y[3] * size + ypos, angle);
    //bates
    for (int i = 4; i < 7; i++)
    {
        line_with_rotate(xpos, ypos, x[i] * size + xpos, ypos - y[i] * size, x[i + 1] * size + xpos, ypos - y[i + 1] * size, angle);
    }
    line_with_rotate(xpos, ypos, x[4] * size + xpos, ypos - y[4] * size, x[7] * size + xpos, ypos - y[7] * size, angle);
    //bates
    line_with_rotate(xpos, ypos, x[0] * size + xpos, y[8] * size + ypos, x[1] * size + xpos, y[9] * size + ypos, angle);
    line_with_rotate(xpos, ypos, x[0] * size + xpos, y[10] * size + ypos, x[1] * size + xpos, y[11] * size + ypos, angle);
    line_with_rotate(xpos, ypos, x[8] * size + xpos, y[0] * size + ypos, x[8] * size + xpos, y[2] * size + ypos, angle);
    line_with_rotate(xpos, ypos, x[11] * size + xpos, y[0] * size + ypos, x[11] * size + xpos, y[2] * size + ypos, angle);
    //sudut..
    arc_with_rotate(xpos, ypos, angle, x[0] * size + xpos, y[10] * size + ypos + size, 90, 180, size);
    arc_with_rotate(xpos, ypos, angle, x[0] * size + xpos, y[8] * size + ypos - size, 180, 270, size);
    arc_with_rotate(xpos, ypos, angle, x[1] * size + xpos, y[10] * size + ypos + size, 0, 90, size);
    arc_with_rotate(xpos, ypos, angle, x[1] * size + xpos, y[8] * size + ypos - size, 270, 360, size);
    //tembak
    line_with_rotate(xpos, ypos, x[12] * size + xpos, y[13] * size + ypos, x[12] * size + xpos, y[14] * size + ypos, angle);
    line_with_rotate(xpos, ypos, x[13] * size + xpos, y[13] * size + ypos, x[13] * size + xpos, y[14] * size + ypos, angle);
    //circle(((x[12] + x[13]) / 2) * size + xpos, (y[13]) * size + ypos, size * x[12]);
}

void find_mouse_pos(int *x, int *y)
{
    *x = mousex();
    *y = mousey();
}

void linear_line(float x, float *y, float x0, float y0, float x1, float y1)
{
    *y = ((y1 - y0) * (x - x0) / (x1 - x0)) + y0;
}
void linear_line_invers(float *x, float y, float x0, float y0, float x1, float y1)
{
    *x = ((x1 - x0) * (y - y0) / (y1 - y0)) + x0;
}

float find_r(float x, float y)
{
    return sqrt(x * x + y * y);
    // return sqrt((xtar - x) * (xtar - x) + (ytar - y) * (ytar - y));
    // return sqrt((xtar - x) * (xtar - x) + (ytar - y) * (ytar - y) + 2 * (xtar - x) * (ytar - y) * cos((find_direction(x, y, xtar, ytar) - 90) * 3.141592653589793238 / 180));
}

int main()
{
    float xpos = 200, ypos = 200;
    float x = 200, y = 200;
    float xtes = 0, ytes = 400, angle = 90;
    int p = 201, q = 201;
    float xtar, ytar;
    float dxtank, dytank, rtank;
    float sizetank = 10;
    bool isfire = 0;

    float dxpeluru, dypeluru, rpeluru;
    float xpeluru = 400, ypeluru = 400;
    float xtarpeluru, ytarpeluru;

    float dxpeluruTank, dypeluruTank, rpeluruTank;
    float xpeluruTank = 400, ypeluruTank = 400;
    float xtarpeluruTank, ytarpeluruTank;
    float xawalpeluruTank, yawalpeluruTank;
    float anglepeluruTank;

    float dxbunker, dybunker, rbunker;
    float xbunker = 400, ybunker = 400;
    float xtarbunker, ytarbunker;
    float anglebunker = angle;
    float sizebunker = 20;
    float xpelurudaritank, ypelurudaritank;
    bool isdestroybunker = 0;

    float dxbunker2, dybunker2, rbunker2;
    float xbunker2 = 200, ybunker2 = 300;
    float xtarbunker2, ytarbunker2;
    float anglebunker2 = angle;
    float sizebunker2 = 20;
    float xpelurudaritank2, ypelurudaritank2;
    bool isdestroybunker2 = 0;

    initwindow(800, 800);

    // linear_line(5, &y, 0, 2, 10, 4);
    // printf("%f", y);

    // printf("%f", find_r(6, 8));

    while (!kbhit())
    {
        xpelurudaritank = xtarpeluruTank - xbunker;
        ypelurudaritank = ytarpeluruTank - ybunker;
        if (xpelurudaritank < 0)
            xpelurudaritank *= -1;
        if (ypelurudaritank < 0)
            ypelurudaritank *= -1;
        if (xpelurudaritank < sizebunker &&
            ypelurudaritank < sizebunker)
        {
            isdestroybunker = 1;
        }

        if (!isdestroybunker)
        {
            init_enemy(xbunker, ybunker, sizebunker, anglebunker);
            xtarbunker = xpos;
            ytarbunker = ypos;
            anglebunker = find_direction(xbunker, ybunker, xtarbunker, ytarbunker);
        }

        xpelurudaritank2 = xtarpeluruTank - xbunker2;
        ypelurudaritank2 = ytarpeluruTank - ybunker2;
        if (xpelurudaritank2 < 0)
            xpelurudaritank2 *= -1;
        if (ypelurudaritank2 < 0)
            ypelurudaritank2 *= -1;
        if (xpelurudaritank2 < sizebunker2 &&
            ypelurudaritank2 < sizebunker2)
        {
            isdestroybunker2 = 1;
        }
        if (!isdestroybunker2)
        {
            init_enemy(xbunker2, ybunker2, sizebunker2, anglebunker2);
            xtarbunker2 = xpos;
            ytarbunker2 = ypos;
            anglebunker2 = find_direction(xbunker2, ybunker2, xtarbunker2, ytarbunker2);
        }

        // // Untuk level 2
        // xtarpeluru = xpos;
        // ytarpeluru = ypos;
        // dxpeluru = xtarpeluru - xpeluru;
        // dypeluru = ytarpeluru - ypeluru;
        // rpeluru = find_r(dxpeluru, dypeluru);
        // dxpeluru /= rpeluru;
        // dypeluru /= rpeluru;
        // xpeluru += dxpeluru;
        // ypeluru += dypeluru;
        // circle(xpeluru, ypeluru, 20);

        // init_bullet(200, 200, 10, 5, angle);
        // printf("%d %d %f %f\n", p, q, xpos, ypos);
        // while (ismouseclick(WM_RBUTTONDOWN))
        // {
        //     init_tank(xpos, ypos, sizetank, angle);
        //     while (ismouseclick(WM_RBUTTONUP))
        //     {
        //         find_mouse_pos(&p, &q);
        //         angle = find_direction(xpos, ypos, p, q);
        //         // move_tank(xpos, ypos, p, q, sizetank, &angle, 0.5, &xpos, &ypos);
        //         clearmouseclick(WM_RBUTTONUP);
        //         clearmouseclick(WM_RBUTTONDOWN);
        //     }
        // }
        if (ismouseclick(WM_RBUTTONDOWN))
        {
            find_mouse_pos(&p, &q);
            angle = find_direction(xpos, ypos, p, q);
            // move_tank(xpos, ypos, p, q, sizetank, &angle, 0.5, &xpos, &ypos);
            clearmouseclick(WM_RBUTTONDOWN);
        }
        dxtank = p - xpos;
        dytank = q - ypos;
        rtank = find_r(dxtank, dytank);
        dxtank /= rtank;
        dytank /= rtank;
        xpos += dxtank * 5;
        ypos += dytank * 5;
        // printf("%d %d %f %f\n", p, q, xpos, ypos);
        if (p < xpos + sizetank && q < ypos + sizetank && p > xpos - sizetank && q > ypos - sizetank)
        {
            init_tank(p, q, sizetank, angle);
        }
        else
        {
            circle(p, q, sizetank);
            init_tank(xpos, ypos, sizetank, angle);
        }

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            if (ismouseclick(WM_LBUTTONUP))
            {
                isfire = 1;
                // dxpeluruTank = dxtank;
                // dypeluruTank = dytank;
                // xpeluruTank = xpos;
                // ypeluruTank = ypos;
                xawalpeluruTank = xpos;
                yawalpeluruTank = ypos;
                xpeluruTank = 0.5 * sizetank + xpos;
                ypeluruTank = -9 * sizetank + ypos;
                anglepeluruTank = angle;
                circle_with_rotate(xpos, ypos, xpeluruTank, ypeluruTank, angle, 10, &dxpeluruTank, &dypeluruTank);
                heavy_rotation(xawalpeluruTank, yawalpeluruTank, xpeluruTank, ypeluruTank, &xtarpeluruTank, &ytarpeluruTank, anglepeluruTank);
                clearmouseclick(WM_LBUTTONUP);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
        if (isfire)
        {
            // circle_with_rotate(xpeluruTank, ypeluruTank, xtarpeluruTank, ytarpeluruTank, angle, 10, &dxpeluruTank, &dypeluruTank);
            // circle(0.5 * sizetank + xpos, -9 * sizetank + ypos, 5);
            // xpeluruTank += dxpeluruTank / 5;
            // ypeluruTank += dypeluruTank / 5;
            // heavy_rotation(xawalpeluruTank, yawalpeluruTank, xpeluruTank, ypeluruTank, &xtarpeluruTank, &ytarpeluruTank, anglepeluruTank);
            // rpeluruTank = find_r(dxpeluruTank, dypeluruTank);
            // dxpeluruTank /= rpeluruTank;
            // dypeluruTank /= rpeluruTank;
            xtarpeluruTank += dxpeluruTank / 10;
            ytarpeluruTank += dypeluruTank / 10;
            circle(xtarpeluruTank, ytarpeluruTank, 10);
        }
        delay(20);
        cleardevice();
    }

    closegraph();
    return 0;
}