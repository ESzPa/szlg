using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Karesz {
    public partial class Form1 : Form {

        void palya06(Robot robot) {
            Jobbra(2);
            while(!Van_e_előttem_fal()) {
                Előre();
            }
            Jobbra(1);
            while (!Van_e_előttem_fal()) {
                Előre();
            }
            Jobbra(1);
            while (true) {
                Előre();
                Jobbra();
                while (!Van_e_előttem_fal()) {
                    Előre();
                }
                Balra(2);
                while (!Van_e_előttem_fal()) {
                    Előre();
                }
                Jobbra();
            }
        }
        void DIÁK_ROBOTJAI() {
            Robot karesz = Robot.Get("Karesz");

            karesz.Feladat = delegate () {
                palya06(karesz);
            };
        }
    }
}
