from django.test import TestCase
from django.urls import reverse

from . import importer, queries
from .models import Tanulo


ADATOK = """"tanulokod";"nev";"mat";"angol";"2nyelv";"tesi";"csaladszam";"tesoszam"
1;"Avon Mór";"alfa";"4. Kis";"német";"F";4;1
2;"Bakt Ernő";"alfa";"4. Kis";"spanyol";"F";4;1
3;"Bal Margó";"alfa";"4. Kis";"spanyol";"L";2;0
4;"Bekre Pál";"alfa";"4. Kis";"spanyol";"F";4;1
5;"Citad Ella";"beta";"1. Sió";"spanyol";"L";3;0
6;"Daj Kálmán";"alfa";"2. Bán";"német";"F";3;0
7;"Dári Dóra";"beta";"1. Sió";"spanyol";"L";2;0
8;"Emanci Pál";"beta";"3. Joó";"spanyol";"F";5;2
9;"Feles Elek";"alfa";"2. Bán";"német";"F";3;0
10;"Git Áron";"beta";"3. Joó";"német";"F";5;2
11;"Halo Lajos";"alfa";"4. Kis";"német";"F";5;2
12;"Hát Izsák";"beta";"3. Joó";"német";"F";4;1
13;"Heu Réka";"beta";"1. Sió";"német";"L";3;0
14;"Hot Elek";"alfa";"4. Kis";"spanyol";"F";5;2
15;"Illemta Nóra";"alfa";"4. Kis";"spanyol";"L";3;0
16;"Ka Pál";"alfa";"4. Kis";"spanyol";"F";5;2
17;"Kor Mihály";"alfa";"2. Bán";"spanyol";"F";3;0
18;"Lapos Elemér";"alfa";"4. Kis";"spanyol";"F";4;1
19;"Major Anna";"alfa";"4. Kis";"német";"L";2;0
20;"Malt Ernő";"beta";"1. Sió";"spanyol";"F";4;1
21;"Mángor Olga";"beta";"3. Joó";"német";"L";4;1
22;"Meg Győző";"beta";"3. Joó";"spanyol";"F";5;2
23;"Mérta Nóra";"beta";"1. Sió";"spanyol";"L";3;1
24;"Ne Pál";"beta";"1. Sió";"német";"F";3;1
25;"Ordy Bálint";"alfa";"2. Bán";"német";"F";4;1
26;"Öröm Melitta";"beta";"3. Joó";"német";"L";4;1
27;"Parady Csoma";"alfa";"4. Kis";"spanyol";"F";4;1
28;"Patkóm Ágnes";"alfa";"2. Bán";"német";"L";6;3
29;"Patta Nóra";"alfa";"4. Kis";"spanyol";"L";5;1
30;"Rö Vid";"beta";"1. Sió";"német";"F";4;1
31;"Szikla Szilárd";"alfa";"4. Kis";"német";"F";3;0
32;"Szüre Tibor";"beta";"3. Joó";"német";"F";4;1
33;"Teo Dóra";"beta";"3. Joó";"spanyol";"L";4;1
34;"Vagd Alma";"beta";"3. Joó";"német";"L";4;1
35;"Veg Eta";"beta";"1. Sió";"spanyol";"L";3;0
36;"Zúz Mara";"beta";"3. Joó";"német";"L";5;2
"""


class CsoportokTests(TestCase):
    @classmethod
    def setUpTestData(cls):
        importer.betolt(ADATOK)

    def test_import(self):
        self.assertEqual(Tanulo.objects.count(), 36)
        self.assertEqual(Tanulo.objects.get(pk=12).nev, "Hát Izsák")
        self.assertEqual(Tanulo.objects.get(pk=2).nev, "Bakt Ernő")  # Latin-2 dekódolás

    def test_2sok(self):
        self.assertEqual(
            queries.nevek(queries.sok2()),
            ["Emanci Pál", "Git Áron", "Halo Lajos", "Hot Elek", "Ka Pál",
             "Meg Győző", "Patkóm Ágnes", "Zúz Mara"],
        )

    def test_3spec(self):
        self.assertEqual(queries.spec3().count(), 6)

    def test_4kis_kun(self):
        elotte = Tanulo.objects.filter(angol="4. Kis").count()
        self.assertGreater(elotte, 0)
        self.assertEqual(queries.kis_kun(), elotte)
        self.assertFalse(Tanulo.objects.filter(angol="4. Kis").exists())
        self.assertEqual(Tanulo.objects.filter(angol="4. Kun").count(), elotte)

    def test_5bontas_sorrend(self):
        fa = queries.bontas()
        self.assertEqual([m["nev"] for m in fa], ["alfa", "beta"])
        beta = fa[1]
        joo = next(a for a in beta["angolok"] if a["nev"] == "3. Joó")
        nemet = next(n for n in joo["nyelvek"] if n["nev"] == "német")
        self.assertEqual(
            nemet["diakok"],
            ["Git Áron", "Hát Izsák", "Mángor Olga", "Öröm Melitta",
             "Szüre Tibor", "Vagd Alma", "Zúz Mara"],
        )

    def test_6izsak(self):
        self.assertEqual(queries.izsak().count(), 1)

    def test_7kapocs(self):
        self.assertEqual(queries.nevek(queries.kapocs7()), ["Git Áron", "Szüre Tibor"])

    def test_hianyzo_hirvivo(self):
        self.assertEqual(queries.nevek(queries.hianyzo()), ["Bekre Pál"])
        self.assertEqual(
            queries.nevek(queries.hirvivo()),
            ["Bakt Ernő", "Hot Elek", "Ka Pál", "Lapos Elemér", "Parady Csoma"],
        )

    def test_oldalak(self):
        for nev in ["index", "sok2", "spec3", "kis_kun4", "bontas5",
                    "izsak6", "kapocs7", "hianyzo", "hirvivo"]:
            with self.subTest(nev):
                self.assertEqual(self.client.get(reverse(f"csoportok:{nev}")).status_code, 200)

    def test_import_view(self):
        url = reverse("csoportok:import_adatok")
        # rossz kódolású ő/ű javítása + újratöltés
        r = self.client.post(url, {"szoveg": ADATOK.replace("ő", "õ")})
        self.assertEqual(r.status_code, 200)
        self.assertEqual(r.context["betoltve"], 36)
        self.assertEqual(Tanulo.objects.get(pk=2).nev, "Bakt Ernő")

    def test_import_hibas(self):
        url = reverse("csoportok:import_adatok")
        r = self.client.post(url, {"szoveg": "valami;mas\n1;2"})
        self.assertIn("hiba", r.context)
        self.assertEqual(Tanulo.objects.count(), 36)  # a tábla érintetlen
