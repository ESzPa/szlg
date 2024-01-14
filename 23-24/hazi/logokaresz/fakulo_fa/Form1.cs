using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fa(double size, int years, double trans=255) {
			if(years <= 0) { return; }
			using(new Szín(Color.FromArgb((byte)trans, 84, 39, 26))) {
				using(new Átmenetileg(Előre, size)) {
					Balra(60);
					Fa(size / 1.5, years - 1, trans * 0.7);
					Jobbra(120);
					Fa(size / 1.5, years - 1, trans * 0.7);
					Balra(60);
				}
			}
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+170, észak);
			Fa(100, 10);
		}
	}
}
