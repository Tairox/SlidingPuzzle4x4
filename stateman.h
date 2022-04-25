#ifndef __stateman_h__
#define __stateman_h__

#include <stack> //Pour créer une pile LIFO
#include <memory> //Pour créer des unique_ptr --> Pointeurs intelligents où on n'a pas besoin de delete la zone mémoire allouée

#include <state.h> //La classe crée précédemment est générique il faut donc indiquer au compilateur de l'inclure

namespace Engine //Pour ne pas avoir à taper Engine:: à chaque fois
{
    class StateMan //For State Manager
    {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack; //Pile de pointeurs sur états
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;

    public:
        StateMan();
        ~StateMan();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessStateChange();
        std::unique_ptr<State>& GetCurrent();
};

} // namespace Engine

#endif