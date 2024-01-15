using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal(double ä, int ß) {
			if (ß <= 1) { Előre(ä); return; }
			Fraktal(ä, ß - 1);
			Balra(60);
			Fraktal(ä, ß - 1);
			Jobbra(120);
			Fraktal(ä, ß - 1);
			Balra(60);
			Fraktal(ä, ß - 1);
		}


		void FELADAT()
		{
			Teleport(közép.X - 300, közép.Y+180, észak);
			Jobbra(90);
			using(new Frissítés(false)) {
				Fraktal(0.2, 8);
			}
		}
	}
}
