#include "line_command.h"
#include "algo.h"

using namespace std;

void Line::handle(const Data& data) {
    // std::cout << "line handle in algo folder" << std::endl;
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



    std::cout << prevData.command << " " << prevData.axis.first << " " << prevData.axis.second << " " << __FILE__ << " " << __func__ << std::endl;

    int prevAxis_x = std::stoi(prevData.axis.first);
    int prevAxis_y = std::stoi(prevData.axis.second);

    midPoint(prevAxis_x, prevAxis_y, _historyLine.back().x, _historyLine.back().y);
}

void Line::midPoint(int X1, int Y1, int X2, int Y2)
{
    // calculate dx & dy
   
    int dx = X2 - X1;
    int dy = Y2 - Y1;
   
    if(dy<=dx){
    // initial value of decision parameter d
    int d = dy - (dx/2);
    int x = X1, y = Y1;
 
    // Plot initial given point
    // putpixel(x,y) can be used to print pixel
    // of line in graphics
    cout << x << "," << y << "\n";
 
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
        cout << x << "," << y << "\n";
    }
    }
   
  else if(dx<dy)
  {
    // initial value of decision parameter d
    int d = dx - (dy/2);
    int x = X1, y = Y1;
 
    // Plot initial given point
    // putpixel(x,y) can be used to print pixel
    // of line in graphics
    cout << x << "," << y << "\n";
 
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
        cout << x << "," << y << "\n";
    }
  }
}