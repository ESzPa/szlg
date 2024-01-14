using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fa(double size, int years) {
			Color c;
			if (years <= 0) { return; }
			else if (years == 1) { c = Color.LightGreen; } 
			else if (years == 2) { c = Color.DarkGreen; }
			else { c = Color.Brown; }
			using(new Szín(c)) {
				using (new Vastagság((years + 1) / 2)) {
					using (new Átmenetileg(Előre, size)) {
						Balra(30);
						Fa(size / 1.5, years - 1);
						Jobbra(30);
						Fa(size / 1.2, years - 1);
						Jobbra(30);
						Fa(size / 1.5, years - 1);
						Balra(30);
					}
				}
			}
		}
		void FELADAT()
		{
			Teleport(közép.X, közép.Y+170, észak);
			Fa(100, 5);
		}
	}
}
