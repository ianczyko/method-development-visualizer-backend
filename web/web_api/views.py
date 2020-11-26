from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.forms.models import model_to_dict
from .models import Node
from .models import Alias

def graph(request):
    nodes = [model_to_dict(node) for node in Node.objects.all()]
    for node in nodes:
        aliases = [alias.alias for alias in Alias.objects.filter(origin_name__exact=node['name'])]
        node['aliases'] = aliases
    nodes_dict = {'nodes':nodes}
    return JsonResponse(nodes_dict)
