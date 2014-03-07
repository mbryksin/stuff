using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GeometryLib
{
    public class Geometry
    {
        /// <summary>
        /// Checks if point is placed within the line
        /// </summary>
        /// <returns><c>true</c>, if within, <c>false</c> otherwise.</returns>
        /// <param name="LinePoint1X">First line point X coordinate</param>
        /// <param name="LinePoint1Y">First line point Y coordinate</param>
        /// <param name="LinePoint2X">Second line point X coordinate</param>
        /// <param name="LinePoint2Y">Second line point Y coordinate</param>
        /// <param name="PointX">Point X coordinate</param>
        /// <param name="PointY">Point Y coordinate</param>
        public static bool PointOnLine(Int32 LinePoint1X, 
                                       Int32 LinePoint1Y,
                                       Int32 LinePoint2X, 
                                       Int32 LinePoint2Y, 
                                       Int32 PointX, 
                                       Int32 PointY)
        {

            if (LinePoint1X == LinePoint2X)
                return (LinePoint1X == PointX);
            Double k = Convert.ToDouble(LinePoint1Y - LinePoint2Y) / Convert.ToDouble(LinePoint1X - LinePoint2X);
            Double y = LinePoint2Y + (PointX - LinePoint2X) * k;
            return Convert.ToDouble(PointY) == y;
        }
    }
}
