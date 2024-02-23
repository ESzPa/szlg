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
        bool Ko_elottem() {
            Előre();
            bool van = Van_e_itt_Kavics();
            Előre(-1);
            return(van);
        }
        void Ko_keres() {
            if (!Van_e_előttem_fal() && !Kilépek_e_a_pályáról()) {
                if (!Ko_elottem()) {
                    Jobbra();
                }
            }
            if (!Van_e_előttem_fal() && !Kilépek_e_a_pályáról()) {
                if (Ko_elottem()) {
                    return;
                }
            }
            Balra(2);
        }

        void kovet() {
            while(true) {
                if(!Van_e_előttem_fal() && !Kilépek_e_a_pályáról()) {
                    if(Ko_elottem()) {
                        Előre();
                    }
                    else {
                        Ko_keres();
                    }
                }
                else {
                    Ko_keres();
                }
            }
        }

        void vmi() {
            ElőreRakj(10);
            Jobbra();
            Előre(-1);
            ElőreRakj(5);
            Jobbra();
            Előre(-1);
            ElőreRakj(3);
            Jobbra();
            Előre(-1);
            ElőreRakj(3);
            Balra();
            Előre(-1);
            ElőreRakj(3);
            Balra();
            Előre(-1);
            ElőreRakj(3);
            Balra();
            Előre(-1);
            ElőreRakj(5);
            Előre();
            Balra();
            Előre();
            Balra(2);
        }
        void DIÁK_ROBOTJAI()
        {
            Robot karesz = Robot.Get("Karesz");

            karesz.Feladat = delegate ()
            {
                //code goes here brrrrr 
                vmi();
            };
        }
    }
}
