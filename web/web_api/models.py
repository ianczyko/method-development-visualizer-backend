from django.db import models

class Node(models.Model):
    name = models.CharField(max_length=30)
    description = models.TextField()
    parent = models.CharField(max_length=30)

class Alias(models.Model):
    alias = models.CharField(max_length=30)
    origin_name = models.CharField(max_length=30)
