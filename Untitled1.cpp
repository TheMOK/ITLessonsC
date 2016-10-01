// Хорман и Корстнелл

# include "TXLib.h"

int main ()
    {
    txCreateWindow (800, 600);
    return 0;
    }
class DrawObject {
    private:
    int x_, y_;
    public:
    DrawObject (int x1, int y1) :
        x_ (x1),
        y_ (y1)
        {}

    ~DrawObject () {}

    public:
    int getX ()
        {
        return x_;
        }

    public:
    int getY ()
        {
        return y_;
        }

    public:
    virtual void draw ();
};

class MovingDrawObject : public DrawObject
    {
    private: int dx_, dy_;

    public:
    MovingDrawObject (int x, int y, int dx1, int dy1) :
        DrawObject(x, y),
        dx_ (dx1),
        dy_ (dy1)
        {}

    public:
    int getDx ()
        {
        return dx_;
        }

    public:
    int getDy ()
        {
        return dy_;
        }

    public:
    virtual void draw ();

    public:
    virtual void moveItself ();
};

class Human
