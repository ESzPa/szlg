using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
        void Fa(double size, int yrs, bool update)
        {
            if (yrs == 0) { return; }
            using (new Frissítés(update))
            {
                Előre(size);
                Balra(30);
                Fa(size / 2, yrs - 1, update);
                Jobbra(90);
                Fa(size / 2, yrs - 1, update);
                Balra(60);
                Hátra(size);
            }
            return;
        }


        void FELADAT()
		{
			Teleport(közép.X, közép.Y+170, észak);
            Fa(100, 10, false);
		}
	}
}
