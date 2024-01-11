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
			using(new Frissítés(update))
			{
				Előre(size);
				Balra(30);
				Fa(size / 2, yrs - 1, update);
				Jobbra(60);
				Fa(size/2, yrs - 1, update);
				Balra(30);
				Hátra(size);
			}
			return;
		}
		void FaLoop(double size, int start, int end = -1, int wait = 1000)
		{
            if (start < 1 || end < 1 || size < 0)
            {
				MessageBox.Show("Ne adj meg a FaLoopnak 1-nél kisebb számot");
				return;
            }
            if (end == -1)
			{
				end = start;
				start = 1;
			}
			for(int i = start; i <= end; i++)
			{
				Fa(size, i, false);
				Pihi(wait);
				Tollszín(Color.White);
				Tollvastagság(10);
				Fa(size, i, false);
				Tollszín(Color.Black);
				Tollvastagság(1);
			}
		}

		void FELADAT()
		{
			Teleport(közép.X, közép.Y+170, észak);

			//Fa(100, 2);

			FaLoop(170, 1, 10);
		}
	}
}
