using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal(double size, int rec) {
			if (rec <= 1) { Előre(size); return; }
			Fraktal(size, rec - 1);
			Balra(60);
            Fraktal(size, rec - 1);
			Jobbra(120);
            Fraktal(size*2, rec - 1);
			Balra(120);
            Fraktal(size, rec - 1);
			Jobbra(60);
            Fraktal(size, rec - 1);
        }


		void FELADAT()
		{
			Teleport(közép.X-250, közép.Y, észak);
			Jobbra(90);
			using(new Frissítés(false)) {
				Fraktal(0.002, 10);
			}
		}
	}
}
