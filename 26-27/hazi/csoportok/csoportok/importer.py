import csv
import io

from django.db import IntegrityError, transaction

from .models import Tanulo

# Ha a txt-t rossz kódolással nyitották meg, a magyar ő/ű így jelenik meg: õ/û.
# Magyar szövegben ezek a betűk nem fordulnak elő, ezért biztonságosan javíthatók.
JAVITAS = str.maketrans({"õ": "ő", "Õ": "Ő", "û": "ű", "Û": "Ű"})

KELL = {"tanulokod", "nev", "mat", "angol", "2nyelv", "tesi", "csaladszam", "tesoszam"}


class ImportHiba(ValueError):
    pass


@transaction.atomic
def betolt(szoveg):
    """Az adatok.txt tartalmából (fejléc + pontosvesszős sorok) újratölti az adatok táblát.
    Visszaadja a betöltött sorok számát; hiba esetén ImportHiba, és a tábla érintetlen marad."""
    szoveg = szoveg.lstrip("\ufeff").translate(JAVITAS).strip()
    if not szoveg:
        raise ImportHiba("Üres a szövegmező.")

    reader = csv.DictReader(io.StringIO(szoveg, newline=""), delimiter=";", quotechar='"')
    if not reader.fieldnames or not KELL <= set(reader.fieldnames):
        raise ImportHiba("Az első sor nem a várt fejléc (tanulokod;nev;mat;angol;2nyelv;tesi;csaladszam;tesoszam).")

    tanulok = []
    for r in reader:
        try:
            tanulok.append(Tanulo(
                tanulokod=int(r["tanulokod"]),
                nev=r["nev"].strip(),
                mat=r["mat"],
                angol=r["angol"],
                nyelv2=r["2nyelv"],
                tesi=r["tesi"],
                csaladszam=int(r["csaladszam"]),
                tesoszam=int(r["tesoszam"]),
            ))
        except (TypeError, ValueError, AttributeError):
            raise ImportHiba(f"Hibás adat a(z) {reader.line_num}. sorban.")

    Tanulo.objects.all().delete()
    try:
        Tanulo.objects.bulk_create(tanulok)
    except IntegrityError:
        raise ImportHiba("A tanulokod mező értékei nem egyediek.")
    return len(tanulok)
