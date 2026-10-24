from django.contrib import admin

from .models import Tanulo


@admin.register(Tanulo)
class TanuloAdmin(admin.ModelAdmin):
    list_display = ("tanulokod", "nev", "mat", "angol", "nyelv2", "tesi", "csaladszam", "tesoszam")
    list_filter = ("mat", "angol", "nyelv2", "tesi")
    search_fields = ("nev",)
