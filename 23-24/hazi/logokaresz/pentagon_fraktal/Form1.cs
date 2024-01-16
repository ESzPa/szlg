using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fraktal5(double size, int rec) {
			if (rec <= 0) { return; }
            for (int i = 0; i < 5; i++) {
                Előre(size);
                Jobbra(72);
				using(new Átmenetileg(Jobbra, -144)) {
					Fraktal5(size, rec-1);
				}
            }
        }


		void FELADAT()
		{
			Teleport(közép.X-10, közép.Y-10, észak);
			using(new Frissítés(false)) {
				Fraktal5(10, 3);
			}
		}
	}
}
