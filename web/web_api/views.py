from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.forms.models import model_to_dict
from .models import Node
from .models import Alias
import sys
import json
sys.path.append("..")
from methodDevelopment.build import method_development

def tree_setup(tree):
    print('Initializing c++ Tree Manager')
    nodes = [model_to_dict(node) for node in Node.objects.all()]
    py_nodes = []
    for node in nodes:
        aliases = [alias.alias for alias in Alias.objects.filter(origin_name__exact=node['name'])]
        py_node = method_development.NodePy(
            node['name'],
            node['parent'],
            node['description'],
            aliases
        )
        py_nodes.append(py_node)
    tree.buildTree(py_nodes)

tree = method_development.TreePyManager()
tree_setup(tree)

def graph(request):
    nodes_dict = {
        'nodes' : [
            {
                'name':node.getName(),
                'description':node.getDescription(),
                'parent':node.getParentName(),
                'alises':node.getAliases()
            } for node in tree.getTree()
        ]
    }
    response = JsonResponse(nodes_dict)
    response['Access-Control-Allow-Origin'] = '*'
    return response

def node_at(request, name):
    if request.method == "GET":
        requesed_node = tree.findNode(name)
        response = JsonResponse({
            'name':requesed_node.getName(),
            'description':requesed_node.getDescription(),
            'parent':requesed_node.getParentName(),
            'alises':requesed_node.getAliases()
        })
        response['Access-Control-Allow-Origin'] = '*'
        return response
    if request.method == "DELETE":
        # TODO: return error response if not found
        tree.removeNode(name)
        return HttpResponse('') 

def add_node_manual(request):
    if request.method != "POST":
        return HttpResponse('') # TODO: return error response
    node_to_add = json.loads(request.body.decode('utf-8'))
    py_node = method_development.NodePy(
        node_to_add['name'],
        node_to_add['parent'],
        node_to_add['description'],
        node_to_add['aliases']
    )
    tree.manualAdd(py_node)
    return HttpResponse('')

def add_node_auto(request):
    pass