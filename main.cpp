// #include "tes.cpp"
// #include <future>
// #include <thread>
// using namespace std;

// class bullet
// {
// private:
//     float xpos, ypos, size, speed;
//     float rx, ry;
//     int kindd;

// public:
//     bullet(float x, float y, float speed_ms, int kind)
//     {
//         xpos = x;
//         ypos = y;
//         speed = speed_ms;
//         kindd = kind;
//     }
//     void make_rad()
//     {
//         if (kindd == 1)
//         {
//             rx = 2;
//             ry = 10;
//         }
//         else if (kindd == 2)
//         {
//             rx = 5;
//             ry = 25;
//         }
//         else if (kindd == 3)
//         {
//             rx = 10;
//             ry = 50;
//         }
//     }
//     void draw_bullet()
//     {
//         make_rad();
//         init_bullet(xpos, ypos, rx, ry);
//     }
// };

// class circle_bullet
// {
// private:
//     float xpos, ypos, size, xh, yh;

// public:
//     bool ismove = 0;
//     circle_bullet(float x, float y, float sz)
//     {
//         xpos = x;
//         ypos = y;
//         size = sz;
//         circle(x, y, sz);
//     }
//     void move()
//     {
//         std::thread t1(move_bullet, xpos, ypos, 200, 200, size, 3, &xpos, &ypos);
//         // move_bullet(xpos, ypos, 200, 200, size, 3, &xpos, &ypos);
//         t1.detach();
//     }
// };

// class main_char
// {
// private:
//     float xpos, ypos, health, size, angle, speed = 0.5;
//     int xh, yh;
//     bool ismove = 0;

// public:
//     main_char(float x, float y, float hp, float sz, float ang)
//     {
//         xpos = x;
//         ypos = y;
//         health = hp;
//         size = sz;
//         angle = ang;
//         init_tank(x, y, sz, ang);
//     }
//     void get_pos(float *x, float *y)
//     {
//         *x = xpos;
//         *y = ypos;
//     }
//     void move_tank_by_mouse()
//     {
//         ismove = 1;
//         find_mouse_pos(&xh, &yh);
//         move_tank(xpos, ypos, xh, yh, size, &angle, speed, &xpos, &ypos);
//     }
//     void infinity_init()
//     {
//         if (!ismove)
//         {
//             std::thread t100(init_tank, xpos, ypos, size, angle);
//             t100.detach();
//         }
//     }
//     float get_x_pos()
//     {
//         return xpos;
//     }
//     float get_y_pos()
//     {
//         return ypos;
//     }
//     float get_size_tank()
//     {
//         return size;
//     }
//     float get_angle_tank()
//     {
//         return angle;
//     }
// };

// main()
// {
//     int x = 30, y = 30, xbenda = 150, ybenda = 150, size = 20, HP = 100;
//     bool klik;

//     initwindow(400, 400);

//     main_char tank(100, 100, 100, 10, 0);
//     bullet bullet1(200, 200, 0.5, 1);
//     bullet bullet2(250, 250, 0.5, 2);
//     bullet bullet3(300, 300, 0.5, 3);
//     circle_bullet bullet11(200, 20, 10);
//     while (!kbhit())
//     {

//         while (ismouseclick(WM_RBUTTONDOWN))
//         {
//             init_tank(tank.get_x_pos(), tank.get_y_pos(), tank.get_size_tank(), tank.get_angle_tank());
//             while (ismouseclick(WM_RBUTTONUP))
//             {
//                 tank.move_tank_by_mouse();
//                 clearmouseclick(WM_RBUTTONUP);
//                 clearmouseclick(WM_RBUTTONDOWN);
//             }
//         }
//         tank.infinity_init();
//         // init_tank(tank.get_x_pos(), tank.get_y_pos(), tank.get_size_tank(), tank.get_angle_tank());
//         // bullet11.move();

//         // ellipse(200, 200, 0, 360, 2, 10);
//         // bullet1.draw_bullet();
//         // bullet2.draw_bullet();
//         // bullet3.draw_bullet();
//         delay(20);
//         cleardevice();
//     }

//     return 0;
// }
