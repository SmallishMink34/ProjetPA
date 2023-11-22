#include "tree.hpp"


rooms::rooms(){
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->type = 0;
    this->tall = 0;
    this->value = "0";
}

rooms::rooms(int x, int y){
    this->x = x;
    this->y = y;
    this->w = 0;
    this->h = 0;
    this->type = 0;
    this->tall = 1;
    this->value = "0";
}

rooms::rooms(int x,int y,int w,int h,int type, int tall){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->type = type;
    this->tall = tall;
    this->value = '0';
}

void rooms::setTall(int tall){
    this->tall = tall;
}

void rooms::setType(int type){
    this->type = type;
}

int rooms::getX(){
    return this->x;
}

int rooms::getY(){
    return this->y;
}

int rooms::setX(int x){
    this->x = x;
}

int rooms::setY(int y){
    this->y = y;
}

std::vector<std::pair<int, int>> rooms::coordsarround(){
    std::vector<std::pair<int, int>> coords;
    if (getTall() == 2){
        coords.push_back(std::pair(getX()+1,getY()));
        coords.push_back(std::pair(getX()-1,getY()));
        coords.push_back(std::pair(getX()+1,getY()+1));
        coords.push_back(std::pair(getX()-1,getY()+1));
    }else{
        coords.push_back(std::pair(getX()+1,getY()));
        coords.push_back(std::pair(getX()-1,getY()+1));
    }

    return coords;
}

int rooms::getTall(){
    return this->tall;
}

int rooms::getType(){
    return this->type;
}

// |---------------------- NODE ----------------------|

Node::Node(){
    this->room = rooms();
    this->value = '0';
}

Node::Node(rooms room, char value){
    this->room = room;
    this->value = value;
}

std::vector<Node*> Node::getChildren(){
    return children;
}

char Node::getChildValue(int index){
    if(index >= 0 && index < children.size()){
        return children[index]->value;
    }
    return '\0'; // Return null character instead of nullptr
}


void Node::addChild(Node* child){
    this->children.push_back(child);
}


int Node::length(){
    return this->children.size();
}

rooms Node::getRoom(){
    return room;
}

char Node::getValue(){
    return value;
}