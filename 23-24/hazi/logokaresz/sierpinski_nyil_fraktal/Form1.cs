using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal(double size, int rec, int sign=1) {
			if (rec <= 1) { Előre(size); return; }
			Balra(60*sign);
			Fraktal(size, rec-1, -1);
			Jobbra(60*sign);
            Fraktal(size, rec - 1);
			Jobbra(60 * sign);
            Fraktal(size, rec - 1, -1);
			Balra(60 * sign);
        }


		void FELADAT()
		{
			Teleport(közép.X-250, közép.Y+180, észak);
			Jobbra(90);
			using(new Frissítés(false)) {
				Fraktal(10, 3);
			}
		}
	}
}
