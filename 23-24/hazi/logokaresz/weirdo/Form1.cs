using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form {
		void Vonalnt(double size, int num) {
            if (num <= 1) { Előre(size); return; }
			Vonalnt(size/3, num - 1);
			Jobbra(-60);
			Vonalnt(size/3, num-1);
			Jobbra(60);
			Vonalnt(size/3, num-1);
        }
        void Weirdo(double size, int cracks) {
			for(int i= 0; i < 3; i++) {
				Vonalnt(size/cracks, cracks);
				Jobbra(120);
			}
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+180, észak);
			Weirdo(500, 3);
        }
	}
}
