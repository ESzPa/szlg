from django.db import models


class Tanulo(models.Model):
    """Az `adatok` tábla: egy sor = egy diák (adatok.txt)."""

    tanulokod = models.IntegerField(primary_key=True)
    nev = models.CharField(max_length=100)
    mat = models.CharField(max_length=20)       # matek/infó csoport
    angol = models.CharField(max_length=30)     # pl. "4. Kis"
    # A fájl mezőneve "2nyelv" - Python-azonosító nem kezdődhet számmal,
    # ezért a mező neve nyelv2, az adatbázis-oszlop neve viszont "2nyelv".
    nyelv2 = models.CharField(max_length=30, db_column="2nyelv")
    tesi = models.CharField(max_length=1)       # F / L (testnevelés-bontás)
    csaladszam = models.IntegerField()
    tesoszam = models.IntegerField()

    class Meta:
        db_table = "adatok"
        ordering = ["tanulokod"]

    def __str__(self):
        return self.nev


# A fájl eredeti mezősorrendje / fejlécei (táblázatos megjelenítéshez)
MEZOK = ["tanulokod", "nev", "mat", "angol", "nyelv2", "tesi", "csaladszam", "tesoszam"]
FEJLEC = ["tanulokod", "nev", "mat", "angol", "2nyelv", "tesi", "csaladszam", "tesoszam"]
