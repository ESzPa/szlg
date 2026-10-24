"""A feladat lekérdezései. Minden függvény neve a feladatban megadott lekérdezésnév."""
import unicodedata

from django.db.models import F, Subquery

from .models import Tanulo


def hu_key(szoveg):
    """Magyar ABC szerinti rendezéshez: o < ó < ö < ő, kis/nagybetű nem számít."""
    s = szoveg.casefold()
    alap = "".join(c for c in unicodedata.normalize("NFD", s) if not unicodedata.combining(c))
    return (alap, s)


def nevek(qs):
    """A lekérdezés neveinek listája névsorban."""
    return sorted(qs.values_list("nev", flat=True), key=hu_key)


# --- 2sok: több mint 1 testvér --------------------------------------------
def sok2():
    return Tanulo.objects.filter(tesoszam__gt=1)


# --- 3spec: együttlakók és testvérek száma közti különbség nem 3 ----------
def spec3():
    return Tanulo.objects.exclude(csaladszam=F("tesoszam") + 3)


# --- 4kis-kun: módosító (UPDATE) lekérdezés --------------------------------
def kis_kun():
    """Visszaadja a módosított sorok számát."""
    return Tanulo.objects.filter(angol="4. Kis").update(angol="4. Kun")


# --- 5bontas: matek > angol > 2. nyelv szerint csoportosított névsor ------
def bontas():
    fa = []
    qs = Tanulo.objects.order_by("mat", "angol", "nyelv2")
    for t in qs:
        if not fa or fa[-1]["nev"] != t.mat:
            fa.append({"nev": t.mat, "angolok": []})
        angolok = fa[-1]["angolok"]
        if not angolok or angolok[-1]["nev"] != t.angol:
            angolok.append({"nev": t.angol, "nyelvek": []})
        nyelvek = angolok[-1]["nyelvek"]
        if not nyelvek or nyelvek[-1]["nev"] != t.nyelv2:
            nyelvek.append({"nev": t.nyelv2, "diakok": []})
        nyelvek[-1]["diakok"].append(t.nev)
    for m in fa:
        for a in m["angolok"]:
            for n in a["nyelvek"]:
                n["diakok"].sort(key=hu_key)
    return fa


# --- 6izsak: Hát Izsák minden adata ---------------------------------------
def izsak():
    return Tanulo.objects.filter(nev="Hát Izsák")


# --- 7kapocs: akikkel Izsák MINDEN csoportban együtt van -------------------
def tarsak(alap):
    """Az `alap` lekérdezés (egy diák) csoporttársai: azonos mat, angol, 2nyelv
    és tesi, az illető maga nélkül. Az alap-lekérdezés részlekérdezésként épül be."""
    return (
        Tanulo.objects.filter(
            mat=Subquery(alap.values("mat")[:1]),
            angol=Subquery(alap.values("angol")[:1]),
            nyelv2=Subquery(alap.values("nyelv2")[:1]),
            tesi=Subquery(alap.values("tesi")[:1]),
        )
        .exclude(pk__in=alap.values("pk"))
    )


def kapocs7():
    return tarsak(izsak())


# --- hianyzo / hirvivo: a 6izsak / 7kapocs másolatai ----------------------
def hianyzo():
    """6izsak másolata, Bekre adataira módosítva (keresztnév nem ismert)."""
    return Tanulo.objects.filter(nev__startswith="Bekre ")


def hirvivo():
    """7kapocs másolata: a hianyzo-ban talált névhez listázza a társakat."""
    return tarsak(hianyzo())
