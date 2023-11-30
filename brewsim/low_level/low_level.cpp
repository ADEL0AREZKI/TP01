#include <iostream>
#include <cpr/cpr.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <string>
using namespace std;
using json = nlohmann::json;
class Departement{

    int numero_;
    float prixm2_;
    int id_;

    public :

        Departement(int numero, float prixm2) : numero_{numero}, prixm2_{prixm2}{}

//................................Constructeur 1..........................................
                Departement(const json& data)
                {
                    numero_ = data["numero_"],prixm2_=data["prixm2_"];
                }
//................................Constructeur 2..........................................
                Departement(int id) : numero_(id), prixm2_(0)
               {
                 std::string id_string = std::to_string(id);
                 std::string plop = "http://localhost:8000/departement/";
                 cpr::Response r  = cpr::Get(cpr::Url(plop + id_string));
                 cout<<"contenue de la reponse :"<<r.text<<endl;
               }


        friend std::ostream& operator<<(std::ostream& out, const Departement& D) {
        return out << D.numero_ << " / " << D.prixm2_;
        }
};
// I add new things here
class Machine {
    std::string machine_;
    int prix_;
public:
    Machine(int id) {
        std::string u = "http://localhost:8000/Machine/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        machine_ = j["nom"];
        prix_ = j["prix"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Machine& p) {
        return out << "nom:" << p.machine_ << ", prix:" << p.prix_;
    }
};
// OK
class Ingredient {
    std::string nom_ingredient;

public:
    Ingredient(std::string nom) {
        nom_ingredient = nom;
    }

    Ingredient(json j) {
        nom_ingredient = j["nom"];
    }

    Ingredient(int id) {
        std::string u = "http://localhost:8000/Ingredient/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        nom_ingredient = j["nom"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Ingredient& p) {
        return out << "Ingredient:" << p.nom_ingredient;
    }
};
// OK
class QuantiteIngredient {
    std::unique_ptr<Ingredient> ingredient_;
    int quantite_ing;

public:
    QuantiteIngredient(int id) {
        std::string u = "http://localhost:8000/QuantiteIngredient/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        ingredient_ = std::make_unique<Ingredient>(j["ingredient"]);
        quantite_ing = j["quantite"];
    }

    friend std::ostream& operator<<(std::ostream& out, const QuantiteIngredient& p) {
        return out << "ingredient:" << *p.ingredient_ << ", quantite:" << p.quantite_ing;
    }
};
// OK
class Action {
    std::unique_ptr<Machine> machine_;
    std::string commandes_;
    int duree_;
    std::unique_ptr<Ingredient> ingredient_;
    std::optional<std::unique_ptr<Action>> action_;

public:
    Action(int id) {
        std::string u = "http://localhost:8000/Action/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        machine_ = std::make_unique<Machine>(j["machine"]);
        commandes_ = j["commandes"];
        ingredient_ = std::make_unique<Ingredient>(j["ingredient"]);
        if (j["action"])
            action_ = std::make_unique<Action>(j["action"]);
    }
};
// OK

/*
class Recette {
    std::unique_ptr<Recette> recette_;
    std::unique_ptr<Action> action_;

public:
    Prix(json j) {

        recette_ = j["recette"];
        action_ = j["action"];
    }
    Recette(int id) {
        std::string u = "http://localhost:8000/QuantiteIngredient/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        recette_ = std::make_unique<Recette>(j["recette"]);
        action_ = std::make_unique<Action>(j["action"]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Recette& p) {
        return out << "recette:" << *p.recette_ << ", action:" << *p.action_;
    }
};
class Prix {
    std::unique_ptr<Ingredient> ingredient_;
    std::unique_ptr<Departement> departement_;
    int prix_;

public:
    Prix(json j) {
        ingredient_ = j["ingredient"];
        departement_ = j["departement"];
        prix_ = j["prix"];
    }

    Prix(int id) {
        std::string u = "http://localhost:8000/Prix/" + std::to_string(id);
        cpr::Response r = cpr::Get(cpr::Url{u});
        std::cout << r.status_code << std::endl;
        json j = json::parse(r.text);
        ingredient_ = std::make_unique<Ingredient>(j["ingredient"]);
        departement_ = std::make_unique<Departement>(j["departement"]);
        prix_ = j["prix"];
        json j = json::parse(r.text);
        nom_ingredient = j["nom"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Prix& p) {
        return out << "ingredient:" << *p.ingredient_ << ", departement:" << *p.departement_ << ", prix:" << p.prix_;
    }
};

class Usine {
  std::unique_ptr<Usine> nom_usine;
  std::unique_ptr<Usine> zone_;
  std::unique_ptr<Departement> departement_;
  int taille_;
  std::vector<std::unique_ptr<Machine> machine_;
  std::vector<std::unique_ptr<Recette> recette_;
  std::vector<std::unique_ptr<QuantiteIngredient> stocks_;
  public:
  Usine(json j) {
      nom_usine = j["nom usine"];
      zone_ = j["zone"];
      departement_ = j["departement"];
      taille_ = j["taille"];
      machine_ = j["machine"];
      recette_ = j["recette"];
      stocks_ = j["stocks"];
  }

  Usine(int id) {
      std::string u = "http://localhost:8000/Prix/" + std::to_string(id);
      cpr::Response r = cpr::Get(cpr::Url{u});
      std::cout << r.status_code << std::endl;
      json j = json::parse(r.text);
      nom_usine_ = std::make_unique<Usine>(j["nom usine"]);
      zone_ = std::make_unique<Usine>(j["zone"]);
      departement_ = std::make_unique<Departement>(j["departement"]);
      machine_ = j["machine"];
      recette_ = j["recette"];
      stocks_ = j["stocks"];
  }

  friend std::ostream& operator<<(std::ostream& out, const Usine& p) {
      return out << "departement:" << *p.departement_ << ", machine :" << *p.machine_ << ", taille:" << p.taille_;
  }



};
*/

auto main()-> int{

    std::cout << Departement{31, 20} << "\n";
    cpr::Response r = cpr::Get(cpr::Url("http://localhost:8000/departement/1"));
    cout<<"contenue de la reponse :"<<r.text<<endl;
    json j = json::parse(r.text);
    std::cout << j << std::endl;

return 0;
}
