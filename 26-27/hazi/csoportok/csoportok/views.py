from django.shortcuts import render
from django.views.decorators.http import require_http_methods

from . import importer, queries
from .models import FEJLEC, MEZOK, Tanulo


def _nevlista(request, cim, leiras, qs):
    return render(request, "csoportok/nevek.html", {
        "cim": cim, "leiras": leiras, "nevek": queries.nevek(qs),
    })


def _rekordok(request, cim, leiras, qs):
    sorok = list(qs.values_list(*MEZOK))
    return render(request, "csoportok/rekordok.html", {
        "cim": cim, "leiras": leiras, "fejlec": FEJLEC, "sorok": sorok,
    })


def index(request):
    return render(request, "csoportok/index.html")


def sok2(request):
    return _nevlista(request, "2sok", "Diákok, akiknek több mint 1 testvérük van.", queries.sok2())


def spec3(request):
    return render(request, "csoportok/szam.html", {
        "cim": "3spec",
        "leiras": "Családok száma, ahol az együttlakók és a testvérek száma közti különbség nem 3.",
        "szam": queries.spec3().count(),
    })


@require_http_methods(["GET", "POST"])
def kis_kun4(request):
    modositott = queries.kis_kun() if request.method == "POST" else None
    return render(request, "csoportok/modosit.html", {
        "cim": "4kis-kun",
        "leiras": "A „4. Kis” angolcsoport-bejegyzések cseréje „4. Kun”-ra.",
        "modositott": modositott,
    })


def bontas5(request):
    return render(request, "csoportok/bontas.html", {"fa": queries.bontas()})


def izsak6(request):
    return _rekordok(request, "6izsak", "Hát Izsák minden adata.", queries.izsak())


def kapocs7(request):
    return _nevlista(
        request, "7kapocs",
        "Akik Hát Izsákkal minden csoportban (testnevelésen is) együtt vannak.",
        queries.kapocs7(),
    )


def hianyzo(request):
    return _rekordok(request, "hianyzo", "Bekre adatai.", queries.hianyzo())


def hirvivo(request):
    return _nevlista(request, "hirvivo", "A hiányzó (Bekre) csoporttársai.", queries.hirvivo())


@require_http_methods(["GET", "POST"])
def import_adatok(request):
    ctx = {"cim": "Adatok betöltése"}
    if request.method == "POST":
        szoveg = request.POST.get("szoveg", "")
        try:
            ctx["betoltve"] = importer.betolt(szoveg)
        except importer.ImportHiba as e:
            ctx["hiba"] = str(e)
            ctx["szoveg"] = szoveg
    ctx["db"] = Tanulo.objects.count()
    return render(request, "csoportok/import.html", ctx)
