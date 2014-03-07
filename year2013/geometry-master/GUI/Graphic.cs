using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GeometryLib;

namespace GUI
{
    public partial class Graphic : Form
    {
        Int32 xMax;
        Int32 xMin;
        Int32 yMax;
        Int32 yMin;
        Point A;
        Point M;
        Point N;
        Pen pen;
        SolidBrush brush;
        Graphics g;

        public Graphic()
        {
            InitializeComponent();
        }

        private void Graphic_Load(object sender, EventArgs e)
        {
            xMax = splitContainer1.Panel1.Width - 15;
            xMin = 10;
            yMax = splitContainer1.Panel1.Height - 15;
            yMin = 10;
            A = new Point(0, 0);
            M = new Point(0, 0);
            N = new Point(0, 0);

            g = Graphics.FromHwnd(splitContainer1.Panel1.Handle);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            pen = new Pen(Color.Black, 2);
            brush = new SolidBrush(System.Drawing.Color.Red);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Random rand = new Random();
            Int32 x = (xMax - xMin) / 2;
            Int32 y = (yMax - yMin) / 2;

            A = new Point(rand.Next(x - 5, x + 5), rand.Next(y - 5, y + 5));
            do {
                M = new Point(rand.Next(x - 5, x + 5), rand.Next(y - 5, y + 5));
                N = new Point(rand.Next(x - 5, x + 5), rand.Next(y - 5, y + 5));
            } while ((M.X == N.X) && (M.Y == N.Y));

            splitContainer1_Panel1_Paint(this, null);
            listViewRefresh();
            showSolution();
        }

        private void listViewRefresh()
        {
            String pointM = "(" + Convert.ToString(M.X) + "," + Convert.ToString(M.Y) + ")";
            String pointN = "(" + Convert.ToString(N.X) + "," + Convert.ToString(N.Y) + ")";
            String pointA = "(" + Convert.ToString(A.X) + "," + Convert.ToString(A.Y) + ")";
            listView1.Items[0].SubItems[1].Text = pointM;
            listView1.Items[1].SubItems[1].Text = pointN;
            listView1.Items[2].SubItems[1].Text = pointA;
        }

        private void showSolution()
        {
            bool solution = Geometry.PointOnLine(M.X, M.Y, N.X, N.Y, A.X, A.Y);
            if (solution)
                label1.Text = "Принадлежит";
            else
                label1.Text = "Не принадлежит";
        }

        private Point normalize(Point X)
        {
            Point Y = new Point(X.X, yMax - X.Y);
            return Y;
        }

        private Double f (int x)
        {
            Int32 kx = M.X - N.X;
            Int32 ky = M.Y - N.Y;
            Double k = Convert.ToDouble(ky) / Convert.ToDouble(kx);
            return N.Y + (x - N.X) * k;
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
            g.Clear(Color.White);

            if ((A == M) && (M == N))
                return;

            Point M2 = normalize(M);
            Point N2 = normalize(N);
            Point A2 = normalize(A);

            if (M2.X == N2.X)
            {
                g.DrawLine(pen, new Point(M2.X, yMin), new Point(M2.X, yMax));
            }
            else
            {
                for (int i = xMin; i <= xMax; i++)
                {
                    Double yd = yMax - f(i);
                    if ((yd >= yMin) && (yd <= yMax))
                        M2 = new Point(i, Convert.ToInt32(Math.Round(yd)));
                }

                for (int i = xMax; i >= xMin; i--)
                {
                    Double yd = yMax - f(i);
                    if ((yd <= yMax) && (yd >= yMin))
                        N2 = new Point(i, Convert.ToInt32(Math.Round(yd)));
                }
                g.DrawLine(pen, M2, N2);
            }

            g.FillEllipse(brush, new System.Drawing.Rectangle(A2.X - 2, A2.Y - 2, 4, 4));
        }

    }
}
