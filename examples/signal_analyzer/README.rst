Signal Analyzer
===============

A minimalistic signal analyzer.

PWM
---

Measure duty cycle and frequency on eight pins in parallel with the
file system command ``/pwm/measure``.

.. code-block:: text

   $ pwm/measure 
   20: [(0,0),(0,0),(100,1),(0,0),(0,0),(0,0),(0,0),(0,0)]
   $ pwm/measure 10
   20: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   40: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   60: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   80: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   100: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   120: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   140: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   160: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   180: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   200: [(0,0),(0,0),(100,0),(0,0),(0,0),(0,0),(0,0),(0,0)]
   $ 
