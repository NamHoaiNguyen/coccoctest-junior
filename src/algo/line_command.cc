#include "line_command.h"
#include "algo.h"
#include <cmath>
#include "math.h"

using namespace std;

void Line::handle(const Data& data) {
    setUpParams(data);
    execute();
}

void Line::setUpParams(const Data& data) {
    LineAxis axis;

    axis.x = std::stoi(data.axis.first);
    axis.y = std::stoi(data.axis.second);
    /*Care!!! Maybe segmant fault when adding reference to vector*/
    this->_historyLine.push_back(axis);
    // this->_result.push_back(axis);
}

void Line::addAlgo(std::weak_ptr<Algo> algo) {
    this->_algo = algo;
}

void Line::execute() {
    /*
    Get the current position
    This position can come from axis from MOVE_TO or LINE_TO command.
    */
    Data prevData;

    if (auto subscriber = this->_algo.lock(); subscriber) {
        prevData = subscriber->getPrevData();
    }

    // std::cout << prevData.command << " " << prevData.axis.first << " " << prevData.axis.second << " " << __FILE__ << " " << __func__ << std::endl;

    int prevAxis_x = std::stoi(prevData.axis.first);
    int prevAxis_y = std::stoi(prevData.axis.second);

    // midPoint(prevAxis_x, prevAxis_y, _historyLine.back().x, _historyLine.back().y);
    DDALine(prevAxis_x, prevAxis_y, _historyLine.back().x, _historyLine.back().y);
    checkResult();
}


int Line::roundt(float n)
{
    if (n - (int)n < 0.5)
        return (int)n;
    return (int)(n + 1);
}
 
// Function for line generation
void Line::DDALine(int x0, int y0, int x1, int y1)
{
 
    // Calculate dx and dy
    int dx = x1 - x0;
    int dy = y1 - y0;
 
    int step;
 
    // If dx > dy we will take step as dx
    // else we will take step as dy to draw the complete
    // line
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
 
    // Calculate x-increment and y-increment for each step
    float x_incr = (float)dx / step;
    float y_incr = (float)dy / step;
 
    // Take the initial points as x and y
    float x = x0;
    float y = y0;
 
    for (int i = 0; i < step + 1; i++) {
 
        // cout << roundt(x) << " " << roundt(y) << "\n";
        LineAxis axis;
        axis.x = roundt(x);
        axis.y = roundt(y);
        _result.push_back(axis);
        x += x_incr;
        y += y_incr;
    }
}

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy, Po;
    int k = 0;
    dx = (x2 - x1);
    dy = (y2 - y1);
    if(dy <= dx && dy > 0) {
        dx = abs(dx);
        dy = abs(dy);
        Po = (2 * dy) - dx;
        cout << "(" << x1 << " " << y1 << ")" << endl;
        int xk = x1;
        int yk = y1;
        for(k = x1; k < x2; k++) { 
            if(Po < 0) {	
                cout << "(" << ++xk << " " << yk << ")" << endl;
                Po = Po + (2 * dy);
            } else {
                cout << "(" << ++xk << " " << ++yk << ")" << endl;
                Po = Po + (2 * dy) - (2 * dx);
            }
        }
    }
    else if(dy > dx && dy > 0) {
        dx = abs(dx);
        dy = abs(dy);
        Po = (2 * dx) - dy;
        cout << "(" << x1 << " " << y1 << ")" << endl;

        int xk = x1; int yk = y1;
        for(k = y1; k < y2; k++) { 
            if(Po < 0) {	
                cout << "(" << xk << " " << ++yk << ")" << endl;

                Po = Po + (2 * dx);
            } else {
                cout << "(" << ++xk << " " << ++yk << ")" << endl;

                Po = Po + (2 * dx) - (2 * dy);
            }
        }			
    }
    else if(dy >= -dx)
    {
        dx = abs(dx);
        dy = abs(dy);
        Po = (2 * dy) - dx;
        cout << "(" << x1 << " " << y1 << ")" << endl;

        int xk = x1;
        int yk = y1;
        for(k = x1; k < x2; k++) { 
            if(Po < 0) {	
                cout << "(" << ++xk << " " << yk << ")" << endl;

                Po = Po + (2 * dy);
            } else{
                cout << "(" << ++xk << " " << --yk << ")" << endl;

                Po = Po + (2 * dy) - (2 * dx);
            }
        }
    }
    else if(dy < -dx) {
        dx = abs(dx);
        dy = abs(dy);
        Po = (2 * dy) - dx;
        cout << "(" << x1 << " " << y1 << ")" << endl;

        int xk = x1;
        int yk = y1;
        for(k = y1; k > y2; k--) { 
            if(Po < 0) {	
                cout << "(" << xk << " " << --yk << ")" << endl;

                Po = Po + (2 * dx);
            }
            else{
                cout << "(" << ++xk << " " << --yk << ")" << endl;

                Po = Po + (2 * dx) - (2 * dy);
            }
        }
    }
}

void Line::midPoint(int X1, int Y1, int X2, int Y2)
{
    // calculate dx & dy
   
    LineAxis axis;

    if (X1 == X2) {
        if (Y1 < Y2) {
            axis.x = X1;
            axis.y = Y1;
            _result.push_back(axis);
            while (Y1 < Y2) {
                Y1++;
                axis.x = X1;
                axis.y = Y1;
                _result.push_back(axis);
            }
        }
        if (Y2 < Y1) {
            axis.x = X1;
            axis.y = Y2;
            _result.push_back(axis);
            while (Y2 < Y1) {
                Y2++;
                axis.x = X1;
                axis.y = Y2;
                _result.push_back(axis);
            }
        }
        return;
    }

    if (Y1 == Y2) {
        if (X1 < X2) {
            axis.x = X1;
            axis.y = Y1;
            _result.push_back(axis);
            while (X1 < X2) {
                X1++;
                axis.x = X1;
                axis.y = Y1;
                _result.push_back(axis);
            }
        }
        if (X2 < X1) {
            axis.x = X2;
            axis.y = Y1;
            _result.push_back(axis);
            while (X2 < X1) {
                X2++;
                axis.x = X2;
                axis.y = Y1;
                _result.push_back(axis);
            }
        }
        return;
    }

    double s,c, angle;
        std::cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << std::endl;

    if (X1 < X2 && Y1 > Y2) {
        c = cos(180 *3.14/180);  
        s = sin(180 *3.14/180);  
        X1 = floor(X1 * c + Y1 * s);  
        Y1 = floor(-X1 * s + Y1 * c);  
        X2 = floor(X2 * c + Y2 * s);  
        Y2 = floor(-X2 * s + Y2 * c);
    
        std::cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << std::endl;
        return;
    }

    //     while(std::abs(Y1 - Y2) != 0) {
    //         axis.x = X1;

    //         if (Y1 < Y2) {
    //             axis.y = Y1;
    //             Y1++;
    //         } 

    //         if (Y1 > Y2) {
    //             axis.y = Y1;
    //             Y1--;
    //         } 
    //         _result.push_back(axis);
    //     }
    //     return;
    // }

    // if (Y1 == Y2) {
    //     while(std::abs(X1 - X2) != 0) {
    //         axis.y = Y1;

    //         if (X1 < X2) {
    //             axis.x = X1;
    //             X1++;
    //         } 

    //         if (X1 > X2) {
    //             axis.x = X1;
    //             X1--;
    //         } 
    //         _result.push_back(axis);
    //     }
    //     return;
    // }

    /*swap*/
    if (X1 > X2 && Y1 > Y2) {
        int x_temp = X1;
        int y_temp = Y1;
        X1 = X2;
        X2 = x_temp;
        Y1 = Y2;
        Y2 = y_temp;
    }

    int dx = X2 - X1;
    int dy = Y2 - Y1;
   
    if (dy <= dx){
        // initial value of decision parameter d
        int d = dy - (dx / 2);
        int x = X1, y = Y1;
    
        // Plot initial given point
        // putpixel(x,y) can be used to print pixel
        // of line in graphics
        // cout << x << "," << y << "\n";
        
        LineAxis axis;
        axis.x = x;
        axis.y = y;

        _result.push_back(axis);
    
        // iterate through value of X
        while (x < X2)
        {
            x++;
    
            // E or East is chosen
            if (d < 0)
                d = d + dy;
    
            // NE or North East is chosen
            else
            {
                d += (dy - dx);
                y++;
            }
    
            // Plot intermediate points
            // putpixel(x,y) is used to print pixel
            // of line in graphics
            // cout << x << "," << y << "\n";
            axis.x = x;
            axis.y = y;
            _result.push_back(axis);
        }
    }
   
    else if(dx < dy)
    {
        // initial value of decision parameter d
        int d = dx - (dy/2);
        int x = X1, y = Y1;

        // Plot initial given point
        // putpixel(x,y) can be used to print pixel
        // of line in graphics
        // cout << x << "," << y << "\n";

        LineAxis axis;
        axis.x = x;
        axis.y = y;

        _result.push_back(axis);

        // iterate through value of X
        while (y < Y2)
        {
            y++;

            // E or East is chosen
            if (d < 0)
                d = d + dx;

            // NE or North East is chosen
            // NE or North East is chosen
            else
            {
                d += (dx - dy);
                x++;
            }

            // Plot intermediate points
            // putpixel(x,y) is used to print pixel
            // of line in graphics
            // cout << x << "," << y << "\n";
            axis.x = x;
            axis.y = y;
            _result.push_back(axis);
        }
    }
}

void Line::checkResult() {
    std::cout << "Check result after executing each line command" << std::endl;

    for (const auto& elem : _result) {
        std::cout << elem.x << " " << elem.y << std::endl;
    }
}