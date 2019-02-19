c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Field
c     Calculate the magnet settings for the HMS at a given momentum.
c     Field knows about the quadrupole tune, and the saturation effects
c     in all the magnets.
c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      program field_new

c--------------------------------------------------------------------------
c History:
c   H Szumila-Vance 14-Jan-2018
c      Change the command line output and include the 
c      cycling currents (MOL--minimum on loop currents)
c
c
c     S A Wood 5-Jun-2003
c        The momentum can now be passed on the command line for use by
c        programs that want to call this.  The output will be a single
c        line with the currents for the quads and the field for the
c        separated by ,'s.
c
c     M K Jones 27-Mar-2003
c        Eric Christy's found that the central momentum of the
c   spectrometer was being set to low by  0.003 . Introduce new
c   norm factor : bnorm_03 = -0.003
c   Now 
c      I_Q1 = I_Q1 * renorm_D / renorm_mom/(1+bnorm_03)
c      I_Q2 = I_Q2 * renorm_D / renorm_mom/(1+bnorm_03)
c      I_Q3 = I_Q3 * renorm_D / renorm_mom/(1+bnorm_03)
c      B_D  = B_D             / renorm_mom/(1+bnorm_03)
c     
c
c
c     Antje Bruell 12-Jul-2000
c Modify Q3 set currents to obtain the correct readback currents
c (fitting Iset(readback)/P from D. Pottervelds note 16768 and 
c renormalising at p=0.93)
c I_Q3 = I_Q3 /  (1.0107*(1.004-0.0136*p_HMS)))
c
c     David Potterveld 26-Feb-1999 Old version had incorrect conversion to
c gauss from tesla for the dipole. We want tesla anyways, so I removed
c the units conversion.
c
c     David McKee 8Feb1999
c Add the golden tune parameters from Jochen's file.
c
c     David McKee 22Jan1999
c Added the dipole parameterization in function Bneedd. Made the quadrupole
c paraeterization function Ineedq. I'll keep both ``need'' functions in
c the same file.
c
c     David McKee   20Jan1999
c Changed the form of the fit to reflect the hysterisis effects and
c the golden tune as per Jochen's version. 
c Why did Rolf give me the one without it?
c
c Also move the calculation of I(bl_q[1-3]) into a function.
c
c     David McKee   3Sept1998
c Hacked from Jochen's version to work like the printout that Rolf gave me
c Comented and cleaned up.
c---------------------------------------------------------------------------
      implicit none

      real*8 befl_q1, befl_q2, befl_q3     ! See note below
      real*8 golden1, golden2, golden3
      real*8 futch_q3                      
      real*8 renorm_D, renorm_mom 
      real*8 p_HMS,sign_HMS
      real*8 bl_q1, bl_q2, bl_q3           ! Int{B dot dL} for each quad.
      real*8 I_Q1, I_Q2, I_Q3              ! Currents in the quads.
      real*8 B_D                           ! Field in the dipole. 
      real*8 I_D                           ! Current in the dipole. 

      real*8 Bneedd, Ineedq
      real*8 bnorm_03

      integer iargc
      integer iargcount
      character*30 arg

      real*8 MOL_Q1, MOL_Q2, MOL_Q3        ! Minimum on loop currents
c These three numbers reflect the quadrupole tune.
c They are the desired B.dl for each magnet at a nominal momentum 
c setting of 6.0 GeV. Mess with them at your peril.

c HMS100 tune (from Jochen's version)
      data befl_q1/2.6571/
      data befl_q2/3.3233/
      data befl_q3/1.6324/
      data golden1/1.010/
      data golden2/1.005/
      data golden3/1.010/


c HMS-1? tune
c      data befl_q1/2.8858/
c      data befl_q2/3.4212/
c      data befl_q3/1.7298/
c      data golden1/1.0/
c      data golden2/1.0/
c      data golden3/1.0/


c The rest of these constants are historical. I don't necessarily know where
c the came from, and I'm not going to mess with them. DWM
c Some find of (Dutch(?)) fudge factor. 1.0 is nominal.
c Imperical value based on Dec '94 run
c      data futch_q3/0.983/
      data futch_q3/1.000/

c Renormalization of currents since we set the Dipole by the NMR now.
      data renorm_D/0.985/
c      data renorm_D/1.000/

c Empirical renormalization of central momentum 
      data renorm_mom/1.009/
c mkj determination by Eric Christy of new normalization 2003.
c   this is a correction to the nromalizations above.
      data bnorm_03 /-0.003/

c---------------------------------------------------------------------------
c Finally, the code...

      iargcount = iargc()

c Prompt the user for the momentum, 
c then seperate the sign from the magnitude...

      if(iargcount.gt.0) then
         call getarg(1,arg)
         read(arg,'(e30.0)') p_HMS
      else
         
         write(*,*) 'Input HMS momentum in GeV, electron is negative.'
         read *,p_HMS
      endif

      sign_HMS = p_HMS/abs(p_HMS)
      p_HMS = abs(p_HMS)

c The B.dl we desire is liearly related to the momentum, the befl_q[1-3]s
c are normalized to 6 GeV
      bl_q1=befl_q1*p_HMS/6.*golden1
      bl_q2=befl_q2*p_HMS/6.*golden2
      bl_q3=befl_q3*p_HMS/6.*golden3

c Calculate the needed current.
      I_Q1 = Ineedq(bl_q1,1)
      I_Q2 = Ineedq(bl_q2,2)
      I_Q3 = Ineedq(bl_q3,3)
      B_D  = Bneedd(p_HMS,iargcount)

c Apply the dipole and central momentum normalizations...
      I_Q1 = I_Q1 * renorm_D / renorm_mom/(1+bnorm_03)
      I_Q2 = I_Q2 * renorm_D / renorm_mom/(1+bnorm_03)
      I_Q3 = I_Q3 * renorm_D / renorm_mom/(1+bnorm_03)
      B_D  = B_D             / renorm_mom/(1+bnorm_03)

c For Q3 use readback current instead of setcurrent
c i.e. renormalise by ratio of readback/set current
      I_Q3 = I_Q3 /  (1.0107*(1.004-0.0136/p_HMS))

c Added 19 April 2003 by Joerg Reinhold
c For the Dipole calculate s start value for the set current
      I_D = 1105.7*B_D+13.192*B_D*B_D

c Set the minimum on loop currents
      if (I_Q1+200.gt.930.) then 
         MOL_Q1 = 930.
      else  
         MOL_Q1 = I_Q1+200.
      endif

      if (I_Q2+200.gt.600.) then 
         MOL_Q2 = 600. 
c 910A is old, changed to 610A 19Feb19 --HS                                                             
      else  
         MOL_Q2 = I_Q2+200. 
      endif

      if (I_Q3+200.gt.475.) then 
         MOL_Q3 = 475.                                                              
      else  
         MOL_Q3 = I_Q3+200.
      endif

c Tell the user what setting he wants.
      if(p_HMS > 0.005) then
         print*, '-----------------------------------------------------'
         print*, 'If increasing momentum, go to Minimum On Loop (MOL) '
         print*, 'current first, then to Iset.'
         print*,'Magnet: Q1'
         print*, '     Iset: ',I_Q1,' [A]. MOL current: '
     $     ,MOL_Q1,' [A].'
         print*, ''
         print*,'Magnet: Q2'
     $        
         print*, '     Iset: ',I_Q2,' [A]. MOL current: ',MOL_Q2,' [A].'
     $        
         print*, ''
         print*,'Magnet: Q3'
     $        
         print*, '     Iset: ',I_Q3,' [A]. MOL current: ',MOL_Q3,' [A].'
     $        
         print*, '----------------------------------------------------'
      else
         print*, '-----------------------------------------------------'
         print*, 'If increasing momentum, go to Minimum On Loop (MOL) '
         print*, 'current first, then to Iset.'
         print*, 'Once Q2 reaches 10A, Power Off the magnet.'
         print*,'Magnet: Q1'
         print*, '     Iset: 0.0 [A]. MOL current: 0.0 [A].'
         print*, ''
         print*,'Magnet: Q2'
     $        
         print*, '     Iset: 10.0 [A]. MOL current: 10.0 [A].'
     $        
         print*, ''
         print*,'Magnet: Q3'
     $        
         print*, '     Iset: 0.0 [A]. MOL current: 0.0 [A].'
     $        
         print*, '----------------------------------------------------'



      endif 



C      if(iargcount.ge.1) then
C         print '(3(f9.3,","),f11.7)',I_Q1*sign_HMS*-1.,I_Q2*sign_HMS
C     $        ,I_Q3*sign_HMS*-1.,B_D *sign_HMS
C      else
C         write(*,*) ' Field03 program'
C         write(*,*)'Set current for Q1 = ',I_Q1*sign_HMS*-1.,' amps'
C         write(*,*)'Set current for Q2 = ',I_Q2*sign_HMS    ,' amps'
C         write(*,*)'Set current for Q3 = ',I_Q3*sign_HMS*-1.,' amps'
C         write(*,'(a,f12.9,a,a,f9.4,a)')
C     >' Set NMR for Dipole = ',B_D *sign_HMS,    ' Tesla'
C     >,'  (approximately ',I_D *sign_HMS,' Amps)'
C      endif


      end





      



