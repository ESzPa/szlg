using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fa(double size, int years) {
			if (years <= 0) { return; }
			using(new Átmenetileg(Előre, size)) {
				Balra(60);
				Fa(size / 1.5, years - 1);
				Jobbra(120);
				Fa(size / 1.5, years - 1);
				Balra(60);
			}
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+150, észak);
			Fa(100, 10);
		}
	}
}
