using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{
		void Shape(double size) {

			Előre(size / 2);
			Jobbra(120);
			Előre(Math.Sqrt((size / 2) * (size / 2) + size * size));
			Jobbra(150);
			Előre(size);
			Jobbra(90);
		}
		void Fraktal(double size, int rec) {
			if(rec <= 0) { }
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y, észak);


		}
	}
}
