﻿using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Fa(double size, int years) {
			if (years <= 0) { return; }
			using (new Átmenetileg(Előre, size)) {
				Fa(size/3, years-1);
				using(new Átmenetileg(Balra, 60)) {
					Fa(size / 3, years - 1);
				}
			}
			using(new Átmenetileg(Előre, size / 2)) {
				Fa(size/3, years - 1);
				using(new Átmenetileg(Jobbra, 60)) {
					Fa(size / 3, years - 1);
				}
			}
			Fa(size / 3, years - 1);
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+180, észak);
			using(new Frissítés(false)) {
				Fa(150, 8);
			}
		}
	}
}
