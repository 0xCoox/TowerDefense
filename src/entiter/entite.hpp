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
        : m_x(x), m_y(y), m_type(entite), m_id(genererIdUnique()) {}

    //Destructeur, evite les fuites mémoires
    virtual ~Entite() = default;

    //méthodes de polymorphismes, class abstraite 
    virtual void update(float dt) = 0;
    
    virtual void render(Rendu& rendu) const = 0; 

    // Getters inline - Vu dans StudentManager
    inline float getX() const { return m_x; }
    inline float getY() const { return m_y; }
    inline int getId() const { return m_id; }
    inline TypeEntite getType() const { return m_type; }

protected: 
    // Ennemis et Tours puissent modifier leurs coordonnées
    float m_x;
    float m_y;
    TypeEntite m_type; //
    int m_id; // id unique par tout

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