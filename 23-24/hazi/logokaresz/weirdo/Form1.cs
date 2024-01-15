using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form {
		void Vonal(double size, int num, int sign = 1) {
			if (num <= 0) { return; }
			Jobbra(-30 * sign);
			using (new Átmenetileg(Előre, size)) {
				Jobbra(30 * sign);
				Vonal(size, num - 1, sign * -1);
				Jobbra(-30 * sign);
			}
			Jobbra(30 * sign);
		}
	


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+180, észak);
			Vonal(50, 3);
		}
	}
}
