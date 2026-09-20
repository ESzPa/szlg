from django.shortcuts import render
from django.http import HttpResponse

def view_negyedik(request):
    return render(request, 'index.html')
