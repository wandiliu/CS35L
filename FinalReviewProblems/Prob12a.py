#!/usr/bin/env python
import os 
import sys

class Point3:
    def __init__(self, x, y, z):
        self.x = x;
        self.y = y;
        self.z = z;    
    def distance2(self, p2):
        return (self.x - p2.x)**2 + (self.y - p2.y)**2 + (self.z - p2.z)**2


a = Point3(1,2,3)
b = Point3(1,2,4)
print (a.x,a.y,a.z)
print(a.distance2(b))

