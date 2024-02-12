using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.CompilerServices;

namespace Karesz {
    public partial class Form1 : Form {
        void DIÁK_ROBOTJAI() {
            Robot karesz = Robot.Get("Karesz");
            #region 16-os pálya
            void Keres(bool i = true) {
                if (i) {
                    Jobbra();
                }
                else {
                    Balra();
                }
                if (!Van_e_előttem_fal()) {
                    Előre();
                    if (!Van_e_itt_Kavics()) {
                        Jobbra(2);
                        Előre();
                        Balra(1);
                        Keres(!i);
                    }
                    else { return; }
                }
                else {
                    if (i) {
                        Balra();
                    }
                    else {
                        Jobbra();
                    }
                    Keres(!i);
                }
            }
            void _16() {
                while (!Kilépek_e_a_pályáról()) {
                    while (!Van_e_előttem_fal()) {
                        Előre();
                        if (!Van_e_itt_Kavics()) {
                            Jobbra(2);
                            Előre();
                            Jobbra(2);
                            break;
                        }
                    }
                    Keres();
                }
            }
            #endregion


            karesz.Feladat = delegate () {
                
            };
        }
    }
}