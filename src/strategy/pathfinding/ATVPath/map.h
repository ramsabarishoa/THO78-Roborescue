#ifndef MAP_H
#define MAP_H

#include <vector>
#include "mapitem.h"

class Map
{
public:
   Map();

   void addItem(const MapItem &mi);
   void clear();

   bool isColliding(const MapItem & mi) const;

private:
   std::vector<MapItem> items;
};

#endif // MAP_H
