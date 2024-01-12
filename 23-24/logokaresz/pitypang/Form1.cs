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
            int fok = yrs-1;
            if (fok == 0) { fok = 1; }
            using (new Frissítés(update))
            {
                Előre(size);
                Balra(60);
                for(int i = 0; i < yrs; i++)
                {
                    Fa(size / 2, yrs - 1, update);
                    Jobbra(120/fok);
                }
                Balra(60);
                Hátra(size);
            }
            return;
        }


        void FELADAT()
		{
			Teleport(közép.X, közép.Y+150, észak);
            Fa(100, 2);
		}
	}
}
