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
        void DIÁK_ROBOTJAI()
        {
            Robot karesz = Robot.Get("Karesz");

            karesz.Feladat = delegate ()
            {
                //code goes here brrrrr 
                
            };
        }
    }
}
