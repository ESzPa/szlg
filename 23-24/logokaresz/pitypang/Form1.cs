using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
        void Fa(double size, int yrs)
        {
            if (yrs <= 0) { return; }
            using (new Átmenetileg(Előre, size))
            {
                Balra(60);
                for(int i = 0; i < yrs - 1; i++)
                {
                    Fa(size / 2, yrs - 1);
                    Jobbra(120 / (yrs - 1));
                    Fa(size/2, yrs - 1);
                }
                if (yrs == 1)
                {
                    Jobbra(120);
                }
                Balra(60);
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
