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
                Jobbra(60);
                Fa(size / 2, yrs - 1, update);
                Balra(30);
                Hátra(size/2);
                Balra(30);
                Fa(size/2, yrs - 2, update);
                Jobbra(30);
                Hátra(size / 2);
            }
            return;
        }

        void FELADAT()
		{
			Teleport(közép.X, közép.Y+150, észak);
            Fa(10, 10, false);
		}
	}
}
