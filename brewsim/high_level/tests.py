# Create your tests here.
from django.test import TestCase

from .models import Departement, Ingredient, Machine, Prix, QuantiteIngredient, Usine


class MachineModelTests(TestCase):
    def test_usine_creation(self):
        depart = Departement.objects.create(numero=31, prixm2=2000)
        houblon = Ingredient.objects.create(nom="houblon")
        orge = Ingredient.objects.create(nom="orge")
        four = Machine.objects.create(nom="four", prix=1000)
        malaxeur = Machine.objects.create(nom="malaxeur", prix=2000)

        Prix.objects.create(ingredient=houblon, departement=depart, prix=20)
        Prix.objects.create(ingredient=orge, departement=depart, prix=10)

        stock_houblon = QuantiteIngredient.objects.create(
            ingredient=houblon, quantite=50
        )
        stock_orge = QuantiteIngredient.objects.create(ingredient=orge, quantite=100)

        usine = Usine.objects.create(departement=depart, taille=50)
        usine.machines.add(four)
        usine.machines.add(malaxeur)
        usine.stocks.add(stock_houblon)
        usine.stocks.add(stock_orge)

        self.assertEqual(Usine.objects.first().costs(), 105000)
