using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal(double size, int side) {
			if(side < 3) { return; }
			double fordulas;
			for(int i = 0; i < side; i++) {
				fordulas = (180 * (side - 2) / side / 2) - (180 * (side - 3) / (side - 1) / 2); 
                Előre(size);
				Jobbra(180 - (180 * (side - 2) / side));
				using(new Átmenetileg(Jobbra, fordulas)) {
					Fraktal(size / 2, side - 1);
				}
			}
		}


		void FELADAT()
		{
			Teleport(közép.X-250, közép.Y+100, észak);
			using(new Frissítés(false)) {
				Fraktal(150, 7);
			}
		}
	}
}
