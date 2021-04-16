#include <graphics.h>
#include <math.h>
#include <cstdio>

using namespace std;

void init_bullet(float xpos, float ypos, float rx, float yx)
{
    ellipse(xpos, ypos, 0, 360, rx, yx);
}

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
void init_tank(float xpos, float ypos, float size, float angle)
{
    int n = 20;
    //andwilinawd a// 0, 1, 2,  3,  4, 5, 6,  7,  8, 9, 10,11,12,13,14 ->st9
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
void move_tank(float xpos, float ypos, float xtarget, float ytarget, float size, float *angle, float delay_ms, float *x_result, float *y_result)
{
    float temp_angle = *angle;
    float xtemp = xtarget - xpos, ytemp = ytarget - ypos;
    int p = xtarget, q = ytarget;
    float xpass = *x_result, ypass = *y_result;
    if (xtemp < 0)
        xtemp *= -1;
    if (ytemp < 0)
        ytemp *= -1;
    if (xpos == xtarget && ytarget >= ypos)
    {
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = ypos; i < ytarget; i++)
        {
            init_tank(xpos, i, size, *angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos == xtarget && ytarget <= ypos)
    {
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = ypos; i > ytarget; i--)
        {
            init_tank(xpos, i, size, *angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (ypos == ytarget && xtarget >= xpos)
    {
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = xpos; i < xtarget; i++)
        {
            init_tank(i, ypos, size, *angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (ypos == ytarget && xtarget <= xpos)
    {
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = xpos; i > xtarget; i--)
        {
            init_tank(i, ypos, size, *angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos != xtarget && ypos >= ytarget && ytemp >= xtemp)
    {
        clearmouseclick(WM_RBUTTONDOWN);
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = ypos, y; i > ytarget; i--)
        {
            init_tank(y, i, size, temp_angle);
            circle(xtarget, ytarget, 10);
            xpass = xtarget;
            ypass = ytarget;
            if (ismouseclick(WM_RBUTTONDOWN))
            {
                while (1)
                {
                    if (ismouseclick(WM_RBUTTONUP))
                    {
                        find_mouse_pos(&p, &q);
                        xpass = p;
                        ypass = q;
                        move_tank(y, i, p, q, 10, &temp_angle, delay_ms, &xpass, &ypass);
                        // linear_line_invers(&y, i, xpos, ypos, xtarget, ytarget);
                        // init_tank(y, i, size, temp_angle);
                        clearmouseclick(WM_RBUTTONUP);
                        break;
                    }
                }
                clearmouseclick(WM_RBUTTONDOWN);
                break;
            }
            linear_line_invers(&y, i, xpos, ypos, xtarget, ytarget);
            init_tank(y, i, size, temp_angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos != xtarget && ypos <= ytarget && ytemp >= xtemp)
    {
        clearmouseclick(WM_RBUTTONDOWN);
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = ypos, y; i < ytarget; i++)
        {
            init_tank(y, i, size, temp_angle);
            circle(xtarget, ytarget, 10);
            xpass = xtarget;
            ypass = ytarget;
            if (ismouseclick(WM_RBUTTONDOWN))
            {
                while (1)
                {
                    if (ismouseclick(WM_RBUTTONUP))
                    {
                        find_mouse_pos(&p, &q);
                        xpass = p;
                        ypass = q;
                        move_tank(y, i, p, q, 10, &temp_angle, delay_ms, &xpass, &ypass);
                        // linear_line_invers(&y, i, xpos, ypos, xtarget, ytarget);
                        // init_tank(y, i, size, temp_angle);
                        clearmouseclick(WM_RBUTTONUP);
                        break;
                    }
                }
                clearmouseclick(WM_RBUTTONDOWN);
                break;
            }
            linear_line_invers(&y, i, xpos, ypos, xtarget, ytarget);
            init_tank(y, i, size, temp_angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos >= xtarget && ypos != ytarget && ytemp <= xtemp)
    {
        clearmouseclick(WM_RBUTTONDOWN);
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = xpos, y; i > xtarget; i--)
        {
            init_tank(i, y, size, temp_angle);
            circle(xtarget, ytarget, 10);
            xpass = xtarget;
            ypass = ytarget;
            if (ismouseclick(WM_RBUTTONDOWN))
            {
                while (1)
                {
                    if (ismouseclick(WM_RBUTTONUP))
                    {
                        find_mouse_pos(&p, &q);
                        xpass = p;
                        ypass = q;
                        move_tank(i, y, p, q, 10, &temp_angle, delay_ms, &xpass, &ypass);
                        // linear_line(i, &y, xpos, ypos, xtarget, ytarget);
                        // init_tank(i, y, size, temp_angle);
                        clearmouseclick(WM_RBUTTONUP);
                        break;
                    }
                }
                clearmouseclick(WM_RBUTTONDOWN);
                break;
            }
            linear_line(i, &y, xpos, ypos, xtarget, ytarget);
            init_tank(i, y, size, temp_angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos <= xtarget && ypos != ytarget && ytemp <= xtemp)
    {
        clearmouseclick(WM_RBUTTONDOWN);
        temp_angle = find_direction(xpos, ypos, xtarget, ytarget);
        for (float i = xpos, y; i < xtarget; i++)
        {
            init_tank(i, y, size, temp_angle);
            circle(xtarget, ytarget, 10);
            xpass = xtarget;
            ypass = ytarget;
            if (ismouseclick(WM_RBUTTONDOWN))
            {
                while (1)
                {
                    if (ismouseclick(WM_RBUTTONUP))
                    {
                        find_mouse_pos(&p, &q);
                        xpass = p;
                        ypass = q;
                        move_tank(i, y, p, q, 10, &temp_angle, delay_ms, &xpass, &ypass);
                        // linear_line(i, &y, xpos, ypos, xtarget, ytarget);
                        // init_tank(i, y, size, temp_angle);
                        clearmouseclick(WM_RBUTTONUP);
                        break;
                    }
                }
                clearmouseclick(WM_RBUTTONDOWN);
                break;
            }
            linear_line(i, &y, xpos, ypos, xtarget, ytarget);
            init_tank(i, y, size, temp_angle);
            delay(delay_ms);
            cleardevice();
        }
    }
    // init_tank(xtarget, ytarget, size, temp_angle);
    *x_result = xpass;
    *y_result = ypass;
    *angle = temp_angle;
}
void move_bullet(float xpos, float ypos, float xtarget, float ytarget, float size, float delay_ms, float *x_result, float *y_result)
{
    cleardevice();
    float xtemp = xtarget - xpos, ytemp = ytarget - ypos;
    int p = xtarget, q = ytarget;
    float xpass = *x_result, ypass = *y_result;
    if (xtemp < 0)
        xtemp *= -1;
    if (ytemp < 0)
        ytemp *= -1;
    if (xpos == xtarget && ytarget >= ypos)
    {
        for (float i = ypos; i < ytarget; i++)
        {
            circle(xpos, i, size);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (xpos == xtarget && ytarget <= ypos)
    {
        for (float i = ypos; i > ytarget; i--)
        {
            circle(xpos, i, size);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (ypos == ytarget && xtarget >= xpos)
    {
        for (float i = xpos; i < xtarget; i++)
        {
            circle(i, ypos, size);
            delay(delay_ms);
            cleardevice();
        }
    }
    else if (ypos == ytarget && xtarget <= xpos)
    {
        for (float i = xpos; i > xtarget; i--)
        {
            circle(i, ypos, size);
            delay(delay_ms);
            cleardevice();
        }
    }
}

// int main()
// {
//     float xpos = 200, ypos = 200;
//     float x = 200, y = 200;
//     float xtes = 0, ytes = 400, angle = 90;
//     int p = 100, q = 100;
//     initwindow(800, 800);

//     // linear_line(5, &y, 0, 2, 10, 4);
//     // printf("%f", y);

//     while (!kbhit())
//     {
//         while (ismouseclick(WM_RBUTTONDOWN))
//         {
//             init_tank(xpos, ypos, 10, angle);
//             while (ismouseclick(WM_RBUTTONUP))
//             {
//                 find_mouse_pos(&p, &q);
//                 move_tank(xpos, ypos, p, q, 10, &angle, 0.5, &xpos, &ypos);
//                 clearmouseclick(WM_RBUTTONUP);
//                 clearmouseclick(WM_RBUTTONDOWN);
//             }
//         }
//         init_tank(xpos, ypos, 10, angle);
//         delay(20);
//         cleardevice();
//     }

//     closegraph();
//     return 0;
// }