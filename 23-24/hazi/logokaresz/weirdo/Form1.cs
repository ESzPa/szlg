using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form {
		void Vonal(double size, int num, int sign = 1) {
			if (num <= 0) { return; }
			Jobbra(-30 * sign);
			using (new Átmenetileg(Előre, size)) {
				Jobbra(30 * sign);
				Vonal(size, num - 1, sign * -1);
				Jobbra(-30 * sign);
			}
			Jobbra(30 * sign);
		}
		void Vonalnt(double size, int num, int sign = 1) {
            if (num <= 0) { return; }
            Jobbra(-30 * sign);
			Előre(size);
            Jobbra(30 * sign);
            Vonalnt(size, num - 1, sign * -1);
        }
        void Weirdo(double size, int cracks) {
			double inner = Math.Pow(3, cracks-1);
			if(cracks == 1) { inner = 1; }
			for(int i= 0; i < 3; i++) {
				Console.WriteLine(inner);
				Vonalnt(size/inner, (int)inner);
				Jobbra(120);
			}
		}


		void FELADAT()
		{
			Teleport(közép.X, közép.Y+180, észak);
			//Vonal(50, 3);
			Weirdo(300, 3);
        }
	}
}
