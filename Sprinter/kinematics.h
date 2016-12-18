/*
 Reprap heater funtions based on Sprinter
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>. */

/*
 This softwarepart for Heatercontrol is based on Sprinter
 big thanks to kliment (https://github.com/kliment/Sprinter)
 
*/


#include "Configuration.h"

typedef struct {double x; double y; double z;} comptable;

static comptable XYvZ[4] =
{
		{  0.0,  30.0, 0.0}, //3.0
    //{ 90.0,  30.0, 2.85},
    {160.0,  30.0, 0.0},
    
    //{  0.0,  100.0, 3.20},
    //{ 90.0,  100.0, 3.1},
    //{160.0,  100.0, 3.25},
		{  0.0, 200.0, 0.80 },
    //{  90.0,  200.0, 3.6},
		{160.0, 200.0, 0.80}
};

static double currentCompZ = 0.0;

double interpolate(double xin, double x1, double y1, double x2, double y2);
double getCompTableValue(comptable* table, double inputX, double inputY);
void applyCompensation(float *currPositions, float *nextPositions);





