using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
        void Fraktal(int order, double size, int sign = 1) {
            if (order <= 1) { Előre(size); return; }

            Fraktal(order - 1, size / 3, sign);
            using (new Átmenetileg(Jobbra, 60 * sign)) {
                Fraktal(order - 1, size / 3, sign);

                using (new Átmenetileg(Jobbra, -120 * sign)) {
                    Fraktal(order - 1, size / 3, sign);
                    Fraktal(order - 1, size / 3, sign);
                }

                Fraktal(order - 1, size / 3, sign);
            }
        }

        void Szigetj(double size, int order, int angle) {
            for(int i = 0; i < angle; i++) {
                Jobbra(360 / angle);
                Fraktal(order, size);
            }
        }
        void Szigete(double size, int order, int angle) {
            for (int i = 0; i < angle; i++) {
                Jobbra(360 / angle);
                Fraktal(order, size, -1);
            }
        }


        void FELADAT()
		{
			Teleport(közép.X, közép.Y, észak);
            using (new Frissítés(false)) {
                //Jobbra(90); Fraktal(300, 6);
                //Szigetj(100, 6, 6);
                Szigete(100, 6, 6);
            }
		}
	}
}
