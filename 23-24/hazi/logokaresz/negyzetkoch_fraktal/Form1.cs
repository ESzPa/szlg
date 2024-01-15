using System;
using System.Drawing;
using System.Security.Policy;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal(double size, int rec, int sign=1) {
			if(rec <= 1) { Előre(size); return; }
			Fraktal(size, rec - 1);
			Balra(90 * sign);
            Fraktal(size, rec - 1, -1);
			Jobbra(90 * sign);
            Fraktal(size, rec - 1);
			Jobbra(90 * sign);
            Fraktal(size, rec - 1, -1);
			Balra(90 * sign);
            Fraktal(size, rec - 1);
        }


		void FELADAT()
		{
			Teleport(közép.X-250, közép.Y, észak);
			Jobbra(90);
			using(new Frissítés(false)) {
                Fraktal(50, 3);
            }
		}
	}
}
