using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Graphic win = new Graphic();
            win.FormBorderStyle = FormBorderStyle.FixedDialog;
            Application.EnableVisualStyles();
            Application.Run(win);
        }
    }
}
