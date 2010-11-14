#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>
//#include "SDL_mixer.h"
#include "singleton.hpp"

#define g_pTimer CTimer::Get ()

class CTimer : public TSingleton<CTimer>
{
  public:
    CTimer           ();

    void  Update     ();
    float GetElapsed () {return m_fElapsed;}

  private:
    float m_fElapsed;  // Vergangene Zeit seit dem letzten Frame
    float m_fCurTime;  // Aktuelle Zeit
    float m_fLastTime; // Zeit des letzten Frames

};

#endif
