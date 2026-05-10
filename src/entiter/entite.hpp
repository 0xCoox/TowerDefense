#include <functional>

// Forward Declaration bien moins lourd qu'un include rendu;
class Rendu; 

enum class TypeEntite {
    Tour,
    Ennemi,
    Projectile
};

class Entite {
public:
    Entite(float x, float y, TypeEntite entite) 
        : x_(x), y_(y), type_(entite), id_(genererIdUnique()) {}

    //Destructeur, evite les fuites mémoires
    virtual ~Entite() = default;

    //méthodes de polymorphismes, class abstraite 
    virtual void update(float dt) = 0;
    
    virtual void render(Rendu& rendu) const = 0; 

    // Getters inline - Vu dans StudentManager
    inline float getX() const { return x_; }
    inline float getY() const { return y_; }
    inline int getId() const { return id_; }
    inline TypeEntite getType() const { return type_; }

protected: 
    // Ennemis et Tours puissent modifier leurs coordonnées
    float x_;
    float y_;
    TypeEntite type_; //
    int id_; // id unique par tout

private:
    // on genere les id pour mon unordered_set
    static int genererIdUnique() {
        static int compteur = 0;
        return compteur++;
    }
};

//permet de stocker mes pointeurs d'Entite dans un unordered_set
struct StockEntite {
    inline size_t operator()(const Entite* e) const {
        return std::hash<int>()(e->getId());
    }
};