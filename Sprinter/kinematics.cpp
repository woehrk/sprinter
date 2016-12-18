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

/* interpolate - basic linear interpolate
 * inputs = xin, table inputs
 * outputs = yout
 */

#include "kinematics.h"

double interpolate(double xin, double x1, double y1, double x2, double y2)
{
	double yout = y1;
	if(x2-x1 > 0.001 || x1-x2 > 0.001)
	{
		yout = y1 + (y2-y1)*(xin-x1)/(x2-x1);
	}
	return yout;
}


/*
 * A**************B
 * ****************
 * ***********P****
 * ****************
 * ****************
 * ****************
 * C**************D
 *
 * Interpolate A-B=ab, fixed X position
 * Interpolate C-D=cd, fixed X position
 * Interpolate ab-cd
 */
double getCompTableValue(comptable *table, double inputX, double inputY)
{
	int ii;
	double ab, cd = 0.0;
	bool first = false;
	double y1, y2 = 0.0;
  
	for(ii = 0; ii < 4; ii++)
	{
		if(table[ii].x <= inputX && table[ii+1].x >= inputX) //first time
		{
			if(!first)
			{
				ab = interpolate(inputX, table[ii].x, table[ii].z, table[ii+1].x, table[ii+1].z);
				y1 = table[ii].y;
				first = true;
			}
			else
			{
				cd = interpolate(inputX, table[ii].x, table[ii].z, table[ii+1].x, table[ii+1].z);
				y2 = table[ii].y;
			}
		}
	}
 if(!first)
 {
  return 0.0;
 }
 return interpolate(inputY, y1, ab, y2, cd);
}

void applyCompensation(float *currPositions, float *nextPositions)
{
	double Zcomp = getCompTableValue(XYvZ, (double)nextPositions[0], (double)nextPositions[1]);
  Zcomp -= currentCompZ;

  currentCompZ += Zcomp;
  nextPositions[2] += Zcomp;
}
