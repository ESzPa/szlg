from django.urls import path

from . import views

app_name = "csoportok"

urlpatterns = [
    path("", views.index, name="index"),
    path("import/", views.import_adatok, name="import_adatok"),
    path("2sok/", views.sok2, name="sok2"),
    path("3spec/", views.spec3, name="spec3"),
    path("4kis-kun/", views.kis_kun4, name="kis_kun4"),
    path("5bontas/", views.bontas5, name="bontas5"),
    path("6izsak/", views.izsak6, name="izsak6"),
    path("7kapocs/", views.kapocs7, name="kapocs7"),
    path("hianyzo/", views.hianyzo, name="hianyzo"),
    path("hirvivo/", views.hirvivo, name="hirvivo"),
]
