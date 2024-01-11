using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
        void Fa(double size, int yrs, bool update=true)
        {
            if (yrs == 0) { return; }
            using (new Frissítés(update))
            {
                Előre(size);
                Balra(60);
                Fa(size / 2, yrs - 1, update);
                Jobbra(120);
                Fa(size / 1.5, yrs - 1, update);
                Balra(60);
                Hátra(size);
            }
            return;
        }


        void FELADAT()
		{
			Teleport(közép.X, közép.Y+170, észak);

            Fa(100, 5);
		}
	}
}
