using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karesz
{
	partial class Form1
	{
		#region Robotokra visszavezetett parancsok
		void Fordulj(int n, int x=1) =>
			Robot.akit_kiválasztottak.Fordulj(n, x);
		/// <summary>
		/// Lép és lerak n alkalommal, paraméter nélkül egyszer
		/// </summary>
		/// <param name="n"></param>
		/// <param name="c"></param>
		void ElőreRakj(int n = 1, int c = fekete) =>
			Robot.akit_kiválasztottak.ElőreRakj(n, c);
		/// <summary>
		/// Nem fogy a köve
		/// </summary>
		/// <param name="n"></param>
		void Végtelenkő(bool n = true) =>
			Robot.akit_kiválasztottak.Végtelen_kő(n);
		/// <summary>
		/// Előre megy n alkalommal, paraméter nélkül egyszer
		/// </summary>
		/// <param name="n"></param>
		void Előre(int n = 1) =>
			Robot.akit_kiválasztottak.Előre(n);
		/// <summary>
		/// Jobbra fordul, paraméter esetén n alkalommal
		/// </summary>
		/// <param name="n"></param>
		void Jobbra(int n = 1) =>
			Robot.akit_kiválasztottak.Fordulj(jobbra, n);
        /// <summary>
        /// Balra fordul, paraméter esetén n alkalommal
        /// </summary>
        /// <param name="n"></param>
        void Balra(int n = 1) =>
			Robot.akit_kiválasztottak.Fordulj(balra, n);
		/// <summary>
		/// Visszaad egy int-et, hogy hány kő maradt egy adott színből
		/// </summary>
		/// <param name="szín"></param>
		/// <returns></returns>
		int Köveinek_száma_ebből(int szín) => 
			Robot.akit_kiválasztottak.Köveinek_száma_ebből(szín);
		/// <summary>
		/// Felveszi az alatta lévő követ
		/// </summary>
		void Vegyél_fel_egy_kavicsot() => 
			Robot.akit_kiválasztottak.Vegyél_fel_egy_kavicsot();
		/// <summary>
		/// Letesz egy kavicsot a paraméterben adott színből
		/// </summary>
		/// <param name="szín"></param>
		void Tegyél_le_egy_kavicsot(int szín = fekete) => 
			Robot.akit_kiválasztottak.Tegyél_le_egy_kavicsot(szín);
		bool Van_e_itt_Kavics() => 
			Robot.akit_kiválasztottak.Alatt_van_kavics();
		int Mi_van_alattam() => 
			Robot.akit_kiválasztottak.Alatt_ez_van();
		bool Van_e_előttem_fal() =>
			Robot.akit_kiválasztottak.Előtt_fal_van();
		bool Kilépek_e_a_pályáról() =>
			Robot.akit_kiválasztottak.Ki_fog_lépni_a_pályáról();
		int Ultrahang() => 
			Robot.akit_kiválasztottak.UltrahangSzenzor();
		int Hőmérséklet() => 
			Robot.akit_kiválasztottak.Hőmérő();

        #endregion

        #region Pályára visszavezetett parancsok

        void Betölt(string path) => pálya.Betölt(path);

        #endregion
	}
}
