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
        void helloworld() {
            while (!Van_e_előttem_fal()) {
                Előre();
            }
            Balra();
            while (!Van_e_előttem_fal()) {
                Előre();
            }
            Balra();
            while (true) {
                if (!Van_e_előttem_fal()) {
                    Előre();

                    if (Van_e_itt_Kavics()) {
                        Vegyél_fel_egy_kavicsot();
                    }
                }
                Jobbra();
                if (!Van_e_előttem_fal()) {
                    Előre();
                    if (Van_e_itt_Kavics()) {
                        Vegyél_fel_egy_kavicsot();
                    }
                }
                else {
                    Balra();
                }
                if (Van_e_előttem_fal()) {
                    Balra();
                }
            }
        }
        void DIÁK_ROBOTJAI()
        {
            Robot karesz = Robot.Get("Karesz");

            karesz.Feladat = delegate ()
            {
                helloworld();
                
            };
        }
    }
}
