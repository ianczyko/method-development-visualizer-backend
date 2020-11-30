from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.forms.models import model_to_dict
from .models import Node
from .models import Alias
import sys
sys.path.append("..")
from methodDevelopment.build.method_development import hello_cpp

def graph(request):
    nodes = [model_to_dict(node) for node in Node.objects.all()]
    for node in nodes:
        aliases = [alias.alias for alias in Alias.objects.filter(origin_name__exact=node['name'])]
        node['aliases'] = aliases
    nodes_dict = {'nodes':nodes}
    response = JsonResponse(nodes_dict)
    # TODO: remove temporary solution for CORS
    response['Access-Control-Allow-Origin'] = '*'
    return response

def cpp_hello_world(request):
    return HttpResponse(hello_cpp())
    # returns text 'hello from c++'
