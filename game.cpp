#include "game.h"

int Game::Builder::setPerfil (const char p){
    Perfil* newPerfil = new Perfil(p);
    if(!perfilExists(p)){
        perfilList.push_back(newPerfil);
        return 1;
    } else {
        return 0;
    }
}

int Game::Builder::perfilExists(const char p){
    for(std::vector<Perfil*>::iterator it = perfilList.begin();
        it != perfilList.end(); ++it){
        if ((*it)->getLabel() == p)
            return 1;
    }
    return 0;
}

Perfil* Game::Builder::getPerfilFromList(const char p){
    int index=0;
    for(std::vector<Perfil*>::iterator it = perfilList.begin();
        it != perfilList.end(); ++it){
        if ((*it)->getLabel() == p){
            Perfil* found = perfilList[index];
            return found;
        }
        index++;
    }
}

//adds new modifier a a perfil
//return 1:added -1:perfil doesnt exist -2:forca unavailable
int Game::Builder::addModifierToPerfil(char label, int id){
    if(perfilExists(label))
    {
        if(getPerfilFromList(label)->addModifier(id)){
            return 1;
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

//return 1:removed -1:perfil doesnt exist -2:Modifier doesnt exist
int Game::Builder::rmModifierFromPerfil(char label,int id){
    if(perfilExists(label)){
        if (getPerfilFromList(label)->rmModifier(id)){
            return 1;
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

//return 1:removed 0:perfil not found
//TODO: check for memory leaks
int Game::Builder::rmPerfil(char label){
    int index;
    if(perfilExists(label)){
        getPerfilFromList(label)->deleteLists();
        index = getPerfilIndex(label);
        delete (getPerfilFromList(label));
        perfilList.erase(perfilList.begin()+index);
        return 1;
    } else {
        return 0;
    }
}

int Game::Builder::getPerfilIndex(const char label){
    int index = 0;
    for(std::vector<Perfil*>::iterator it = perfilList.begin();
        it != perfilList.end(); ++it){
        if ((*it)->getLabel() != label)
            index++;
    }
    return index;
}
