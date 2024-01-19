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
            Fraktal(size / 2, rec - 1);
			Jobbra(72);
            Fraktal(size / 2, rec - 1);
			Jobbra(-144);
            Fraktal(size / 2, rec - 1);
			using(new Átmenetileg(Jobbra, -72)) {
				Fraktal(size/2, rec-1);
            }
            Fraktal(size / 2, rec - 1);
			Jobbra(72);
            Fraktal(size / 2, rec - 1);
        }

        void Fraktal5(double size, int rec) {
            for (int i = 0; i < 5; i++) {
				Fraktal(size, rec);
                Jobbra(72);
            }
        }


		void FELADAT()
		{
			Teleport(közép.X-10, közép.Y-10, észak);
			using(new Frissítés(false)) {
				//Fraktal(50, 5);
				//Fraktal5(50, 5);
			}
		}
	}
}
