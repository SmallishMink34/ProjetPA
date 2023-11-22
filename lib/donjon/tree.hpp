#ifndef defTree
#define defTree
#include <iostream>
#include <tuple>
#include <vector>

class rooms{
    private:
        int x;
        int y;
        int w;
        int h;
        int type;
        int tall;
        std::string value;
    
    public:
        rooms();
        rooms(int x, int y);
        rooms(int x,int y,int w,int h,int type, int tall);
        void setTall(int tall);
        void setType(int type);
        int getX();
        int getY();
        int getTall();
        int getType();
        int setX(int x);
        int setY(int y);

        std::vector<std::pair<int, int>> rooms::coordsarround();
};

class Node{
    public:
        Node();
        Node(rooms room, char value);
        std::vector<Node*> getChildren();
        char getChildValue(int index);
        void addChild(Node *child);
        int length();
        rooms getRoom();
        char getValue();

    private:
        rooms room;
        char value;
        std::vector<Node*> children;
};
#endif