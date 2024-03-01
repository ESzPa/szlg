using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Linq.Expressions;
using System.Security.Cryptography;

namespace Karesz
{
    public partial class Form1 : Form
    {
        #region 1. Feladat Várfal
        
        void bastya(int height) {
            Előre(-1);
            ElőreRakj(height);
            Jobbra();
            Előre(-1);
            ElőreRakj(3);
            Jobbra();
            Előre(-1);
            ElőreRakj(height);
            Jobbra(2);
        }

        void varfal(int pcs, int height) {
            for(int i = 1; i < pcs+1; i++) {
                if(i % 2 == 0) {
                    bastya(height - 2);
                }
                else {
                    bastya(height);
                }
                Jobbra();
                Előre();
                Balra();
            }
        }


        #endregion
        #region 2. Feladat Kiút

        /*
        const int fekete = 2;
        const int piros = 3;
        const int zöld = 4;
        const int sárga = 5;
        const int hó = 6;
        const int víz = 8;
        */

        void kiut() {
            Random generator = new Random();
            generator.Next(0, 1);
            while (!Van_e_előttem_fal()) { Előre(); }
            Jobbra();
            while (true) {
                if (Van_e_előttem_fal()) {
                    Jobbra();
                }
                Előre();
                Tegyél_le_egy_kavicsot(generator.Next(2, 7));
                Balra();
                if (!Van_e_előttem_fal()) {
                    break;
                }
                Jobbra();
            }
            Előre();
        }

        #endregion
        #region 3. Feladat Takaritas, Ultetes

        void handle_stone() {
            if(Mi_van_alattam() == 2 || Mi_van_alattam() == 3) {
                Vegyél_fel_egy_kavicsot();
            } 
            else if(Mi_van_alattam() == 5) {
                for(int i = -1; i < 2; i+=2) {
                    Előre();
                    Tegyél_le_egy_kavicsot(6);
                    Előre(-2);
                    Tegyél_le_egy_kavicsot(6);
                    Előre();
                    Fordulj(i);
                }
            }
        }

        void Vegigmegy() {
            for(int i = 0; i < 2; i++) {
                Balra();
                while (!Kilépek_e_a_pályáról()) { Előre(); }
            }
            Jobbra(2);

            int sign = 1;
            while (true) {
                if (Kilépek_e_a_pályáról()) {
                    Fordulj(sign);
                    if (Kilépek_e_a_pályáról()) {
                        break;
                    }
                    else {
                        if (Van_e_itt_Kavics()) {
                            handle_stone();
                        }
                        Előre();
                        Fordulj(sign);
                        sign *= -1;
                    }
                }
                else {
                    if (Van_e_itt_Kavics()) {
                        handle_stone();
                    }
                    Előre();
                }
            }
            Fordulj(-1);
        }



        #endregion

        void DIÁK_ROBOTJAI()
        {
            Robot karesz = Robot.Get("Karesz");

            karesz.Feladat = delegate ()
            {
                Végtelenkő(); // csak hogy nehogy kifogyjon a kavicsbol

                Vegigmegy();
                
            };
        }
    }
}
