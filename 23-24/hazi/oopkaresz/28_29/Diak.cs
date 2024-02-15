using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Karesz
{
    public partial class Form1 : Form
    {
        void DIÁK_ROBOTJAI()
        {
            #region Koordináta rendszer

            int x = 0;
            int y = 0;
            int karesz_irany = 0;
            // 0, 1, 2, 3
            List<int[]> Kövek= new List<int[]>();
            
            void KElore() {
                Előre();
                switch (karesz_irany) {
                    case 0:
                        y++;
                        break;
                    case 1:
                        x++;
                        break;
                    case 2:
                        y--;
                        break;
                    case 3:
                        x--;
                        break;
                }
            }

            void KFordulj(int n) {
                if(n != 1 && n!= -1) { return; }
                if (n == 1) {
                    Jobbra();
                    if (karesz_irany == 3) {
                        karesz_irany = 0;
                    }
                    else {
                        karesz_irany++;
                    }
                }
                else {
                    Balra();
                    if (karesz_irany == 0) {
                        karesz_irany = 3;
                    }
                    else {
                        karesz_irany--;
                    }
                }
            }

            void Nezz(int n) {
                if (n != 0 && n != 1 && n != 2 && n != 3) { return; }
                while (n != karesz_irany) {
                    KFordulj(1);
                }
            }

            bool Go_to(int gotox, int gotoy) {
                if (gotox < 0 || gotoy < 0 || gotox > 40 || gotoy > 30) {
                    return false;
                }
                int temp_irany = karesz_irany;
                int diffx = Math.Abs(gotox - x);
                int diffy = Math.Abs(gotoy - y);
                Nezz(0);
                if (gotoy > y) {
                    for(int i = 0; i < diffy ; i++) { //jo
                        KElore();
                    }
                }
                else if (gotoy < y) {
                    KFordulj(1);
                    KFordulj(1);
                    for (int i = 0; i < diffy; i++) {
                        KElore();
                    }
                    KFordulj(1);
                    KFordulj(1);
                }
                if (gotox > x) {
                    KFordulj(1);
                    for(int i = 0;i < diffx ; i++) { //jo
                        KElore();
                    }
                    KFordulj(-1);
                }
                else if (gotox < x) {
                    KFordulj(-1);
                    for (int i = 0; i < diffx; i++) {
                        KElore();
                    }
                    KFordulj(1);
                }
                Nezz(temp_irany);
                return true;
            }

            void AddData(int map) {
                int[] xyc = new int[3];
                xyc[0] = x;
                xyc[1] = y;
                if(map == 28) {
                    xyc[2] = 4;
                }
                else if(map == 29) {
                    xyc[2] = Mi_van_alattam();
                }
                else {
                    MessageBox.Show("No map");
                }
                Kövek.Add(xyc);
            }

            #endregion

            void Végigmegy(int map) {
                int sign = 1;
                while (true) {
                    if (Kilépek_e_a_pályáról()) {
                        KFordulj(sign);
                        if (Kilépek_e_a_pályáról()) {
                            break;
                        }
                        else {
                            if (Van_e_itt_Kavics()) {
                                AddData(map);
                            }
                            KElore();
                            KFordulj(sign);
                            sign *= -1;
                        }
                    }
                    else {
                        if (Van_e_itt_Kavics()) {
                            AddData(map);
                        }
                        KElore(); 
                    }
                }
                KFordulj(-1);
            }

            void Kavics(int c) {
                if (!Van_e_itt_Kavics()) {
                    Tegyél_le_egy_kavicsot(c);
                }
            }

            void Korberak(int gotox, int gotoy, int c) {
                if(Go_to(gotox, gotoy + 1)) {
                    Kavics(c);
                }
                if(Go_to(gotox + 1, gotoy + 1)) {
                    Kavics(c);
                }
                if(Go_to(gotox + 1, gotoy)) {
                    Kavics(c);
                }
                if(Go_to(gotox + 1, gotoy - 1)) {
                    Kavics(c);
                }
                if(Go_to(gotox, gotoy - 1)) {
                    Kavics(c);
                }
                if(Go_to(gotox - 1, gotoy - 1)) {
                    Kavics(c);
                }
                if(Go_to(gotox - 1, gotoy)) {
                    Kavics(c);
                }
                if(Go_to(gotox - 1, gotoy + 1)) {
                    Kavics(c);
                }
            }

            void Végigrak(List<int[]> kove) {
                for(int i = 0; i < kove.Count; i++) {
                    Korberak(kove[i][0], kove[i][1], kove[i][2]);
                }
            } 

            void Végigrak_28(List<int[]> kove) {
                for (int i = 0; i < kove.Count; i++) {
                    Korberak(kove[i][0], kove[i][1], kove[i][2]);
                }
            }
            
            void Solve(int map) {
                Végtelenkő();
                Végigmegy(map);
                Go_to(0, 0);
                Végigrak(Kövek);
            }

            Robot karesz = Robot.Get("Karesz");



            karesz.Feladat = delegate ()
            {
                //BAL ALSO SAROKBA KELL RAKNI INDULASKOR!

                //28
                //Solve(28);

                //29
                //Solve(29);
            };
        }
    }
}
