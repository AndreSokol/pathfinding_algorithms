#ifndef MAP_H
#define MAP_H


class Map
{
public:
    Map();
    Map(const char*);

    bool GetMapFromXML(const char*);
private:
    int data;
};

#endif // MAP_H
