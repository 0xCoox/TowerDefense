# --- Configuration du compilateur ---
CXX = g++

# Flags de compilation : C++20, warnings activés, et on inclut le dossier src
CXXFLAGS = -std=c++20 -Wall -Wextra -I./src

# Flags d'édition de liens : on relie les bibliothèques SDL2
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

# --- Dossiers ---
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
DOC_DIR = doc

# --- Documentation ---
DOXYFILE = Doxyfile

# --- Nom de l'exécutable final ---
TARGET = $(BIN_DIR)/tower_defense

# --- Recherche automatique des fichiers ---
# Trouve tous les .cpp dans le dossier src et ses sous-dossiers
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Déduit le nom des fichiers objets (.o) correspondants dans le dossier build
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# --- Règles de compilation ---

# Règle par défaut quand tu tapes juste 'make'
all: $(TARGET)

# Édition de liens (création de l'exécutable final)
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Compilation terminée avec succès ! Exécutable dans $(TARGET)"

# Compilation de chaque fichier .cpp en .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pratique pour compiler et lancer le jeu d'un coup
run: all
	./$(TARGET)

# Génération de la documentation avec Doxygen
doc:
	doxygen Doxyfile

# Règle pour tout nettoyer : build, bin et documentation
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(DOC_DIR)
	@echo "Nettoyage terminé."

# Indique à Make que ces mots ne sont pas des fichiers
.PHONY: all clean run doc