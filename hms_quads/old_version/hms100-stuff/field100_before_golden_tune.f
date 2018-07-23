      program field_new

c     calculate the current necessary to reach a certain B.dl
c     in Rolf's notation and in the new fit, valid up to 500 Amps
c     the 1.5% correction has been taken into account

      real*8 bdl1,bdl2,bdl3,sign_HMS,p_HMS
      real*8 fac1,fac2,fac3,I_Q1,I_Q2,I_Q3

      data befl_q1/2.6571/     ! all factors normalized for 6GeV/c particles
      data befl_q2/3.3233/     ! Tm/A/(6GeV/c)
      data befl_q3/1.6324/
      data field_D/0.2765/
      data renorm_mom/1.009/

      type *,'Input HMS momentum in GeV, electron is negative.'
      accept *,p_HMS

      sign_HMS = p_HMS/abs(p_HMS)
      p_HMS = abs(p_HMS)

      bdl1=befl_q1*p_HMS/6.
      bdl2=befl_q2*p_HMS/6.
      bdl3=befl_q3*p_HMS/6.

c     Calculate Q1, Q2, Q3 Current conversion factor

      if (bdl1 .le. 1.2964) then
         fac1=293.17*(1-4.752e-4/bdl1)
      else
         fac1=293.17*(1-4.752e-4/bdl1)+1.8*(bdl1-1.2964)**3
      endif

      if (bdl2 .le. 1.604) then
         fac2=187.38*(1-1.4782e-3/bdl2)
      else
         fac2=187.38*(1-1.4782e-3/bdl2)
         fac2=fac2+0.4004*(bdl2-1.604)+0.1251*(bdl2-1.604)**3
      endif

      if (bdl3 .le. 1.609) then
         fac3=186.77*(1-1.4534e-3/bdl3)
      else
         fac3=186.77*(1-1.4534e-3/bdl3)+0.1882*(bdl3-1.609)**3
      endif

      I_Q1=fac1*bdl1
      I_Q2=fac2*bdl2
      I_Q3=fac3*bdl3
      
      type *,'Set current for Q1 = ',I_Q1*sign_HMS*-1./renorm_mom
      type *,'Set current for Q2 = ',I_Q2*sign_HMS/renorm_mom
      type *,'Set current for Q3 = ',I_Q3*sign_HMS*-1./renorm_mom
      type *,'Set NMR for Dipole = ',sign_HMS*p_HMS*field_D/renorm_mom

      end



