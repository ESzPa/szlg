using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace LogoKaresz {
    public partial class Form1 : Form {
        #region Fraktal   
        void Fraktal(int yrs, double size, int sign) {
            if (yrs <= 1) { Előre(size); return; }
            Fraktal(yrs - 1, size / 2, sign * -1);
            using (new Átmenetileg(Jobbra, 90 * sign)) {
                Fraktal(yrs - 1, size / 2, sign);
                Hátra(size / 2);
                Fraktal(yrs - 1, size / 2, sign * -1);
                Hátra(size / 2);
            }
            Fraktal(yrs - 1, size / 2, sign * -1);
        }

        void NegyzetFraktal(int yrs, double size, int sign) {
            for(int i = 0; i < 4; i++) {
                Fraktal(yrs, size, sign*-1);
                Jobbra(90);
            }
        }
        #endregion

        #region Fa
        void Fa(int yrs, double size) {
            if (yrs <= 0) { return; }
            if (yrs <= 1) { Tollszín(Color.Green); }
            using (new Vastagság(yrs)) {
                using (new Átmenetileg(Előre, size)) {
                    Balra(50);
                    Fa(yrs - 1, size / 1.5);
                    Jobbra(100);
                    Fa(yrs - 1, size / 1.5);
                    Balra(50);
                }
                using (new Átmenetileg(Előre, size / 3)) {
                    using (new Átmenetileg(Jobbra, 50)) {
                        Fa(yrs - 3, size / 1.5);
                    }
                }
            }
            Tollszín(Color.Black);
        }
        #endregion

        void FELADAT() {
            //Fraktal
            /*
            Balra(90);
            Fraktal(4, 100, 1);
            */

            //Negyzetfraktal
            /*
            using (new Frissítés(false)) {
                NegyzetFraktal(5, 100, 1);
            }
            */

            //Fa
            /*
			Teleport(közép.X, közép.Y + 150, észak);
			using (new Frissítés(false)) {
				Fa(8, 100);
			}
			*/
        }
    }
}
