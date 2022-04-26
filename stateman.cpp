#include "stateman.h"

StateMan::StateMan() : m_add(false), m_replace(false), m_remove(false) //Liste d'initialisation : permet d'initialiser les composantes de la classe
{
    //Donc rien à faire ici
}


void StateMan::Add(State* toAdd, bool replace)
{
    m_add = true;
    m_newState = toAdd;

    m_replace = replace;
}

void StateMan::PopCurrent()
{
    m_remove = true;
}

void StateMan::ProcessStateChange()
{
    if(m_remove && (!m_stateStack.empty()))
    {
        m_stateStack.pop();

        if(!m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }

        m_remove = false;
    }

    if(m_add)
    {
        if(m_replace && (!m_stateStack.empty()))
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if(!m_stateStack.empty())
        {
            m_stateStack.top()->Pause();
        }

        m_stateStack.push(m_newState);
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}

State* StateMan::GetCurrent()
{
    return m_stateStack.top();
}

StateMan::~StateMan()
{
    delete m_newState;
    for(unsigned int i = 0;i<m_stateStack.size();i++)
    {
        delete m_stateStack.top();
        m_stateStack.pop();
    }
    
}