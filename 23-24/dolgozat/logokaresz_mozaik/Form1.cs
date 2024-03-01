using System;
using System.Drawing;
using System.Security.Policy;
using System.Threading;
using System.Timers;
using System.Windows.Forms;

namespace LogoKaresz
{
	public partial class Form1 : Form
	{

        #region 1. Feladat Segédfunkciók
		void Odatölt(double side1, double side2, Color color, int dir=1){
			using(new Rajzol(false)) {
                using (new Átmenetileg(Előre, side1)) {
                    using (new Átmenetileg(Jobbra, 90 * dir)) {
                        using (new Átmenetileg(Előre, side2)) {
                            Tölt(color, false);
                        }
                    }
                }
            }
		}
		void Téglalap(double side1, double side2, Color color) { 
			for(int i = 0; i < 2; i++) {
				Előre(side2);
				Jobbra(-90);
				Előre(side1);
				Jobbra(-90);
			}
			Odatölt(side2/2, side1/2, color, -1);
		}
		void VéJump(double side2) {
			using(new Rajzol(false)) {
                Jobbra(135);
                Előre(side2);
                Jobbra(-90);
                Előre(side2);
                Jobbra(-45);
            }
		}
		void ParkettaJump(double side1) {
			using(new Rajzol(false)) {
				Jobbra(45);
				Előre(side1);
				Balra(90);
				Előre(side1);
				Jobbra(45);
			}
		}

        #endregion
        #region 1. Feladat Megoldás

		void Vé(double side1, double side2, Color color) {
			using(new Átmenetileg(Jobbra, 135)) {
				Téglalap(side1, side2, color);
				using(new Átmenetileg(Előre, side2+side1)) {
					using(new Átmenetileg(Jobbra, -90)) {
						Téglalap(side1, side2, color);
					}
				}
			}
		}
		void ParkettaSor(double side1, double side2, Color color, int db) {
			for(int i=0; i<db; i++) {
				Vé(side1, side2, color);
				VéJump(side2);
			}
			for(int i=0; i<db;i++) {
				VéJump(-side2);
			}
		}
		void Parketta(double side1, double side2, Color color, int xdb, int ydb) {
			for(int i = 0; i < ydb; i++) {
				ParkettaSor(side1, side2, color, xdb);
				ParkettaJump(side1);
			}
			for(int i=0; i<ydb; i++) {
				ParkettaJump(-side1);
			}
		}

		#endregion
		#region 2. Feladat Segédfunkciók
		void Odatölt_forward(double side, Color color) {
			using(new Rajzol(false)) {
				using(new Átmenetileg(Előre, side)) {
					Tölt(color, false);
				}
			}
		}
		void UpsidedownHázikó(double side, Color color) {
			Jobbra(30);
			Előre(side);
			Jobbra(-30);
			Előre(side);
			for(int i=0; i<2; i++) {
				Balra(90);
				Előre(side);
			}
			Jobbra(-30);
			Előre(side);
			Jobbra(-150);
			Odatölt_forward(side/2, color);
		}
		void SpiralJump(double side) { //ez nagyon csúnya lett
			using(new Rajzol(false)) {
                Balra(90);
                Előre(side);
                Jobbra(60);
                Előre(side);
				Jobbra(60);
				Előre(side);

                Balra(30);
                Előre(side);
				Jobbra(-30);
				Előre(side); Balra(-30);
            }
		}
		void MozaikJump(double side) { //ez még csúnyább
            using (new Rajzol(false)) {
                Balra(90);
                Előre(side);
                Jobbra(60);
                Előre(side);
                Jobbra(60);
                Előre(side);
				Jobbra(30);
				Előre(side);

                Balra(30);
                Előre(side);
                Jobbra(-30);
                Előre(side); Balra(-30);
            }
        }

        #endregion
        #region 2. Feladat Megoldás

		void Spiral(double size, Color color=default(Color)) {
			if(color == default(Color)) { color = Color.Black; }
			using(new Átmenetileg(Jobbra, 120)) {
                for (int i = 0; i < 6; i++) {
                    UpsidedownHázikó(size, color);
                    Balra(30);
                    Előre(size);
                    Balra(30);
                }
            }
		}
		void Spiralsor(double size, int db, Color color=default(Color)) {
            if (color == default(Color)) { color = Color.Black; }
            for (int i = 0;i < db;i++) {
				Spiral(size);
				SpiralJump(size);
			}
			for(int  i = 0;i < db; i++) {
				SpiralJump(-size);
			}
		}
		void Spiralmozaik(double size, int ydb, int xdb, Color color = default(Color)) {
            if (color == default(Color)) { color = Color.Black; }
			using( new Átmenetileg(Balra, 90)) {
				for(int i = 0; i < ydb; i++) {
					Spiralsor(size, xdb, color);
					MozaikJump(size);
				}
			}
        }

        #endregion

        void FELADAT()
		{
			//	1. Feladat

			//Vé(20, 80, Color.SandyBrown);
			//
			//ParkettaSor(20, 80, Color.SandyBrown, 3);
			//
			//Parketta(20, 80, Color.SandyBrown, 3, 4);


			// 2. Feladat

			//Spiral(30);
			//
			//Spiralsor(20, 3); //A jump egy katyvasz és fél óra debugging után sem tudtam rájönni hogyan csúszik el
			//
			//Spiralmozaik(10, 3, 5); //nem működik, eh
		}
	}
}
