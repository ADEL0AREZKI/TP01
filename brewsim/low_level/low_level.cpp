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

auto main()-> int{

    std::cout << Departement{31, 20} << "\n";
    cpr::Response r = cpr::Get(cpr::Url("http://localhost:8000/departement/1"));
    cout<<"contenue de la reponse :"<<r.text<<endl;
    json j = json::parse(r.text);
    std::cout << j << std::endl;

return 0;
}
