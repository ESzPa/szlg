using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fa(double size, int years) {
			Color c;
			if (years <= 0) { return; }
			else if (years == 1) { c = Color.Green; }
			else { c =Color.Brown; }
			using(new Szín(c)) {
				using(new Átmenetileg(Előre, size)) {
					Balra(60);
					Fa(size/1.5, years-1);
					Jobbra(120);
					Fa(size/1.5, years-1);
					Balra(60);
				}
			}
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+180, észak);
			Tollvastagság(2f);
			using(new Frissítés(false)) {
				Fa(150, 10);
			}
		}
	}
}
