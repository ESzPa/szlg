using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
        void kisfra(uint order, double length, int angle) {
            if (0 == order) {
                Előre(length);
            }
            else {
                kisfra(order - 1, length / 2, -angle);
                Jobbra(angle);
                kisfra(order - 1, length / 2, angle);
                Jobbra(angle);
                kisfra(order - 1, length / 2, -angle);
            }
        }
        void Fraktal(uint order, double length) {
            if (0 == (order & 1)) {
                kisfra(order, length, 60);
            }
            else{
                Jobbra(60);
                kisfra(order, length, 60);
            }
        }


        void FELADAT()
		{
            //Teleport(közép.X-250, közép.Y+180, észak);
            Balra(90);
			using(new Frissítés(false)) {
				Fraktal(7, 300);
			}
		}
	}
}
