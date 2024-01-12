using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;


namespace Karesz
{
    public partial class Form1 : Form
    {
        string betöltendő_pálya = "palya04.txt";

        void TANÁR_ROBOTJAI()
        {
            int feketedb = 100;
            int pirosdb = 100; 
            int zölddb = 100;
            int sárgadb = 100;
            int hódb = 100;

            int pos_x = 5;
            int pos_y = 28;

            new Robot("Karesz", feketedb, pirosdb, zölddb, sárgadb, hódb, pos_x, pos_y, 0);

            /*
            Robot janesz = new Robot("Janesz", Robot.képkészlet_lilesz, 0, 0, 0, 0, 0, 14, 1, 2);

            janesz.Feladat = delegate ()
            {
                //
            };

            Robot fanesz = new Robot("Fanesz", Robot.képkészlet_lilesz, 0, 0, 0, 0, 0, 16, 1, 2);

            fanesz.Feladat = delegate ()
            {
                //
            };
            */

        }
    }
}